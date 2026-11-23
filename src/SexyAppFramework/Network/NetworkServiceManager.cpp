//
//  NetworkServiceManager.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-11-17.
//
#include "SexyAppFramework/Common.h"
#include "NetworkServiceManager.h"
#include "AsyncTaskManager.h"
#include "ResumeRequestInfo.h"
#include "SexyAppFramework/SexyAppBase.h"
#include "JsonWriter.h"
#include "JsonReader.h"

using namespace Sexy;

namespace Sexy { extern CritSect gNetworkServiceRequestLock; }

/////////////// Lifecycle ///////////////

static NetworkServiceManager* sDefaultNetworkServiceManager;
static DummyNetworkServiceListener sDummyNetworkServiceListener;

NetworkServiceManager* NetworkServiceManager::DefaultNetworkServiceManager()
{
	if ( sDefaultNetworkServiceManager == NULL )
		sDefaultNetworkServiceManager = new NetworkServiceManager();
	return sDefaultNetworkServiceManager;
}

NetworkServiceManager* NetworkServiceManager::TryDefaultNetworkServiceManager()
{
	return sDefaultNetworkServiceManager;
}

NetworkServiceManager::NetworkServiceManager()
	: mLogLevel(LOG_NONE)
	, mNextRequestId(1)
{
	AsyncTaskManager* taskManager = AsyncTaskManager::DefaultAsyncTaskManager();
	if (taskManager != NULL)
		mResumeRequestTaskManager = taskManager;
	else
		mResumeRequestTaskManager = new AsyncTaskManager();
	MkDir(ResumableRequestInfo::GetResumeCachedFolder());
	DeleteOldPartialFiles();
}

NetworkServiceManager::~NetworkServiceManager()
{
	delete mResumeRequestTaskManager;
	mResumeRequestTaskManager = NULL;
}

/////////////// Channels ///////////////

void NetworkServiceManager::FillWithChannels( ChannelPtrs& outChannels )
{
	outChannels.clear();
	outChannels[DefaultChannelName] = &mDefaultChannel;
	Channels::iterator it;
	for ( it = mNamedChannels.begin(); it != mNamedChannels.end(); ++it )
	{
		outChannels[it->first] = &it->second;
	}
}

void NetworkServiceManager::EnqueueRequest( StructuredData::String channelName, const NetworkServiceRequest& request )
{
	Channel* channel = GetChannel( channelName );
	if ( channel->slots.empty() )
	{
		channel->slots.resize( 2 );
	}
	channel->requests.push_back( request );
	SlotNextRequest( channel );
}

NetworkServiceManager::RequestId NetworkServiceManager::GetNextRequestId()
{
	RequestId requestId = mNextRequestId;
	if ( ++mNextRequestId < 0 )
	{
		mNextRequestId = 1;
	}
	return requestId;
}

void NetworkServiceManager::ConfigureChannel( StructuredData::String channelName, uint32 slotCount )
{
	GetChannel( channelName )->slots.resize( slotCount );
}

void NetworkServiceManager::SetLogLevel( LogLevel level )
{
	mLogLevel = level;
}

/////////////// Requests ///////////////

NetworkServiceManager::RequestId NetworkServiceManager::MakeRequest( const StructuredData* request, const NetworkServiceProfile* profile, NetworkServiceListener* listener, const void* context )
{
	const char* path = request->StringForPath( "$.path", 0 );
	const StructuredData::Value* params = request->ObjectForPath( "$.params" );
	std::string url = profile->uri;
	if ( path )
		AppendPathComponent( url, path );
	std::string query;
	if ( profile->params.Readable() )
		profile->params.AppendToQueryString( query );
	if ( params )
		params->AppendToQueryString( query );
	url += query;
	return MakeRequest( request, url, listener, context );
}

NetworkServiceManager::RequestId NetworkServiceManager::MakeRequest( const StructuredData* request, NetworkServiceListener* listener, const void* context )
{
	return MakeRequest( request, -1, listener, context );
}

NetworkServiceManager::RequestId NetworkServiceManager::MakeRequest( const StructuredData* request, const std::string& url, NetworkServiceListener* listener, const void* context )
{
	return MakeRequest( request, -1, url, listener, context );
}

