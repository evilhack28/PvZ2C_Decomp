//
//  PackageContentsProvider.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-05.
//

#include "SexyAppFramework/Common.h"

#include "PackageContentsProvider.h"

#include <algorithm>
#include <deque>
#include <string.h>

#include "GameEventMgr.h"
#include "RtSerial.h"
#include "SexyAppBase.h"
#include "ResStreamsManager.h"

using namespace Sexy;

/////////////// PackageContentsProvider ///////////////

PackageContentsProvider::PackageContentsProvider(const std::string& i_defaultPackagePath, const std::string& i_overridePackagePath)
	: m_defaultPackagePath(i_defaultPackagePath)
	, m_overridePackagePath(i_overridePackagePath)
{
}

PackageContentsProvider::~PackageContentsProvider() = default;

static bool isPathSeparator(char i_char)
{
	std::vector<char> separators = { '\x5c', '/' };
	return std::find(separators.begin(), separators.end(), i_char) != separators.end();
}

std::string PackageContentsProvider::cleanPackagePath(const std::string& i_packagePath) const
{
	return Sexy::Trim(Sexy::Lower(i_packagePath));
}

std::string PackageContentsProvider::cleanAbsolutePath(const std::string& i_path) const
{
	std::string normalized = gFileDriver->FixPath(i_path);
	std::string result;
	bool lastWasSeparator = false;
	for (size_t i = 0; i < normalized.size(); i++)
	{
		char c = normalized[i];
		bool isSeparator = isPathSeparator(c);
		if (lastWasSeparator && isSeparator)
			lastWasSeparator = true;
		else
		{
			result.push_back(c);
			lastWasSeparator = isSeparator;
		}
	}

	for (int i = (int)result.size() - 1; i >= 0; i--)
	{
		if (!isPathSeparator(result[i]))
			break;

		result.erase(result.begin() + i);
	}

	result = Sexy::Trim(result);
	return result;
}

std::string PackageContentsProvider::getDefaultPackagePath(const std::string& i_packagePath) const
{
	std::string packagePath = cleanPackagePath(i_packagePath);
	std::string absolutePath = m_defaultPackagePath + '\x5c' + packagePath + ".rton";
	return cleanAbsolutePath(absolutePath);
}

std::string PackageContentsProvider::getOverridePackagePath(const std::string& i_packagePath) const
{
	std::string packagePath = cleanPackagePath(i_packagePath);
	std::string absolutePath = m_overridePackagePath + '\x5c' + packagePath + ".rton";
	return cleanAbsolutePath(absolutePath);
}

std::string PackageContentsProvider::getPackagePathFromAbsoluteDefaultPath(const std::string& i_absolutePath) const
{
	std::string result = cleanAbsolutePath(i_absolutePath);
	for (int i = (int)result.length() - 1; i >= 0; i--)
	{
		if (result[i] == '.')
		{
			result.erase(result.begin() + i, result.end());
			break;
		}
	}

	std::string prefix = cleanAbsolutePath(m_defaultPackagePath);
	if (strstr(result.c_str(), prefix.c_str()) == result.c_str())
		result.erase(result.begin() + prefix.length(), result.end());

	return result;
}

std::string PackageContentsProvider::getPackagePathFromAbsoluteOverridePath(const std::string& i_absolutePath) const
{
	std::string result = cleanAbsolutePath(i_absolutePath);
	for (int i = (int)result.length() - 1; i >= 0; i--)
	{
		if (result[i] == '.')
		{
			result.erase(result.begin() + i, result.end());
			break;
		}
	}

	std::string prefix = cleanAbsolutePath(m_overridePackagePath);
	if (strstr(result.c_str(), prefix.c_str()) == result.c_str())
		result.erase(result.begin(), result.begin() + prefix.length() + 1);

	return result;
}

bool PackageContentsProvider::findDefaultPackageFor(const std::string& i_packagePath, std::string& o_defaultPath) const
{
	std::string packagePath = cleanPackagePath(i_packagePath);
	std::string defaultPath = getDefaultPackagePath(packagePath);
	if (gSexyAppBase->mResStreamsManager != NULL && gSexyAppBase->mResStreamsManager->IsInitialized("dynamic.rsb"))
	{
		uint32 group = gSexyAppBase->mResStreamsManager->GetGroupForFile(defaultPath, true, true);
		if (group != 0xffffffff)
		{
			uint8* buffer = NULL;
			uint32 size;
			bool found = gSexyAppBase->mResStreamsManager->GetResidentFileBuffer(group, defaultPath, &buffer, &size);
			if (found)
				o_defaultPath = defaultPath;

			return found;
		}
	}

	return false;
}

bool PackageContentsProvider::findOverridePackageFor(const std::string& i_packagePath, std::string& o_overridePath) const
{
	std::string packagePath = cleanPackagePath(i_packagePath);
	std::string overridePath = getOverridePackagePath(packagePath);
	bool result = false;
	if (gSexyAppBase->FileExists(overridePath))
	{
		o_overridePath = overridePath;
		result = true;
	}

	return result;
}

bool PackageContentsProvider::GetPackageContentsPath(const std::string& i_packagePath, std::string& o_absolutePath) const
{
	std::string packagePath = cleanPackagePath(i_packagePath);
	bool result = true;
	if (!findOverridePackageFor(packagePath, o_absolutePath))
		result = findDefaultPackageFor(packagePath, o_absolutePath);

	return result;
}

bool PackageContentsProvider::OverridePackageContentsWithJSON(const std::string& i_packagePath, const std::string& i_newJSON) const
{
	std::string packagePath = cleanPackagePath(i_packagePath);
	Sexy::RtSerialBuffer buffer(NULL, 0);
	Sexy::RtSerialRtonWriter writer(&buffer);
	std::string error;
	bool result = Sexy::RtSerial::JsonToRton(i_newJSON.c_str(), writer, error);
	if (result)
	{
		std::string overridePath = getOverridePackagePath(packagePath);
		if (!gSexyAppBase->WriteBytesToFile(overridePath, buffer.GetDataPtr(), buffer.GetDataSize()))
		{
			result = false;
		}
		else
		{
			gMessageRouter->Broadcast(Message::PackageContentsChanged, packagePath);
		}
	}

	return result;
}

bool PackageContentsProvider::ClearOverridePackageFor(const std::string& i_packagePath) const
{
	std::string packagePath = cleanPackagePath(i_packagePath);
	std::string overridePath;
	bool result = false;
	if (findOverridePackageFor(packagePath, overridePath))
	{
		if (gSexyAppBase->EraseFile(overridePath))
		{
			result = true;
			gMessageRouter->Broadcast(Message::PackageContentsChanged, packagePath);
		}
	}

	return result;
}

void PackageContentsProvider::ClearOverridePackageFolder() const
{
	std::deque<std::string> folders;
	folders.push_back(m_overridePackagePath);
	do
	{
		std::string folder = folders.front();
		folders.pop_front();

		IFileDriver* driver = gSexyAppBase->mFileDriver;
		FileSearchInfo info;
		std::string criteria = folder + '/';
		IFileSearch* search = driver->FileSearchStart(criteria, &info);
		if (search == NULL)
			break;

		bool more = true;
		while (more)
		{
			if (!(info.file_name == "." || info.file_name == ".."))
			{
				std::string path = criteria + info.file_name;
				if (info.is_directory)
					folders.push_back(path);
				else
					ClearOverridePackageFor(getPackagePathFromAbsoluteOverridePath(path));
			}

			more = driver->FileSearchNext(search, &info);
		}

		driver->FileSearchEnd(search);
	} while (!folders.empty());
}
