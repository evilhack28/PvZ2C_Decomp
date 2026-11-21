//
//  DIniFile.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-11-21.
//

#include "SexyAppFramework/Common.h"

#include "DIniFile.h"

/////////////// Lifecycle ///////////////

DIniFile::DIniFile()
{
}

/////////////// Logic ///////////////

DIniField* DIniFile::getField(const std::string& fieldName)
{
	std::map<std::string, DIniField>::iterator it = m_fieldList.find(fieldName);
	if (it != m_fieldList.end())
		return &(*it).second;

	return NULL;
}
