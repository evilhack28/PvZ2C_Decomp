//
//  FileUtil.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-04.
//

#include "SexyAppFramework/Common.h"

#include <time.h>

#include "FileUtil.h"

struct FileCloser
{
	void operator()(FILE* i_file)
	{
		fclose(i_file);
	}
};

/////////////// FileUtil ///////////////

std::shared_ptr<FILE> FileUtil::openFile(const std::string& i_name, const std::string& i_mode)
{
	return std::shared_ptr<FILE>(fopen(i_name.c_str(), i_mode.c_str()), FileCloser());
}

void FileUtil::writeFile(const std::shared_ptr<FILE>& i_file, const std::string& i_content)
{
	if (i_file)
	{
		fwrite(i_content.c_str(), 1, i_content.size(), i_file.get());
	}
}

bool FileUtil::readFile(const std::shared_ptr<FILE>& i_file, std::string& i_content)
{
	bool result = (bool)i_file;
	if (result)
	{
		fseek(i_file.get(), 0, SEEK_END);
		long size = ftell(i_file.get());
		fseek(i_file.get(), 0, SEEK_SET);

		char* buffer = new char[size];
		fread(buffer, 1, size, i_file.get());
		i_content = std::string(buffer, size);
		delete[] buffer;
	}
	return result;
}

std::string FileUtil::getTimeStr()
{
	time_t now = time(NULL);
	return std::string(ctime(&now));
}
