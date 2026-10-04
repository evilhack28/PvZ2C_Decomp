//
//  AssetsManagerEx.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-25.
//

#include "SexyAppFramework/Common.h"
#include "AssetsManagerEx.h"
#include "DebugLog.h"
#include "SexyAppFramework/drivers/app/android/JavaInterface.h"
#include "GameEventMgr.h"
#undef MD5_H
#include "logServer/md5.h"
#include "AssetsManagerEx.h"

typedef std::__umap_hashtable<std::string, DownloadUnit, std::hash<std::string>, std::equal_to<std::string>, std::allocator<std::pair<const std::string, DownloadUnit> > > DownloadUnitTable;
typedef std::pair<std::__detail::_Node_iterator<std::pair<const std::string, DownloadUnit>, false, true>, bool> DownloadUnitEmplaceResult;
DownloadUnitEmplaceResult DownloadUnitTable_MEmplace(DownloadUnitTable * table, std::string & key, DownloadUnit & unit);

namespace std
{
template<> template<>
DownloadUnitEmplaceResult DownloadUnitTable::emplace<std::string &, DownloadUnit &>(std::string & key, DownloadUnit & unit)
{
	return DownloadUnitTable_MEmplace(this, std::forward<std::string &>(key), std::forward<DownloadUnit &>(unit));
}
}

template<class R>
struct DownloadUnitReuseGen
{
	R & roan;
	template<class N> auto operator()(const N * n) const -> decltype(roan(n->_M_v())) { return roan(n->_M_v()); }
};

void DownloadUnitTable_MAssignAlloc(DownloadUnitTable * table, const std::__detail::_Hash_node_base & beforeBegin);

template<class G>
void DownloadUnitTable_MAssign(DownloadUnitTable * table, const std::__detail::_Hash_node_base & beforeBegin, const G & gen);

namespace std
{
template<>
DownloadUnitTable & DownloadUnitTable::operator=(const DownloadUnitTable & __ht)
{
	if (&__ht == this)
		return *this;
	if (__node_alloc_traits::_S_propagate_on_copy_assign())
	{
		auto & __this_alloc = this->_M_node_allocator();
		auto & __that_alloc = __ht._M_node_allocator();
		if (!__node_alloc_traits::_S_always_equal() && __this_alloc != __that_alloc)
		{
			this->_M_deallocate_nodes(_M_begin());
			_M_before_begin._M_nxt = nullptr;
			_M_deallocate_buckets();
			_M_buckets = nullptr;
			std::__alloc_on_copy(__this_alloc, __that_alloc);
			__hashtable_base::operator=(__ht);
			_M_bucket_count = __ht._M_bucket_count;
			_M_element_count = __ht._M_element_count;
			_M_rehash_policy = __ht._M_rehash_policy;
			DownloadUnitTable_MAssignAlloc(this, __ht._M_before_begin);
			return *this;
		}
		std::__alloc_on_copy(__this_alloc, __that_alloc);
	}
	__bucket_type * __former_buckets = nullptr;
	std::size_t __former_bucket_count = _M_bucket_count;
	const __rehash_state & __former_state = _M_rehash_policy._M_state();
	if (_M_bucket_count != __ht._M_bucket_count)
	{
		__former_buckets = _M_buckets;
		_M_buckets = _M_allocate_buckets(__ht._M_bucket_count);
		_M_bucket_count = __ht._M_bucket_count;
	}
	else
		__builtin_memset(_M_buckets, 0, _M_bucket_count * sizeof(__bucket_type));
	__hashtable_base::operator=(__ht);
	_M_element_count = __ht._M_element_count;
	_M_rehash_policy = __ht._M_rehash_policy;
	__reuse_or_alloc_node_type __roan(_M_begin(), *this);
	_M_before_begin._M_nxt = nullptr;
	DownloadUnitTable_MAssign(this, __ht._M_before_begin, DownloadUnitReuseGen<__reuse_or_alloc_node_type>{ __roan });
	if (__former_buckets)
		_M_deallocate_buckets(__former_buckets, __former_bucket_count);
	return *this;
}
}

void AssetsManagerEx::ContentDownloaderFinished()
{
}

bool AssetsManagerEx::decompress(const std::string & i_arg)
{
	return false;
}

AssetsManagerEx::AssetsManagerState AssetsManagerEx::getState() const
{
	return _updateState;
}

