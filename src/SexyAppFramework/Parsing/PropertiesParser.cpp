//
//  PropertiesParser.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-11-21.
//
#include "SexyAppFramework/Common.h"
#include "PropertiesParser.h"
#include "XMLParser.h"
#include "Buffer.h"

using namespace Sexy;

/////////////// Lifecycle ///////////////

PropertiesParser::PropertiesParser( SexyAppBase* theApp )
{
	mHasFailed = false;
	mApp = theApp;
	mXMLParser = NULL;
}

PropertiesParser::~PropertiesParser()
{
}

/////////////// Accessors ///////////////

SexyString PropertiesParser::GetErrorText()
{
	return mError;
}

/////////////// Parsing ///////////////

void PropertiesParser::Fail( const SexyString& theErrorText )
{
	if ( !mHasFailed )
	{
		mHasFailed = true;
		int aLineNum = mXMLParser->GetCurrentLineNum();
		mError = theErrorText;
		if ( aLineNum > 0 )
			mError += StrFormat( _S( " on Line %d" ), aLineNum );
		if ( !mXMLParser->GetFileName().empty() )
			mError += StrFormat( _S( " in File '%s'" ), ToSexyString( mXMLParser->GetFileName() ).c_str() );
	}
}

bool PropertiesParser::ParseSingleElement( SexyString* theString )
{
	*theString = _S( "" );
	bool aResult;
	for ( ;; )
	{
		XMLElement aXMLElement;
		aResult = mXMLParser->NextElement( &aXMLElement );
		if ( !aResult )
			break;
		if ( aXMLElement.mType == XMLElement::TYPE_START )
		{
			aResult = false;
			Fail( _S( "Unexpected Section: '" ) + aXMLElement.mValue + _S( "'" ) );
			break;
		}
		else if ( aXMLElement.mType == XMLElement::TYPE_ELEMENT )
		{
			*theString = aXMLElement.mValue;
		}
		else if ( aXMLElement.mType == XMLElement::TYPE_END )
		{
			break;
		}
	}
	return aResult;
}

bool PropertiesParser::ParseStringArray( StringVector* theStringVector )
{
	theStringVector->clear();
	bool aResult;
	for ( ;; )
	{
		XMLElement aXMLElement;
		aResult = mXMLParser->NextElement( &aXMLElement );
		if ( !aResult )
			break;
		if ( aXMLElement.mType == XMLElement::TYPE_START )
		{
			if ( aXMLElement.mValue == _S( "String" ) )
			{
				SexyString aString;
				aResult = ParseSingleElement( &aString );
				if ( !aResult )
					break;
				theStringVector->push_back( WStringToString( aString ) );
			}
			else
			{
				aResult = false;
				Fail( _S( "Invalid Section '" ) + aXMLElement.mValue + _S( "'" ) );
				break;
			}
		}
		else if ( aXMLElement.mType == XMLElement::TYPE_ELEMENT )
		{
			aResult = false;
			Fail( _S( "Element Not Expected '" ) + aXMLElement.mValue + _S( "'" ) );
			break;
		}
		else if ( aXMLElement.mType == XMLElement::TYPE_END )
		{
			break;
		}
	}
	return aResult;
}

bool PropertiesParser::DoParseProperties()
{
	if ( !mXMLParser->HasFailed() )
	{
		for ( ;; )
		{
			XMLElement aXMLElement;
			if ( !mXMLParser->NextElement( &aXMLElement ) )
				break;
			if ( aXMLElement.mType == XMLElement::TYPE_START )
			{
				if ( aXMLElement.mValue == _S( "Properties" ) )
				{
					if ( !ParseProperties() )
						break;
				}
				else
				{
					Fail( _S( "Invalid Section '" ) + aXMLElement.mValue + _S( "'" ) );
					break;
				}
			}
			else if ( aXMLElement.mType == XMLElement::TYPE_ELEMENT )
			{
				Fail( _S( "Element Not Expected '" ) + aXMLElement.mValue + _S( "'" ) );
				break;
			}
		}
	}
	if ( mXMLParser->HasFailed() )
		Fail( mXMLParser->GetErrorText() );
	delete mXMLParser;
	mXMLParser = NULL;
	return !mHasFailed;
}

bool PropertiesParser::ParsePropertiesFile( const std::string& theFilename )
{
	mXMLParser = new XMLParser();
	mXMLParser->OpenFile( theFilename );
	return DoParseProperties();
}

bool PropertiesParser::ParsePropertiesBuffer( const Buffer& theBuffer )
{
	mXMLParser = new XMLParser();
	mXMLParser->SetStringSource( theBuffer.UTF8ToWideString() );
	return DoParseProperties();
}
