//
//  DString.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-11-21.
//

#include "SexyAppFramework/Common.h"

#include "DString.h"
#include "DStackAllocator.h"

class DStringBlock
{
public:
	DStringBlock(const char* src);
	DStringBlock(const char* src, size_t len);
	~DStringBlock();

	void resetMemory(size_t len);
	void release();
	void retain() { m_refCount++; }
	DStringBlock* addString(const char* src);

	size_t m_capacity;
	size_t m_length;
	char* m_data;
	int m_refCount;
};

/////////////// DStringBlock ///////////////

DStringBlock::DStringBlock(const char* src)
	: m_capacity(0)
	, m_length(0)
	, m_data(NULL)
	, m_refCount(1)
{
	if (src)
	{
		size_t len = strlen(src);
		resetMemory(len);
		if (len)
			memcpy(m_data, src, len);
		m_data[len] = 0;
		m_length = len;
		m_capacity = len;
	}
}

DStringBlock::DStringBlock(const char* src, size_t len)
	: m_capacity(0)
	, m_length(0)
	, m_data(NULL)
	, m_refCount(1)
{
	if (src)
	{
		resetMemory(len);
		if (len)
			memcpy(m_data, src, len);
		m_data[len] = 0;
		m_length = len;
		m_capacity = len;
	}
}

DStringBlock::~DStringBlock()
{
	if (m_data)
		free(m_data);
}

void DStringBlock::resetMemory(size_t len)
{
	if (m_capacity <= len)
	{
		size_t aNewCapacity = (len + 0xff) & ~(size_t)0xff;
		if (m_capacity <= aNewCapacity)
		{
			if (m_data)
			{
				m_capacity = aNewCapacity;
				m_data = (char*)realloc(m_data, aNewCapacity + 1);
			}
			else
			{
				m_length = len;
				m_capacity = len;
				m_data = (char*)malloc(len + 1);
			}
		}
	}
}

void DStringBlock::release()
{
	if (--m_refCount == 0)
		delete this;
}

/////////////// DString ///////////////

DString::DString()
	: str(NULL)
{
}

DString::~DString()
{
	if (str)
		str->release();
}

DString::DString(char src)
	: str(NULL)
{
	char aBuffer[2];
	aBuffer[0] = src;
	aBuffer[1] = 0;
	newString(aBuffer);
}

DString::DString(const int v)
	: str(NULL)
{
	format("%d", v);
}

DString::DString(const long src)
	: str(NULL)
{
	format("%ld", src);
}

DString::DString(const double src)
	: str(NULL)
{
	format("%lf", src);
}

DString::DString(const long long src)
	: str(NULL)
{
	format("%lld", src);
}

DString::DString(const float v)
	: str(NULL)
{
	format("%f", v);
}

DString::DString(const char* src)
	: str(NULL)
{
	newString(src);
}

DString::DString(const char* src, size_t len)
	: str(NULL)
{
	newString(src, len);
}

void DString::newString(const char* src)
{
	if (str)
	{
		str->release();
		str = NULL;
	}
	str = new DStringBlock(src);
}

void DString::newString(const char* src, size_t newLen)
{
	if (str)
	{
		str->release();
		str = NULL;
	}
	str = new DStringBlock(src, newLen);
}

/////////////// Format ///////////////

void DString::initWithFormatAndValist(const char* format, va_list list)
{
	char* aBuffer = (char*)DStackAllocator::getInstance()->push(0x2800);
	vsprintf(aBuffer, format, list);
	newString(aBuffer);
	DStackAllocator::getInstance()->pop();
}

DString& DString::format(const char* _format, ...)
{
	va_list aList;
	va_start(aList, _format);
	initWithFormatAndValist(_format, aList);
	va_end(aList);
	return *this;
}

DString DString::Format(const char* _format, ...)
{
	DString aResult;
	va_list aList;
	va_start(aList, _format);
	aResult.initWithFormatAndValist(_format, aList);
	va_end(aList);
	return aResult;
}

__attribute__((noclone, noinline)) static char* DStringBlockData(char* i_data)
{
	return i_data;
}

char* DString::c_str()
{
	if (str)
		return DStringBlockData(str->m_data);
	return "";
}

__attribute__((noclone, noinline)) static size_t DStringBlockLength(size_t i_length)
{
	return i_length;
}

bool DString::empty() const
{
	if (!str)
		return true;
	return DStringBlockLength(str->m_length) == 0;
}

size_t DString::size() const
{
	return DStringBlockLength(str->m_length);
}

ssize_t DString::findString(ssize_t start, const char* sub) const
{
	char* aData = DStringBlockData(str->m_data);
	if (!aData)
		return npos;
	char* aFound = strstr(aData + start + 1, sub);
	if (!aFound)
		return npos;
	return aFound - aData;
}