const std::string & AssetsManagerEx::getStoragePath() const
{
	return _storagePath;
}

const AssetsManagerManifest * AssetsManagerEx::getLocalManifest() const
{
	return _localManifest;
}

const AssetsManagerManifest * AssetsManagerEx::getRemoteManifest() const
{
	return _remoteManifest;
}

const DownloadUnits & AssetsManagerEx::getFailedAssets() const
{
	return _failedUnits;
}

bool AssetsManagerEx::isWaitToUpdate()
{
	return _waitToUpdate;
}

void AssetsManagerEx::setDelegate(AssetsManagerDelegateProtocol * delegate)
{
	_delegate = delegate;
}

void AssetsManagerEx::setRsbVersion(const std::string & rsbVersion)
{
	_rsbVersion = rsbVersion;
}

void AssetsManagerEx::downloadFailedAssets()
{
	updateAssets(_failedUnits);
}

void AssetsManagerEx::adjustPath(std::string & path)
{
	if (path.size() != 0 && path[path.size() - 1] != '/')
		path += "/";
}

void AssetsManagerEx::setStoragePath(const std::string & storagePath)
{
	_storagePath = storagePath;
	adjustPath(_storagePath);
	Sexy::MkDir(_storagePath);
}

void AssetsManagerEx::destroyDownloadedVersion()
{
	gSexyAppBase->EraseFile(_cacheVersionPath);
	gSexyAppBase->EraseFile(_cacheManifestPath);
}

std::string AssetsManagerEx::basename(const std::string & path) const
{
	size_t found = path.find_last_of("/\\");
	if (found != std::string::npos)
		return path.substr(0, found);
	return path;
}

void AssetsManagerEx::dispatchUpdateEvent(EventCode code, const std::string & message, const std::string & assetId, int curle_code, int curlm_code)
{
	if (_delegate)
		_delegate->dispatchEvent(this, code, _percent, _percentByFile, message, assetId, curle_code, curlm_code);
}

std::string AssetsManagerEx::get(const std::string & key) const
{
	auto it = _assets->find(key);
	if (it != _assets->end())
		return _storagePath + it->second.path;
	return "";
}

void AssetsManagerEx::ContentDownProgress(float i_progress)
{
	dispatchUpdateEvent(EventCode::UPDATE_PROGRESSION, "", Sexy::StrFormat("%d", (int)(i_progress * 100.0f)));
}

void AssetsManagerEx::ServiceRequestFailed(const Sexy::StructuredData *, const void * i_context)
{
	if (i_context == this)
	{
		if (_updateState == AssetsManagerState::DOWNLOADING_VERSION)
		{
			Sexy::OutputDebugStrF("AssetsManagerEx : Fail to download version file, step skipped\n");
			_updateState = AssetsManagerState::PREDOWNLOAD_MANIFEST;
			downloadManifest();
		}
		else if (_updateState == AssetsManagerState::DOWNLOADING_MANIFEST)
		{
			dispatchUpdateEvent(EventCode::ERROR_DOWNLOAD_MANIFEST, MANIFEST_ID, "");
		}
	}
}

void AssetsManagerEx::ServiceRequestCompleted(ImageLib::Image *&, const void * i_context)
{
}

void AssetsManagerEx::ServiceRequestCompleted(const Sexy::Buffer *, const void * i_context)
{
}

AssetsManagerEx::~AssetsManagerEx()
{
	if (_tempManifest != _localManifest && _tempManifest != _remoteManifest && _tempManifest != NULL)
	{
		delete _tempManifest;
		_tempManifest = NULL;
	}
	if (_localManifest != NULL)
	{
		delete _localManifest;
		_localManifest = NULL;
	}
	if (_remoteManifest != NULL)
	{
		delete _remoteManifest;
		_remoteManifest = NULL;
	}
}

void AssetsManagerEx::prepareLocalManifest()
{
	_assets = &_localManifest->getAssets();
	_localManifest->prependSearchPaths();
}

void AssetsManagerEx::onDownloadUnitsFinished()
{
	if (_failedUnits.size() != 0)
	{
		_tempManifest->saveToFile(_tempManifestPath);
		decompressDownloadedZip();
		_updateState = AssetsManagerState::FAIL_TO_UPDATE;
		dispatchUpdateEvent(EventCode::UPDATE_FAILED, "", "");
	}
	else
	{
		updateSucceed();
	}
}