bool NetworkServiceManager::DeleteOldPartialFiles( void )
{
	bool result = true;
	IFileDriver* driver = gSexyAppBase->mFileDriver;
	FileSearchInfo info;
	IFileSearch* search = driver->FileSearchStart( ResumableRequestInfo::GetResumeCachedFolder(), &info );
	do
	{
		if ( !info.is_directory && IsPartialFile( info.file_name ) && IsOlderThan( 1209600, ResumableRequestInfo::GetResumeCachedFolder() + info.file_name ) )
		{
			std::string path = ResumableRequestInfo::GetResumeCachedFolder() + info.file_name;
			if ( result )
				result = driver->DeleteFile( path );
		}
	} while ( driver->FileSearchNext( search, &info ) );
	driver->FileSearchEnd( search );
	return result;
}

void NetworkServiceManager::EncodeFormData( const StructuredData::Value* formData, NetworkServiceRequest& request )
{
	std::string boundary = "_{{}}_";
	std::string startBoundary = "--" + boundary;
	std::string endBoundary = "--" + boundary + "--";
	std::string contentType = "multipart/form-data; boundary=" + boundary;
	request.requestBody = new Buffer;
	for ( const StructuredData::Value* it = formData->ChildrenBegin(); it != formData->ChildrenEnd(); it = it->Next() )
	{
		std::string value = it->StringValue();
		if ( !value.empty() )
		{
			request.requestBody->WriteLine( startBoundary );
			request.requestBody->WriteLine( StrFormat( "Content-Disposition: form-data; name=\"%s\"", it->Name() ) );
			request.requestBody->WriteLine( "" );
			request.requestBody->WriteLine( value );
		}
	}
	request.requestBody->WriteLine( endBoundary );
	request.httpTransaction->SetRequestHeader( "Content-Type", contentType );
	request.httpTransaction->SetRequestHeader( "Content-Length", StrFormat( "%d", request.requestBody->GetDataLen() ) );
	request.httpTransaction->SetRequestBody( request.requestBody->GetDataPtr(), request.requestBody->GetDataLen() );
}

NetworkServiceManager::RequestId NetworkServiceManager::MakeRequest( const StructuredData* request, RequestId inUseRequestId, NetworkServiceListener* listener, const void* context )
{
	const char* path = request->StringForPath( "$.path", 0 );
	const StructuredData::Value* params = request->ObjectForPath( "$.params" );
	const char* baseUrl = request->StringForPath( "$.url", 0 );
	if ( !baseUrl )
		return -1;
	std::string url = baseUrl;
	if ( path )
		AppendPathComponent( url, path );
	if ( params )
	{
		std::string query;
		params->AppendToQueryString( query );
		url += query;
	}
	return MakeRequest( request, inUseRequestId, url, listener, context );
}

