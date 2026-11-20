//
//  DValue.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-11-20.
//

#include "SexyAppFramework/Common.h"

#include "DNode/DValue.h"

#include <new>
#include <sstream>
#include <iomanip>

/////////////// Lifecycle ///////////////

DValue::DValue(const std::string& v)
{
	_type = Type::STRING;
	_field.strVal = new std::string();
	*_field.strVal = v;
}

DValue::DValue(DValue&& v)
	: _type(Type::NONE)
{
	*this = std::move(v);
}

/////////////// Type management ///////////////

void DValue::reset(Type type)
{
	if (_type == type)
		return;

	clear();
	switch (type)
	{
	case Type::STRING:
		_field.strVal = new std::string();
		break;
	case Type::VECTOR:
		_field.vectorVal = new (std::nothrow) DValueVector();
		break;
	case Type::MAP:
		_field.mapVal = new (std::nothrow) DValueMap();
		break;
	case Type::INT_KEY_MAP:
		_field.intKeyMapVal = new (std::nothrow) DValueMapIntKey();
		break;
	}
	_type = type;
}

/////////////// Assignment ///////////////

DValue& DValue::operator=(const std::string& v)
{
	reset(Type::STRING);
	*_field.strVal = v;
	return *this;
}

DValue& DValue::operator=(const DValueMap& v)
{
	reset(Type::MAP);
	*_field.mapVal = v;
	return *this;
}

DValue& DValue::operator=(const DValueMapIntKey& v)
{
	reset(Type::INT_KEY_MAP);
	*_field.intKeyMapVal = v;
	return *this;
}

std::string DValue::asString() const
{
	if (_type == Type::STRING)
		return *_field.strVal;

	std::stringstream aStream(std::ios::out | std::ios::in);
	switch (_type)
	{
	case Type::BYTE:
		aStream << (char)_field.byteVal;
		break;
	case Type::INTEGER:
		aStream << _field.intVal;
		break;
	case Type::FLOAT:
		aStream << std::fixed << std::setprecision(7) << _field.floatVal;
		break;
	case Type::DOUBLE:
		aStream << std::fixed << std::setprecision(16) << _field.doubleVal;
		break;
	case Type::INTEGER64:
		aStream << _field.int64Val;
		break;
	case Type::BOOLEAN:
		aStream << (_field.boolVal ? "true" : "false");
		break;
	}
	return aStream.str();
}