void AssetsManagerEx::ContentDownloaderFailed(const DownloadPath & i_path, const std::string & i_errorMsg, int i_errorCode)
{
	auto unitIt = _downloadUnits.find(i_path.CustomId);
	if (unitIt != _downloadUnits.end())
	{
		_totalWaitToDownload--;
		DownloadUnit unit = unitIt->second;
		_failedUnits.emplace(unit.customId, unit);
	}
	dispatchUpdateEvent(EventCode::ERROR_UPDATING, i_path.CustomId, i_errorMsg, i_errorCode);
	if (_totalWaitToDownload <= 0)
		onDownloadUnitsFinished();
}

void AssetsManagerEx::downloadVersion()
{
	if (_updateState < AssetsManagerState::DOWNLOADING_VERSION)
	{
		std::string versionUrl = m_manifestUrl + _localManifest->getVersionFileUrl();
		if (versionUrl.size() != 0)
		{
			_updateState = AssetsManagerState::DOWNLOADING_VERSION;
			Sexy::StructuredData request;
			request.BeginObject();
			request.AddString("url", versionUrl);
			request.AddInteger("timeout", 20);
			request.EndObject();
			Sexy::NetworkServiceManager::DefaultNetworkServiceManager()->MakeRequest(&request, this, this);
		}
		else
		{
			Sexy::OutputDebugStrF("AssetsManagerEx : No version file found, step skipped\n");
			_updateState = AssetsManagerState::PREDOWNLOAD_MANIFEST;
			downloadManifest();
		}
	}
}

void AssetsManagerEx::updateSucceed()
{
	gSexyAppBase->RenameFile(_storagePath + "project.manifest.temp", _storagePath + "project.manifest");
	if (_localManifest)
		delete _localManifest;
	_localManifest = _remoteManifest;
	_remoteManifest = nullptr;
	prepareLocalManifest();
	_updateState = AssetsManagerState::UP_TO_DATE;
	dispatchUpdateEvent(EventCode::UPDATE_FINISHED, "", "");
}

void AssetsManagerEx::decompressDownloadedZip()
{
	for (auto it = _compressedFiles.begin(); it != _compressedFiles.end(); ++it)
	{
		std::string zipFile = *it;
		if (!decompress(zipFile))
			dispatchUpdateEvent(EventCode::ERROR_DECOMPRESS, "", "Unable to decompress file " + zipFile, 0, 0);
		gSexyAppBase->EraseFile(zipFile);
	}
	_compressedFiles.clear();
}

void AssetsManagerEx::updateAssets(const DownloadUnits & assets)
{
	if (!_inited)
	{
		Sexy::OutputDebugStrF("AssetsManagerEx : Manifests uninited.\n");
		dispatchUpdateEvent(EventCode::ERROR_NO_LOCAL_MANIFEST, "", "");
	}
	else if (_updateState != AssetsManagerState::UPDATING && _localManifest->isLoaded() && _remoteManifest->isLoaded())
	{
		int size = (int)assets.size();
		if (size > 0)
		{
			_updateState = AssetsManagerState::UPDATING;
			_downloadUnits.clear();
			_downloadUnits = assets;
			_totalWaitToDownload = _totalToDownload = (int)_downloadUnits.size();
			batchDownload();
		}
		else if (size == 0 && _totalWaitToDownload == 0)
		{
			updateSucceed();
		}
	}
}

void AssetsManagerEx::ServiceRequestCompleted(const Sexy::StructuredData * i_response, const void * i_context)
{
	if (i_context == this)
	{
		AssetsManagerEx * self = (AssetsManagerEx *)i_context;
		long long statusCode = i_response->IntegerForPath("$.statusCode", -1);
		if (statusCode == -1 || statusCode == 200)
		{
			if (self->_updateState == AssetsManagerState::DOWNLOADING_VERSION)
			{
				if (gSexyAppBase->FileExists(self->_cacheVersionPath))
					gSexyAppBase->EraseFile(self->_cacheVersionPath);
				Sexy::Buffer buffer;
				i_response->WriteToBuffer(&buffer);
				gSexyAppBase->WriteBufferToFile(self->_cacheVersionPath, &buffer);
				self->_updateState = AssetsManagerState::VERSION_LOADED;
				self->parseVersion();
			}
			else if (self->_updateState == AssetsManagerState::DOWNLOADING_MANIFEST)
			{
				if (__builtin_expect(gSexyAppBase->FileExists(self->_tempManifestPath), 0))
					gSexyAppBase->EraseFile(self->_tempManifestPath);
				Sexy::Buffer buffer;
				i_response->WriteToBuffer(&buffer);
				gSexyAppBase->WriteBufferToFile(self->_tempManifestPath, &buffer);
				self->_updateState = AssetsManagerState::MANIFEST_LOADED;
				self->parseManifest();
			}
		}
		else
		{
			ServiceRequestFailed(i_response, i_context);
		}
	}
}