NetworkServiceManager::RequestId NetworkServiceManager::MakeRequest( const StructuredData* request, RequestId inUseRequestId, const std::string& url, NetworkServiceListener* listener, const void* context )
{
	if ( !listener )
		listener = &sDummyNetworkServiceListener;
	const StructuredData::Value* postData = request->ObjectForPath( "$.postData" );
	const StructuredData::Value* formData = request->ObjectForPath( "$.formData" );
	const char* method = request->StringForPath( "$.method", ( postData || formData ) ? "POST" : "GET" );
	const char* channel = request->StringForPath( "$.channel", defaultChannel );
	int priority = request->IntegerForPath( "$.priority", defaultPriority );
	const char* schema = request->StringForPath( "$.schema", 0 );
	int timeout = request->IntegerForPath( "$.timeout", defaultTimeout );
	const char* trace = request->StringForPath( "$.trace", 0 );
	bool slackCerts = request->BooleanForPath( "$.slackCerts", false );
	const char* username = request->StringForPath( "$.basicAuth.username", 0 );
	const char* password = request->StringForPath( "$.basicAuth.password", 0 );
	bool resumable = request->BooleanForPath( "$.resumable", false );
	const char* targetFilePath = request->StringForPath( "$.targetFilePath", 0 );
	request->BooleanForPath( "$.reRequest", false );
	int resumePos = request->IntegerForPath( "$.resumePos", defaultResumePos );
	StructuredData::Integer responseBufferSize = request->IntegerForPath( "$.responseBufferSize", 2048 );
	int diskBufferSize = request->IntegerForPath( "$.diskBufferSize", 1048576 );
	bool disableIfRangeHeader = request->BooleanForPath( "$.disableIfRangeHeader", true );
	const char* req = formData ? formData->StringForName( "req", "" ) : NULL;
	if ( inUseRequestId == -1 )
		inUseRequestId = GetNextRequestId();
	ResumableRequestInfo* resumableInfo = NULL;
	if ( resumable )
	{
		if ( !targetFilePath )
			targetFilePath = "";
		if ( responseBufferSize == 2048 )
			responseBufferSize = 15360;
		resumableInfo = new ResumableRequestInfo( *request, diskBufferSize, targetFilePath, resumePos, !disableIfRangeHeader );
	}
	NetworkServiceRequest serviceRequest( resumableInfo, inUseRequestId );
	serviceRequest.httpTransaction = gSexyAppBase->mHttpDriver->CreateHttpTransaction( method, url, responseBufferSize );
	serviceRequest.httpTransaction->SetTimeout( timeout );
	serviceRequest.httpTransaction->SetSlackCertificateValidation( slackCerts );
	serviceRequest.context = context;
	serviceRequest.listener = listener;
	serviceRequest.schema = NULL;
	serviceRequest.priority = priority;
	if ( serviceRequest.IsResumableRequest() )
		serviceRequest.GetResumableRequestInfo()->Prepare( this, url );
	if ( trace )
		serviceRequest.trace = trace;
	else if ( mLogLevel > 0 )
		serviceRequest.trace = StrFormat( "%s:%p", channel ? channel : "default", context );
	if ( username && password )
		serviceRequest.httpTransaction->SetBasicAuth( username, password );
	if ( postData )
	{
		serviceRequest.requestBody = new Buffer;
		JsonWriter writer( JsonWriter::COMPACT );
		writer.Write( serviceRequest.requestBody, postData );
		serviceRequest.httpTransaction->SetRequestHeader( "Content-Type", "application/json" );
		serviceRequest.httpTransaction->SetRequestBody( serviceRequest.requestBody->GetDataPtr(), serviceRequest.requestBody->GetDataLen() );
	}
	else if ( formData )
		EncodeFormData( formData, serviceRequest );
	if ( schema )
	{
		Schemata::iterator it = mSchemata.find( schema );
		if ( it != mSchemata.end() )
			serviceRequest.schema = it->second;
	}
	if ( req )
		serviceRequest.req = req;
	if ( serviceRequest.GetCancelState() != NetworkServiceRequest::CancelState_NotCanceled )
		inUseRequestId = -1;
	else
		EnqueueRequest( channel, serviceRequest );
	return inUseRequestId;
}

void NetworkServiceManager::HttpReceivedData( IHttpTransaction* http, void* data, size_t length )
{
	Slot* slot = (Slot*)http->GetUserData();
	if ( UpdateRequestsPendingCancel( slot ) )
		return;
	if ( slot->request.IsResumableRequest() )
	{
		if ( slot->request.GetResumableRequestInfo() )
		{
			slot->request.GetResumableRequestInfo()->DispatchProgressNotification( slot->request.listener, slot->request.context );
			slot->request.GetResumableRequestInfo()->HandleReceivedData( data, length );
		}
		UpdateRequestsPendingCancel( slot );
	}
	else
		slot->responseBuffer->WriteBytes( (const uint8*)data, length );
}

void NetworkServiceManager::HttpTransactionError( IHttpTransaction* http )
{
	Slot* slot = (Slot*)http->GetUserData();
	NetworkServiceRequest& request = slot->request;
	request.AbortCancelRequest();
	Channel* channel = slot->channel;
	StructuredData& response = slot->response;
	std::string error = http->GetErrorMessage();
	if ( !request.trace.empty() )
		OutputDebugStrF( "xxxxx\n[%s]\n%s\nxxxxx\n\n", request.trace.c_str(), error.c_str() );
	response.Clear();
	response.BeginObject();
	response.AddString( "error", error );
	response.AddString( "req", request.req );
	response.EndObject();
	request.MarkForCancellation( false );
	request.CancelHttpTransactionAndEnterPendingCancel( slot );
	request.listener->ServiceRequestFailed( &response, request.context );
	SlotNextRequest( channel );
}

void NetworkServiceManager::CancelRequest( RequestId inRequestToCancel )
{
	if ( inRequestToCancel != InvalidRequestId )
	{
		ChannelPtrs channels;
		FillWithChannels( channels );
		ChannelPtrs::iterator it;
		for ( it = channels.begin(); it != channels.end(); ++it )
		{
			if ( CancelRequest( it->second, inRequestToCancel ) )
				break;
		}
	}
}