__attribute__((noclone, noinline)) static DStringBlock* DStringBlockRetain(DStringBlock* const& i_block)
{
	if (i_block)
		i_block->retain();
	return i_block;
}

DString& DString::addDString(const DString& s)
{
	if (str)
		str = str->addString(((DString&)s).c_str());
	else
	{
		DStringBlockRetain(s.str);
		str = s.str;
	}
	return *this;
}

DString::DString(const DString& s)
	: str(NULL)
{
	str = DStringBlockRetain(s.str);
}

DString::DString(DString&& s)
	: str(s.str)
{
	s.str = NULL;
}

DString& DString::operator=(const DString& s)
{
	DStringBlockRetain(s.str);
	if (str)
		str->release();
	str = s.str;
	return *this;
}

void DString::clear()
{
	if (str)
	{
		str->release();
		str = NULL;
	}
}

DString& DString::addString(const char* src)
{
	if (str)
		str = str->addString(src);
	else
		newString(src);
	return *this;
}

int DString::toInt() const
{
	const char* aStr = c_str();
	if (aStr)
		return atoi(aStr);
	return 0;
}

long long DString::toInt64() const
{
	const char* aStr = c_str();
	if (aStr)
		return atoll(aStr);
	return 0;
}

long DString::toLong() const
{
	const char* aStr = c_str();
	if (aStr)
		return atol(aStr);
	return 0;
}

double DString::toDouble() const
{
	const char* aStr = c_str();
	if (aStr)
		return atof(aStr);
	return 0;
}

float DString::toFloat() const
{
	return toDouble();
}

bool DString::compare(const DString& src) const
{
	return camp(src.c_str());
}

bool DString::compareWithNoCase(const DString& src) const
{
	return campn(src.c_str());
}

DString& DString::addChar(char src)
{
	char aBuffer[2];
	aBuffer[0] = src;
	aBuffer[1] = 0;
	addString(aBuffer);
	return *this;
}

DString DString::subString(ssize_t start) const
{
	DString aResult;
	if (str)
	{
		char* aData = DStringBlockData(str->m_data);
		if (start < 0 || start >= DStringBlockLength(str->m_length))
			return DString("");
		aResult += aData + start;
	}
	return aResult;
}

DString DString::makeUpper() const
{
	char* aBuffer = (char*)DStackAllocator::getInstance()->push(size());
	const char* aSrc = ((DString*)this)->c_str();
	size_t i = 0;
	for (; aSrc[i]; i++)
	{
		char c = aSrc[i];
		if (c >= 'a' && c <= 'z')
			c -= 0x20;
		aBuffer[i] = c;
	}
	aBuffer[i] = 0;
	DString aResult(aBuffer);
	DStackAllocator::getInstance()->pop();
	return aResult;
}

DString DString::makeLower() const
{
	char* aBuffer = (char*)DStackAllocator::getInstance()->push(size());
	const char* aSrc = ((DString*)this)->c_str();
	size_t i = 0;
	for (; aSrc[i]; i++)
	{
		char c = aSrc[i];
		if (c >= 'A' && c <= 'Z')
			c += 0x20;
		aBuffer[i] = c;
	}
	aBuffer[i] = 0;
	DString aResult(aBuffer);
	DStackAllocator::getInstance()->pop();
	return aResult;
}

/////////////// Compare ///////////////

__attribute__((noclone, noinline)) static bool DStringBlockEqual(const char* i_data, const char* i_src)
{
	if (i_src == i_data)
		return true;
	if (!i_data)
		return false;
	return strcmp(i_src, i_data) == 0;
}

__attribute__((noclone, noinline)) static bool DStringBlockLess(const char* i_data, const char* i_src)
{
	if (i_src == i_data)
		return false;
	if (!i_data)
		return true;
	return strcmp(i_src, i_data) < 0;
}

__attribute__((noclone, noinline)) static bool DStringBlockGreater(const char* i_data, const char* i_src)
{
	if (i_src == i_data || !i_data)
		return false;
	return strcmp(i_src, i_data) > 0;
}

bool DString::camp(const char* src) const
{
	if (str)
		return DStringBlockEqual(str->m_data, src);
	return false;
}

/////////////// Operators ///////////////

DString& DString::operator=(const std::string& src)
{
	newString(src.c_str());
	return *this;
}

DString& DString::operator=(std::string&& src)
{
	newString(src.c_str());
	return *this;
}

DString& DString::operator=(const int src)
{
	format("%d", src);
	return *this;
}

DString& DString::operator=(const float src)
{
	format("%f", src);
	return *this;
}

DString& DString::operator=(const long src)
{
	format("%ld", src);
	return *this;
}

DString& DString::operator=(const double src)
{
	format("%lf", src);
	return *this;
}