void AssetsManagerEx::update()
{
	if (!_inited)
	{
		Sexy::OutputDebugStrF("AssetsManagerEx : Manifests uninited.\n");
		dispatchUpdateEvent(EventCode::ERROR_NO_LOCAL_MANIFEST, "", "");
		return;
	}
	if (!_localManifest->isLoaded())
	{
		Sexy::OutputDebugStrF("AssetsManagerEx : No local manifest file found error.\n");
		dispatchUpdateEvent(EventCode::ERROR_NO_LOCAL_MANIFEST, "", "");
		return;
	}
	_waitToUpdate = true;
	switch (_updateState)
	{
	case AssetsManagerState::UNCHECKED:
		_updateState = AssetsManagerState::PREVERSION_CHECK;
	case AssetsManagerState::PREVERSION_CHECK:
		versionCheck();
	case AssetsManagerState::PREDOWNLOAD_VERSION:
		downloadVersion();
		break;
	case AssetsManagerState::VERSION_LOADED:
		parseVersion();
		break;
	case AssetsManagerState::PREDOWNLOAD_MANIFEST:
		downloadManifest();
		break;
	case AssetsManagerState::MANIFEST_LOADED:
		parseManifest();
		break;
	case AssetsManagerState::NEED_UPDATE:
	case AssetsManagerState::FAIL_TO_UPDATE:
		if (!_remoteManifest->isLoaded())
		{
			_waitToUpdate = true;
			_updateState = AssetsManagerState::PREDOWNLOAD_MANIFEST;
			downloadManifest();
		}
		else
		{
			startUpdate();
		}
		break;
	case AssetsManagerState::UPDATING:
	case AssetsManagerState::UNZIPPING:
	case AssetsManagerState::UP_TO_DATE:
		_waitToUpdate = false;
		break;
	default:
		break;
	}
}

void AssetsManagerEx::versionCheck()
{
	if (_updateState < AssetsManagerState::VERSION_CHECK)
	{
		_updateState = AssetsManagerState::VERSION_CHECK;
		int localVersion = AssetsManagerManifest::getVersionToInt(_localManifest->getVersion());
		int rsbVersion = AssetsManagerManifest::getVersionToInt(_rsbVersion);
		if (localVersion < rsbVersion)
		{
			_updateState = AssetsManagerState::NEED_UPDATE;
			dispatchUpdateEvent(EventCode::NEW_VERSION_FOUND, "", "");
			if (_waitToUpdate)
			{
				_updateState = AssetsManagerState::PREDOWNLOAD_MANIFEST;
				downloadManifest();
			}
		}
		else
		{
			_updateState = AssetsManagerState::UP_TO_DATE;
			dispatchUpdateEvent(EventCode::ALREADY_UP_TO_DATE, "", "");
		}
	}
}

void AssetsManagerEx::downloadManifest()
{
	if (_updateState == AssetsManagerState::PREDOWNLOAD_MANIFEST)
	{
		std::string manifestUrl = m_manifestUrl + _rsbVersion + "/" + _localManifest->getManifestFileUrl();
		if (manifestUrl.size() != 0)
		{
			_updateState = AssetsManagerState::DOWNLOADING_MANIFEST;
			Sexy::StructuredData request;
			request.BeginObject();
			request.AddString("url", manifestUrl);
			request.AddInteger("timeout", 20);
			request.EndObject();
			Sexy::NetworkServiceManager::DefaultNetworkServiceManager()->MakeRequest(&request, this, this);
		}
		else
		{
			Sexy::OutputDebugStrF("AssetsManagerEx : No manifest file found, check update failed\n");
			dispatchUpdateEvent(EventCode::ERROR_DOWNLOAD_MANIFEST, "", "");
			_updateState = AssetsManagerState::UNCHECKED;
		}
	}
}