bool NetworkServiceManager::CancelRequest( Channel* channel, RequestId inRequestToCancel )
{
	for ( Queue::iterator it = channel->requests.begin(); it != channel->requests.end(); ++it )
	{
		if ( it->requestId == inRequestToCancel )
		{
			it->MarkForCancellation( true );
			it->CancelImmediate();
			channel->requests.erase( it );
			return true;
		}
	}
	for ( Slots::iterator it = channel->slots.begin(); it != channel->slots.end(); ++it )
	{
		Slot& slot = *it;
		if ( !slot.IsFree() && slot.request.requestId == inRequestToCancel )
		{
			slot.request.MarkForCancellation( true );
			if ( !slot.request.IsResumableRequest() )
			{
				slot.request.CancelImmediate();
				SlotNextRequest( slot.channel );
			}
			return true;
		}
	}
	return false;
}

void NetworkServiceManager::CancelRequests( StructuredData::String channelName )
{
	CancelRequests( GetChannel( channelName ) );
}

void NetworkServiceManager::DumpChannelState()
{
	ChannelPtrs channels;
	FillWithChannels( channels );
	ChannelPtrs::iterator it;
	for ( it = channels.begin(); it != channels.end(); ++it )
	{
		Channel* channel = it->second;
		for ( Queue::iterator requestIt = channel->requests.begin(); requestIt != channel->requests.end(); ++requestIt )
		{
		}
		for ( Slots::iterator slotIt = channel->slots.begin(); slotIt != channel->slots.end(); ++slotIt )
		{
			( *slotIt ).IsFree();
		}
	}
}

/////////////// Cancellation ///////////////

void NetworkServiceManager::AddPendingCancelSlot( Slot* slot )
{
	AutoCrit aCrit( mLock );
	mPendingCancels.push_back( slot );
}

bool NetworkServiceManager::UpdateRequestsPendingCancel( Slot* slot )
{
	bool result = false;
	if ( !slot->IsFree() )
	{
		NetworkServiceRequest& request = slot->request;
		int cancelState = request.GetCancelState();
		if ( cancelState == NetworkServiceRequest::CancelState_Canceled )
		{
			result = true;
		}
		else
		{
			if ( cancelState == NetworkServiceRequest::CancelState_CancelRequested )
			{
				result = true;
				request.CancelHttpTransactionAndEnterPendingCancel( slot );
			}
			else
			{
				result = false;
			}
			if ( request.GetCancelState() == NetworkServiceRequest::CancelState_CancelPending )
			{
				if ( !request.IsResumableRequest() || request.GetResumableRequestInfo() == NULL )
				{
					result = true;
					request.CancelImmediate();
					SlotNextRequest( slot->channel );
				}
				else if ( request.GetResumableRequestInfo()->IsQueueEmpty() )
				{
					result = true;
					request.GetResumableRequestInfo()->MarkQueueForDelete();
					request.CancelImmediate();
					SlotNextRequest( slot->channel );
				}
			}
		}
	}
	return result;
}

void NetworkServiceManager::Update()
{
	AutoCrit aCrit( mLock );
	std::vector<Slot*>::iterator it = mPendingCancels.begin();
	while ( it != mPendingCancels.end() )
	{
		UpdateRequestsPendingCancel( *it );
		if ( (*it)->IsFree() )
		{
			it = mPendingCancels.erase( it );
		}
		else
		{
			++it;
		}
	}
}

void NetworkServiceManager::CancelRequests( Channel* channel )
{
	while ( !channel->requests.empty() )
	{
		NetworkServiceRequest& request = channel->requests.back();
		request.MarkForCancellation( true );
		request.CancelImmediate();
		channel->requests.pop_back();
	}
	for ( Slots::iterator it = channel->slots.begin(); it != channel->slots.end(); ++it )
	{
		Slot& slot = *it;
		if ( !slot.IsFree() )
		{
			slot.request.MarkForCancellation( true );
			if ( !slot.request.IsResumableRequest() )
			{
				slot.request.CancelImmediate();
			}
		}
	}
}

void NetworkServiceManager::CancelAllRequests()
{
	ChannelPtrs channels;
	FillWithChannels( channels );
	ChannelPtrs::iterator it;
	for ( it = channels.begin(); it != channels.end(); ++it )
	{
		CancelRequests( it->second );
	}
}

/////////////// Slots ///////////////

NetworkServiceManager::Slot* NetworkServiceManager::Channel::FreeSlot()
{
	for ( Slots::iterator it = slots.begin(); it != slots.end(); ++it )
	{
		Slot& slot = *it;
		if ( slot.IsFree() )
		{
			return &slot;
		}
	}
	return NULL;
}