DString& DString::operator=(const long long src)
{
	format("%lld", src);
	return *this;
}

DString& DString::operator=(char* src)
{
	newString(src);
	return *this;
}

DString& DString::operator=(const char* src)
{
	newString(src);
	return *this;
}

DString& DString::operator=(DString&& s)
{
	if (str)
		str->release();
	str = s.str;
	s.str = NULL;
	return *this;
}

__attribute__((noclone, noinline)) static char DStringBlockCharAt(DStringBlock* i_block, int i_index)
{
	if (i_block)
		return DStringBlockData(i_block->m_data)[i_index];
	return 0;
}

__attribute__((noclone, noinline)) static char& DStringBlockCharRef(DStringBlock* i_block, int i_index)
{
	return DStringBlockData(i_block->m_data)[i_index];
}

const char DString::operator[](int index) const
{
	return DStringBlockCharAt(str, index);
}

char& DString::operator[](int index)
{
	return DStringBlockCharRef(str, index);
}

bool DString::operator==(char* src) const
{
	return camp(src);
}

bool DString::operator==(const char* src) const
{
	return camp(src);
}

bool DString::operator==(const DString& s) const
{
	return camp(s.c_str());
}

bool DString::operator==(const std::string& s) const
{
	return camp(s.c_str());
}

bool DString::operator!=(char* src) const
{
	return !camp(src);
}

bool DString::operator!=(const char* src) const
{
	return !camp(src);
}

bool DString::operator!=(const DString& s) const
{
	return !camp(s.c_str());
}

bool DString::operator!=(const std::string& s) const
{
	return !camp(s.c_str());
}

bool DString::operator>(char* src) const
{
	if (str)
		return DStringBlockGreater(str->m_data, src);
	return false;
}

bool DString::operator>(const char* src) const
{
	if (str)
		return DStringBlockGreater(str->m_data, src);
	return false;
}

bool DString::operator>(const DString& src) const
{
	DStringBlock* aBlock = str;
	if (aBlock)
	{
		const char* aSrc = src.c_str();
		return DStringBlockGreater(aBlock->m_data, aSrc);
	}
	return false;
}

bool DString::operator>=(char* src) const
{
	if (str)
		return !DStringBlockLess(str->m_data, src);
	return false;
}

bool DString::operator>=(const char* src) const
{
	if (str)
		return !DStringBlockLess(str->m_data, src);
	return false;
}

bool DString::operator>=(const DString& src) const
{
	DStringBlock* aBlock = str;
	if (aBlock)
	{
		const char* aSrc = src.c_str();
		return !DStringBlockLess(aBlock->m_data, aSrc);
	}
	return false;
}

DString& DString::operator+=(const char* src)
{
	addString(src);
	return *this;
}

DString& DString::operator+=(char* src)
{
	addString(src);
	return *this;
}

DString& DString::operator+=(char src)
{
	addChar(src);
	return *this;
}

DString& DString::operator+=(DString* s)
{
	addDString(s);
	return *this;
}

DString& DString::operator+=(const DString& s)
{
	addDString(s);
	return *this;
}

DString& DString::operator+=(DString&& s)
{
	if (str)
		str = str->addString(s.c_str());
	else
	{
		str = s.str;
		s.str = NULL;
	}
	return *this;
}

DString& DString::operator+=(const std::string& s)
{
	addString(s.c_str());
	return *this;
}

DString& DString::operator+=(const int s)
{
	*this += DString(s);
	return *this;
}

DString& DString::operator+=(const float s)
{
	*this += DString(s);
	return *this;
}

DString& DString::operator+=(const double s)
{
	*this += DString(s);
	return *this;
}

DString& DString::operator+=(const long s)
{
	*this += DString(s);
	return *this;
}

DString& DString::operator+=(const long long s)
{
	*this += DString(s);
	return *this;
}

DString& DString::operator-=(const char* src)
{
	replace(src, "");
	return *this;
}

DString& DString::operator-=(char* src)
{
	replace(src, "");
	return *this;
}

DString& DString::operator-=(char src)
{
	replace(&src, "");
	return *this;
}

DString& DString::operator-=(DString* s)
{
	replace(s ? s->c_str() : NULL, "");
	return *this;
}

DString& DString::operator-=(const DString& s)
{
	replace(s.c_str(), "");
	return *this;
}

DString& DString::operator-=(const std::string& s)
{
	replace(s.c_str(), "");
	return *this;
}

DString::operator int() const
{
	return toInt();
}

DString::operator float() const
{
	return toFloat();
}

DString::operator char*()
{
	return c_str();
}

DString::operator const char*() const
{
	return c_str();
}

DString::operator long() const
{
	return toLong();
}

DString::operator long long() const
{
	return toInt64();
}