void AssetsManagerEx::batchDownload()
{
	std::vector<DownloadPath> paths;
	paths.clear();
	_downloader.Reset();
	for (auto it = _downloadUnits.begin(), end = _downloadUnits.end(); it != end; ++it)
	{
		std::pair<const std::string, DownloadUnit> unit = *it;
		DownloadPath path;
		path.URL = unit.second.srcUrl;
		path.SavePath = unit.second.storagePath;
		path.CustomId = unit.second.customId;
		paths.push_back(path);
		std::string log = Sexy::StrFormat("BatchDownload %s", path.URL.c_str());
		gDebugLog->SendLog(log, DebugLog_NetMessage, DebugPath_File | DebugPath_NetWork);
	}
	_downloader.StartDownload(paths);
}

void AssetsManagerEx::checkUpdate()
{
	if (!_inited)
	{
		Sexy::OutputDebugStrF("AssetsManagerEx : Manifests uninited.\n");
		dispatchUpdateEvent(EventCode::ERROR_NO_LOCAL_MANIFEST, "", "");
		return;
	}
	if (!_localManifest->isLoaded())
	{
		Sexy::OutputDebugStrF("AssetsManagerEx : No local manifest file found error.\n");
		dispatchUpdateEvent(EventCode::ERROR_NO_LOCAL_MANIFEST, "", "");
		return;
	}
	switch (_updateState)
	{
	case AssetsManagerState::UNCHECKED:
	case AssetsManagerState::PREVERSION_CHECK:
		versionCheck();
		break;
	case AssetsManagerState::PREDOWNLOAD_VERSION:
		downloadVersion();
		break;
	case AssetsManagerState::NEED_UPDATE:
	case AssetsManagerState::FAIL_TO_UPDATE:
		dispatchUpdateEvent(EventCode::NEW_VERSION_FOUND, "", "");
		break;
	case AssetsManagerState::UP_TO_DATE:
		dispatchUpdateEvent(EventCode::ALREADY_UP_TO_DATE, "", "");
		break;
	default:
		break;
	}
}

void AssetsManagerEx::initManifests(const std::string & manifestUrl)
{
	_inited = true;
	_localManifest = new (std::nothrow) AssetsManagerManifest("");
	if (!_localManifest)
	{
		_inited = false;
	}
	else
	{
		loadLocalManifest(manifestUrl);
		_tempManifest = new (std::nothrow) AssetsManagerManifest("");
		if (!_tempManifest)
		{
			_inited = false;
		}
		else
		{
			_tempManifest->parse(_tempManifestPath);
			if (!_tempManifest->isLoaded() && gSexyAppBase->FileExists(_tempManifestPath))
				gSexyAppBase->EraseFile(_tempManifestPath);
		}
		_remoteManifest = new (std::nothrow) AssetsManagerManifest("");
		if (!_remoteManifest)
			_inited = false;
	}
	if (!_inited)
	{
		if (_localManifest)
		{
			delete _localManifest;
			_localManifest = nullptr;
		}
		if (_tempManifest)
		{
			delete _tempManifest;
			_tempManifest = nullptr;
		}
		if (_remoteManifest)
		{
			delete _remoteManifest;
			_remoteManifest = nullptr;
		}
	}
}

void AssetsManagerEx::parseVersion()
{
	if (_updateState == AssetsManagerState::VERSION_LOADED)
	{
		_remoteManifest->parseVersion(_cacheVersionPath, _rsbVersion);
		if (!_remoteManifest->isVersionLoaded())
		{
			Sexy::OutputDebugStrF("AssetsManagerEx : Fail to parse version file, step skipped\n");
			_updateState = AssetsManagerState::PREDOWNLOAD_MANIFEST;
			downloadManifest();
		}
		else
		{
			int localVersion = AssetsManagerManifest::getVersionToInt(_localManifest->getVersion());
			int remoteVersion = AssetsManagerManifest::getVersionToInt(_remoteManifest->getVersion());
			if (localVersion < remoteVersion)
			{
				_updateState = AssetsManagerState::NEED_UPDATE;
				dispatchUpdateEvent(EventCode::NEW_VERSION_FOUND, "", "");
				gMessageRouter->Post(&Message::NewVersionFound);
				if (_waitToUpdate)
				{
					_updateState = AssetsManagerState::PREDOWNLOAD_MANIFEST;
					downloadManifest();
				}
			}
			else
			{
				_updateState = AssetsManagerState::UP_TO_DATE;
				dispatchUpdateEvent(EventCode::ALREADY_UP_TO_DATE, "", "");
			}
		}
	}
}