void NetworkServiceManager::SlotNextRequest( Channel* channel )
{
	Slot* slot;
	while ( !channel->requests.empty() && ( slot = channel->FreeSlot() ) != NULL )
	{
		slot->channel = channel;
		slot->response.Clear();
		slot->responseBuffer = NULL;
		slot->request = channel->requests.front();
		channel->requests.pop_front();
		slot->request.Refresh();
		slot->request.httpTransaction->SetListener( this );
		slot->request.httpTransaction->SetUserData( slot );
		slot->request.httpTransaction->Start();
	}
}

/////////////// NetworkServiceRequest ///////////////

NetworkServiceRequest::NetworkServiceRequest(ResumableRequestInfo* inResumableRequestInfo, int32 inRequestId)
	: httpTransaction(NULL)
	, requestBody(NULL)
	, requestId(inRequestId)
	, mIsResumableRequest(inResumableRequestInfo != NULL)
	, mResumeInfo(inResumableRequestInfo)
	, mCancelState(CancelState_NotCanceled)
	, mShouldNotifyListenerOnCancel(false)
{
	httpTransaction = NULL;
	if (inResumableRequestInfo != NULL)
		inResumableRequestInfo->SetParentRequest(this);
}

void NetworkServiceRequest::Refresh()
{
	if (mResumeInfo != NULL)
		mResumeInfo->SetParentRequest(this);
}

void NetworkServiceRequest::Release()
{
	CancelHttpTransaction();
	if (mResumeInfo != NULL)
		delete mResumeInfo;
	mResumeInfo = NULL;
	SetCancelState(CancelState_Canceled);
}

void NetworkServiceRequest::ConvertToNonResumableRequest()
{
	mIsResumableRequest = false;
	if (mResumeInfo != NULL)
		delete mResumeInfo;
	mResumeInfo = NULL;
}

/////////////// Cancellation ///////////////

NetworkServiceRequest::CancelState NetworkServiceRequest::GetCancelState()
{
	AutoCrit aCrit(gNetworkServiceRequestLock);
	return mCancelState;
}

void NetworkServiceRequest::SetCancelState(CancelState inState)
{
	AutoCrit aCrit(gNetworkServiceRequestLock);
	mCancelState = inState;
}

ResumableRequestInfo* NetworkServiceRequest::GetResumableRequestInfo()
{
	AutoCrit aCrit(gNetworkServiceRequestLock);
	return mResumeInfo;
}

void NetworkServiceRequest::MarkForCancellation(bool inShouldNotifyListener)
{
	AutoCrit aCrit(gNetworkServiceRequestLock);
	SetCancelState(CancelState_CancelRequested);
	mShouldNotifyListenerOnCancel = inShouldNotifyListener;
}

ResumableRequestInfo* NetworkServiceRequest::TakeResumableInfoAndMarkForCancellation(bool inShouldNotifyListener)
{
	AutoCrit aCrit(gNetworkServiceRequestLock);
	ResumableRequestInfo* aResumeInfo = mResumeInfo;
	if (aResumeInfo != NULL)
	{
		MarkForCancellation(inShouldNotifyListener);
		aResumeInfo->SetParentRequest(NULL);
	}
	mResumeInfo = NULL;
	return aResumeInfo;
}

void NetworkServiceRequest::AbortCancelRequest()
{
	SetCancelState(CancelState_NotCanceled);
}

void NetworkServiceRequest::NotifyCancel()
{
	bool aShouldNotify;
	{
		AutoCrit aCrit(gNetworkServiceRequestLock);
		aShouldNotify = mShouldNotifyListenerOnCancel;
	}
	if (aShouldNotify)
		listener->ServiceRequestCanceled(context);
}

void NetworkServiceRequest::CancelHttpTransaction()
{
	if (httpTransaction != NULL)
	{
		httpTransaction->Release();
		httpTransaction = NULL;
	}
	if (requestBody != NULL)
	{
		delete requestBody;
		requestBody = NULL;
	}
}

void NetworkServiceRequest::CancelHttpTransactionAndEnterPendingCancel(void* slot)
{
	CancelHttpTransaction();
	SetCancelState(CancelState_CancelPending);
	NetworkServiceManager::DefaultNetworkServiceManager()->AddPendingCancelSlot((NetworkServiceManager::Slot*)slot);
}

void NetworkServiceRequest::CancelImmediate()
{
	NotifyCancel();
	Release();
	SetCancelState(CancelState_Canceled);
}
