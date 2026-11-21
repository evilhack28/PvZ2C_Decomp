//
//  JsonWriter.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-11-21.
//
#include "SexyAppFramework/Common.h"
#include "JsonWriter.h"
#include "Buffer.h"
#include <sstream>
#include <iomanip>
#include <ctype.h>
#include <string.h>

using namespace Sexy;

/////////////// Lifecycle ///////////////

JsonWriter::JsonWriter()
{
	SetOutputFormat( COMPACT );
}

JsonWriter::JsonWriter( Format format )
{
	SetOutputFormat( format );
}

/////////////// Output ///////////////

void JsonWriter::SetOutputFormat( Format format )
{
	if ( format == COMPACT )
	{
		mNameSeparator = ":";
		mFieldTerminator = "";
		mIndentation = "";
	}
	else
	{
		mNameSeparator = " : ";
		mFieldTerminator = "\n";
		mIndentation = "   ";
	}
}

void JsonWriter::Write( std::ostream& os, const StructuredData::Value* root, bool i_addQuote ) const
{
	Write( os, root, "", false, i_addQuote );
	os << mFieldTerminator;
}

void JsonWriter::Write( Buffer* outputBuffer, const StructuredData::Value* root ) const
{
	std::ostringstream os( std::ios_base::out );
	Write( os, root, true );
	std::string str = os.str();
	outputBuffer->SetData( (const uchar*)&str[0], str.length() );
}

void JsonWriter::Write( std::ostream& os, const StructuredData::Value* root, std::string prefix, bool writeName, bool i_addQuote ) const
{
	os << prefix;
	if ( writeName && root->HasName() )
		os << '"' << root->Name() << '"' << mNameSeparator;
	switch ( root->Type() )
	{
	case StructuredData::SD_JSON:
		os << root->GetJSON();
		break;
	case StructuredData::SD_BOOLEAN:
		os << ( root->GetBoolean() ? "true" : "false" );
		break;
	case StructuredData::SD_ARRAY:
	{
		const StructuredData::Value* child = root->FirstChild();
		os << "[" << mFieldTerminator;
		for ( uint32 i = 0; i < root->ChildCount(); ++i )
		{
			Write( os, child, prefix + mIndentation, true, true );
			if ( i + 1 < root->ChildCount() )
				os << ",";
			os << mFieldTerminator;
			child = child->Next();
		}
		os << prefix << "]";
		break;
	}
	case StructuredData::SD_NULL:
		os << "null";
		break;
	case StructuredData::SD_STRING:
		WriteString( os, root->GetString(), i_addQuote );
		break;
	case StructuredData::SD_NUMBER:
		os << root->GetNumber();
		break;
	case StructuredData::SD_INTEGER:
		os << root->GetInteger();
		break;
	case StructuredData::SD_OBJECT:
	{
		const StructuredData::Value* child = root->FirstChild();
		os << "{" << mFieldTerminator;
		for ( uint32 i = 0; i < root->ChildCount(); ++i )
		{
			Write( os, child, prefix + mIndentation, true, true );
			if ( i + 1 < root->ChildCount() )
				os << ",";
			os << mFieldTerminator;
			child = child->Next();
		}
		os << prefix << "}";
		break;
	}
	}
}