void AssetsManagerEx::parseManifest()
{
	if (_updateState == AssetsManagerState::MANIFEST_LOADED)
	{
		_remoteManifest->parse(_tempManifestPath);
		if (!_remoteManifest->isLoaded())
		{
			Sexy::OutputDebugStrF("AssetsManagerEx : Error parsing manifest file\n");
			dispatchUpdateEvent(EventCode::ERROR_PARSE_MANIFEST, "", "");
			_updateState = AssetsManagerState::UNCHECKED;
		}
		else
		{
			int localVersion = AssetsManagerManifest::getVersionToInt(_localManifest->getVersion());
			int remoteVersion = AssetsManagerManifest::getVersionToInt(_remoteManifest->getVersion());
			if (localVersion < remoteVersion)
			{
				_updateState = AssetsManagerState::NEED_UPDATE;
				dispatchUpdateEvent(EventCode::NEW_VERSION_FOUND, "", "");
				if (_waitToUpdate)
					startUpdate();
			}
			else
			{
				_updateState = AssetsManagerState::UP_TO_DATE;
				dispatchUpdateEvent(EventCode::ALREADY_UP_TO_DATE, "", "");
			}
		}
	}
}

void AssetsManagerEx::loadLocalManifest(const std::string & manifestUrl)
{
	AssetsManagerManifest * cachedManifest = nullptr;
	if (gSexyAppBase->FileExists(_cacheManifestPath))
	{
		cachedManifest = new (std::nothrow) AssetsManagerManifest("");
		if (cachedManifest)
		{
			cachedManifest->parse(_cacheManifestPath);
			if (!cachedManifest->isLoaded())
			{
				gSexyAppBase->EraseFile(_cacheManifestPath);
				delete cachedManifest;
				cachedManifest = nullptr;
			}
		}
	}
	_localManifest->parse(_manifestUrl);
	if (!_localManifest->isLoaded())
		goto check;
	if (cachedManifest)
	{
		if (strcmp(_localManifest->getVersion().c_str(), cachedManifest->getVersion().c_str()) > 0)
		{
			Sexy::Deltree(_storagePath);
			Sexy::MkDir(_storagePath);
			delete cachedManifest;
		}
		else
		{
			delete _localManifest;
			_localManifest = cachedManifest;
			prepareLocalManifest();
			goto check;
		}
	}
	prepareLocalManifest();
check:
	if (!_localManifest->isLoaded())
	{
		Sexy::OutputDebugStrF("AssetsManagerEx : No local manifest file found error.\n");
		dispatchUpdateEvent(EventCode::ERROR_NO_LOCAL_MANIFEST, "", "");
	}
}

void AssetsManagerEx::FileDownloadSuccess(const DownloadPath & i_path)
{
	const std::string & key = i_path.CustomId;
	const auto & assets = _remoteManifest->getAssets();
	auto assetIt = assets.find(key);
	if (assetIt != assets.end())
	{
		std::string md5 = "";
		Sexy::Buffer buffer;
		if (gSexyAppBase->ReadBufferFromFile(i_path.SavePath, &buffer))
		{
			MD5 digest(buffer.GetDataPtr(), buffer.GetDataLen());
			md5 = digest.toString();
		}
		if (assetIt->second.md5 != md5)
		{
			gSexyAppBase->EraseFile(i_path.SavePath);
			dispatchUpdateEvent(EventCode::ERROR_MD5, "", "");
			return;
		}
		_tempManifest->setAssetDownloadState(key, AssetsManagerManifest::DownloadState::SUCCESSED);
		if (assetIt->second.compressed)
			_compressedFiles.push_back(i_path.SavePath);
	}
	auto it = _downloadUnits.find(key);
	if (it != _downloadUnits.end())
	{
		_totalWaitToDownload--;
		_percentByFile = (float)(_totalToDownload - _totalWaitToDownload) * 100.0f / (float)_totalToDownload;
	}
	dispatchUpdateEvent(EventCode::ASSET_UPDATED, key, "");
	it = _failedUnits.find(key);
	if (it != _failedUnits.end())
		_failedUnits.erase(it);
	if (_totalWaitToDownload <= 0)
		onDownloadUnitsFinished();
}

AssetsManagerEx::AssetsManagerEx(const std::string & manifestUrl, const std::string & storagePath)
	: _delegate(nullptr)
	, _updateState(AssetsManagerState::UNCHECKED)
	, _assets(nullptr)
	, _storagePath("")
	, _cacheVersionPath("")
	, _cacheManifestPath("")
	, _tempManifestPath("")
	, _manifestUrl(manifestUrl)
	, _localManifest(nullptr)
	, _tempManifest(nullptr)
	, _remoteManifest(nullptr)
	, _waitToUpdate(false)
	, _percent(0)
	, _percentByFile(0)
	, _totalToDownload(0)
	, _totalWaitToDownload(0)
	, _inited(false)
	, _rsbVersion("0")
{
	m_manifestUrl = "http://profile.pvz2ios.popcap.com.cn/new_pvz2_ios/";
	m_cdnUrl = "http://download.pvz2ios.popcap.com.cn/";
	std::string version("default");
	version = Sexy::StrFormat("%d", Android::Info::SysGetProductVersionCode());
	version += "_HD";
	m_manifestUrl += version;
	m_cdnUrl += version;
	m_manifestUrl += "/";
	m_cdnUrl += "/";
	_updateState = AssetsManagerState::UNCHECKED;
	_downloader.setDelegate(this);
	setStoragePath(storagePath);
	_cacheVersionPath = _storagePath + "version.manifest";
	_cacheManifestPath = _storagePath + "project.manifest";
	_tempManifestPath = _storagePath + "project.manifest.temp";
	_totalEnabled = 0;
	_sizeCollected = 0;
	_totalSize = 0;
	initManifests(manifestUrl);
}

void AssetsManagerEx::startUpdate()
{
	if (_updateState == AssetsManagerState::NEED_UPDATE)
	{
		_updateState = AssetsManagerState::UPDATING;
		_failedUnits.clear();
		_downloadUnits.clear();
		_compressedFiles.clear();
		_totalToDownload = 0;
		_totalWaitToDownload = 0;
		_sizeCollected = 0;
		_percentByFile = 0;
		_totalSize = 0;
		_percent = 0;
		_downloadedSize.clear();
		_totalEnabled = 0;
		if (!_tempManifest->isLoaded() || !_tempManifest->versionEquals(_remoteManifest))
		{
			delete _tempManifest;
			_tempManifest = _remoteManifest;
			{
			std::unordered_map<std::string, AssetsManagerManifest::AssetDiff> diffMap = _localManifest->genDiff(_remoteManifest);
			if (diffMap.size() == 0)
			{
				updateSucceed();
			}
			else
			{
				std::string packageUrl = _remoteManifest->getPackageUrl();
				for (auto it = diffMap.begin(); it != diffMap.end(); ++it)
				{
					AssetsManagerManifest::AssetDiff diff = it->second;
					if (diff.type == AssetsManagerManifest::DiffType::DELETED)
					{
						gSexyAppBase->EraseFile(_storagePath + diff.asset.path);
					}
					else
					{
						std::string path = diff.asset.path;
						Sexy::MkDir(basename(_storagePath + path));
						DownloadUnit unit;
						unit.customId = it->first;
						unit.srcUrl = m_cdnUrl + _rsbVersion + "/" + packageUrl + path;
						unit.storagePath = _storagePath + path;
						_downloadUnits.emplace(unit.customId, unit);
					}
				}
				const auto & assets = _remoteManifest->getAssets();
				for (auto it = assets.cbegin(); it != assets.cend(); ++it)
				{
					const std::string & key = it->first;
					if (diffMap.find(key) == diffMap.end())
						_tempManifest->setAssetDownloadState(key, AssetsManagerManifest::DownloadState::SUCCESSED);
				}
				_totalWaitToDownload = _totalToDownload = (int)_downloadUnits.size();
				batchDownload();
			}
			}
			_waitToUpdate = false;
		}
		else
		{
			_tempManifest->genResumeAssetsList(&_downloadUnits, m_cdnUrl, _rsbVersion);
			_totalWaitToDownload = _totalToDownload = (int)_downloadUnits.size();
			batchDownload();
			_waitToUpdate = false;
		}
	}
}
