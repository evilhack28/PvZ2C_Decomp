//
//  Definition.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-10-04.
//

#include "SexyAppFramework/Common.h"

#include "SexyAppFramework/XMLParser.h"
#include "SexyAppFramework/SexyCache.h"
#include "SexyAppFramework/SexyAppBase.h"
#include "SexyAppFramework/ResourceManager.h"
#include "SexyAppFramework/PerfTimer.h"
#include "SexyAppFramework/IFileDriver.h"
#include "SexyAppFramework/PakLib/PakInterface.h"
#include "RtObject.h"
#include "TodLib/Definition.h"
#include "TodLib/TodDebug.h"
#include "core.h"
#include "TodLib/TodList.h"

#include <stdarg.h>
#include <wchar.h>
#include <alloca.h>

int wcscasecmp_prime(const wchar_t* s1, const wchar_t* s2);
extern "C" unsigned long crc32(unsigned long theCrc, const void* theBuf, unsigned int theLen);
void DefinitionXmlError(Sexy::XMLParser* theParser, const SexyChar* theFormat, ...);
int TodCrc32(int theCrc, void* theBuf, int theLen);
void DefinitionFreeStringField(SexyChar** theField);
void DefinitionFreeFloatTrackField(FloatParameterTrack* theTrack);
bool DefParseTrackTime(const SexyChar*& theSrc, FloatParameterTrackNode* theNode);
int DefParseTrackCurve(const SexyChar*& theSrc);
bool DefParseTrackRangeNode(const SexyChar*& theSrc, FloatParameterTrackNode* theNode);
bool DefParseTrackSimpleNode(const SexyChar*& theSrc, FloatParameterTrackNode* theNode);

class DefinitionArrayDef
{
public:
	void* m_arrayData;
	int m_arrayCount;
};

int DefinitionGetDeepSize(DefMap* theDefMap, void* theDefinition);
int DefinitionGetArraySize(DefinitionArrayDef* theArray, DefMap* theElementMap);
int DefinitionGetSize(DefMap* theDefMap, void* theDefinition);

DefSymbol gDefTrackEaseSymbols[] = {
	{ CURVE_LINEAR, L"Linear" },
	{ CURVE_EASE_IN, L"EaseIn" },
	{ CURVE_EASE_OUT, L"EaseOut" },
	{ CURVE_EASE_IN_OUT, L"EaseInOut" },
	{ CURVE_EASE_IN_OUT_WEAK, L"EaseInOutWeak" },
	{ CURVE_FAST_IN_OUT, L"FastInOut" },
	{ CURVE_FAST_IN_OUT_WEAK, L"FastInOutWeak" },
	{ CURVE_BOUNCE, L"Bounce" },
	{ CURVE_BOUNCE_FAST_MIDDLE, L"BounceFastMiddle" },
	{ CURVE_BOUNCE_SLOW_MIDDLE, L"BounceSlowMiddle" },
	{ CURVE_SIN_WAVE, L"SinWave" },
	{ CURVE_EASE_SIN_WAVE, L"EaseSinWave" },
	{ -1, NULL },
};

/////////////// Definition ///////////////

bool DefSymbolValueFromString(DefSymbol* theSymbolMap, const SexyChar* theName, int* theResultValue)
{
	for (DefSymbol* aSymbol = theSymbolMap; aSymbol->m_symbolName != NULL; aSymbol++)
	{
		if (wcscasecmp_prime(theName, aSymbol->m_symbolName) == 0)
		{
			*theResultValue = aSymbol->m_symbolValue;
			return true;
		}
	}
	return false;
}

const SexyChar* DefSymbolStringFromValue(DefSymbol* theSymbolMap, int theValue)
{
	const SexyChar* aName = theSymbolMap->m_symbolName;
	while (aName != NULL)
	{
		if (theSymbolMap->m_symbolValue == theValue)
			break;
		theSymbolMap++;
		aName = theSymbolMap->m_symbolName;
	}
	return aName;
}

void* DefinitionAlloc(int theSize)
{
	void* aPtr = new char[theSize];
	memset(aPtr, 0, theSize);
	return aPtr;
}

bool FloatTrackIsSet(FloatParameterTrack& theTrack)
{
	return theTrack.m_countNodes != 0 && theTrack.m_nodes[0].m_curveType != CURVE_CONSTANT;
}

bool FloatTrackIsConstantZero(FloatParameterTrack& theTrack)
{
	if (theTrack.m_countNodes == 0)
		return true;
	if (theTrack.m_countNodes != 1)
		return false;
	return theTrack.m_nodes[0].m_lowValue == 0.0f && theTrack.m_nodes[0].m_highValue == 0.0f;
}

void FloatTrackSetDefault(FloatParameterTrack& theTrack, float theValue)
{
	if (theValue == 0.0f)
		return;
	if (theTrack.m_nodes != NULL)
		return;

	theTrack.m_countNodes = 1;
	FloatParameterTrackNode* aNode = (FloatParameterTrackNode*)DefinitionAlloc(sizeof(FloatParameterTrackNode));
	theTrack.m_nodes = aNode;
	aNode->m_curveType = CURVE_CONSTANT;
	aNode->m_distribution = CURVE_LINEAR;
	aNode->m_lowValue = theValue;
	aNode->m_highValue = theValue;
	aNode->m_time = 0.0f;
}

void DefinitionFree(void* thePtr)
{
	delete[] (char*)thePtr;
}

void DefinitionXmlError(Sexy::XMLParser* theParser, const SexyChar* theFormat, ...)
{
	va_list aArgList;
	va_start(aArgList, theFormat);
	std::string aMessage = Sexy::SexyStringToString(Sexy::StrFormat(theFormat, aArgList));
	va_end(aArgList);
}

int TodCrc32(int theCrc, void* theBuf, int theLen)
{
	return crc32(theCrc, theBuf, theLen);
}

int DefinitionCalcHashSymbolMap(int theHash, DefSymbol* theSymbolMap)
{
	for (DefSymbol* aSymbol = theSymbolMap; aSymbol->m_symbolName != NULL; aSymbol++)
	{
		theHash = TodCrc32(theHash, (void*)aSymbol->m_symbolName, wcslen(aSymbol->m_symbolName) * 4);
		theHash = TodCrc32(theHash, aSymbol, 4);
	}
	return theHash;
}

void DefinitionFreeStringField(SexyChar** theField)
{
	if (**theField != 0)
		DefinitionFree(*theField);
	*theField = NULL;
}

void DefinitionFreeFloatTrackField(FloatParameterTrack* theTrack)
{
	if (theTrack->m_countNodes != 0)
		DefinitionFree(theTrack->m_nodes);
	theTrack->m_nodes = NULL;
}

void DefWriteToCacheFloatTrack(void** theWritePtr, const FloatParameterTrack* theTrack);
bool DefReadFromCacheFloatTrack(void** theReadPtr, FloatParameterTrack* theTrack);
void DefWriteToCacheString(void** theWritePtr, const SexyChar* theString);
bool DefReadFromCacheString(void** theReadPtr, SexyChar** theString);
void DefWriteToCacheArraySSLKeyBool(void** theWritePtr, const SSListKey* theKey);
bool DefReadFromCacheArraySSLKeyBool(void** theReadPtr, SSListKey* theKey);
bool DefinitionLoadImage(Sexy::Image** theImage, const std::string& thePath);
bool DefinitionLoadFont(Sexy::Font** theFont, std::string thePath);
void DefWriteToCacheImage(void** theWritePtr, Sexy::Image** theImage);
void DefWriteToCacheFont(void** theWritePtr, Sexy::Font** theFont);
bool DefReadFromCacheImage(void** theReadPtr, Sexy::Image** theImage);
bool DefReadFromCacheFont(void** theReadPtr, Sexy::Font** theFont);
void DefinitionFillWithDefaults(DefMap* theDefMap, void* theDefinition);
void DefinitionFreeMap(DefMap* theDefMap, void* theDefinition);
void DefinitionFreeArrayField(DefinitionArrayDef* theArray, DefMap* theElementMap);
void DefinitionFreeArraySSLKeyField(SSListKey* theKey);
bool DefinitionCompileAndLoad(const std::string& theFilename, DefMap* theDefMap, void* theDefinition, bool theSkipCompile, bool theRunConstructor);
std::string GetFolder(Sexy::IFileDriver::PathType thePathType);
bool IsFileInPakFile(const std::string& theFilename);
std::string DefinitionGetCompiledFilePathFromXMLFilePath(const std::string& theXMLFilePath);
bool DefinitionCompileFile(const std::string& theXMLFilePath, const std::string& theCompiledFilePath, DefMap* theDefMap, void* theDefinition, bool theRunConstructor);
bool DefinitionLoadMap(Sexy::XMLParser* theXMLParser, DefMap* theDefMap, void* theDefinition, bool theRunConstructor);
bool DefinitionWriteCompiledFile(const std::string& theCompiledFilePath, DefMap* theDefMap, void* theDefinition);
bool DefinitionReadXMLString(Sexy::XMLParser* theXMLParser, SexyString* theValue);
bool DefinitionReadStringField(Sexy::XMLParser* theXMLParser, SexyChar** theValue);
bool DefinitionReadIntField(Sexy::XMLParser* theXMLParser, int* theValue);
bool DefinitionReadFloatField(Sexy::XMLParser* theXMLParser, float* theValue);
bool DefinitionReadBoolField(Sexy::XMLParser* theXMLParser, bool* theValue);
bool DefinitionReadEnumField(Sexy::XMLParser* theXMLParser, int* theValue, DefSymbol* theSymbolMap);
bool DefinitionReadVector2Field(Sexy::XMLParser* theXMLParser, Sexy::SexyVector2* theValue);
bool DefinitionReadVector3Field(Sexy::XMLParser* theXMLParser, Sexy::SexyVector3* theValue);
bool DefinitionReadRectField(Sexy::XMLParser* theXMLParser, Sexy::Rect* theValue);
bool DefinitionReadImageField(Sexy::XMLParser* theXMLParser, Sexy::Image** theValue);
bool DefinitionReadFontField(Sexy::XMLParser* theXMLParser, Sexy::Font** theValue);
bool DefinitionReadFlagField(Sexy::XMLParser* theXMLParser, SexyString theFlagName, unsigned int* theFlags, DefSymbol* theSymbolMap);
bool DefinitionReadFloatTrackField(Sexy::XMLParser* theXMLParser, FloatParameterTrack* theTrack);
bool DefinitionReadSpaceSeparatedList(Sexy::XMLParser* theXMLParser, std::vector<int>* theList);
bool DefinitionReadField(Sexy::XMLParser* theXMLParser, DefMap* theDefMap, void* theDefinition, bool& theDone);
bool DefinitionReadArrayField(Sexy::XMLParser* theXMLParser, DefinitionArrayDef* theArray, DefField* theField);
bool DefinitionReadSpaceSeparatedListWithKey(Sexy::XMLParser* theXMLParser, SSListKey* theKey, DefSymbol* theSymbolMap);
extern "C" int compress(unsigned char* theDest, unsigned long* theDestLen, const unsigned char* theSource, unsigned long theSourceLen);
extern "C" int uncompress(unsigned char* theDest, unsigned long* theDestLen, const unsigned char* theSource, unsigned long theSourceLen);
unsigned char* DefinitionCompressCompiledBuffer(unsigned char* theData, unsigned int theSize, unsigned int* theOutSize);
unsigned char* DefinitionUncompressCompiledBuffer(unsigned char* theData, unsigned int theSize, unsigned int* theOutSize, const std::string& theFilename);
bool DefinitionLoadImage(Sexy::Image** theImage, const std::string& thePath);
int DefinitionCalcHashSymbolMap(int theHash, DefSymbol* theSymbolMap);
int DefinitionCalcHashDefMap(int theHash, DefMap* theDefMap, TodList<DefMap*>& theDefMapList);
int DefinitionCalcHash(DefMap* theDefMap);
void DefMapWriteToCache(void** theWritePtr, DefMap* theDefMap, void* theDefinition);
void DefWriteToCacheArray(void** theWritePtr, DefinitionArrayDef* theArray, DefMap* theElementMap);
bool DefMapReadFromCache(void** theReadPtr, DefMap* theDefMap, void* theDefinition);
bool DefReadFromCacheArray(void** theReadPtr, DefinitionArrayDef* theArray, DefMap* theElementMap);
bool DefinitionReadFromCache(const std::string& theFilePath, DefMap* theDefMap, void* theDefinition);
void DefinitionWriteToCache(const std::string& theFilePath, DefMap* theDefMap, void* theDefinition);
bool DefinitionWriteCompiledFile(const std::string& theCompiledFilePath, DefMap* theDefMap, void* theDefinition);
int DefGetSizeString(SexyChar** theField);
int DefGetSizeFloatTrack(FloatParameterTrack* theTrack);
int DefGetSizeArraySSListKey(SSListKey* theKey);
int DefGetSizeImage(Sexy::Image** theImage);
int DefGetSizeFont(Sexy::Font** theFont);
bool TodFindFontPath(Sexy::Font* theFont, std::string& thePath);

static void DefSkipSpaces(const SexyChar*& theSrc)
{
	theSrc += wcsspn(theSrc, L" 	");
}

bool DefParseTrackTime(const SexyChar*& theSrc, FloatParameterTrackNode* theNode)
{
	DefSkipSpaces(theSrc);
	if (*theSrc != L',')
	{
		theNode->m_time = -1.0f;
		return true;
	}

	theSrc++;
	DefSkipSpaces(theSrc);
	float aTime;
	if (swscanf(theSrc, L"%f", &aTime) != 1)
		return false;

	theNode->m_time = aTime * 0.01f;
	theSrc += wcscspn(theSrc, L" 	");
	return true;
}

int DefParseTrackCurve(const SexyChar*& theSrc)
{
	size_t aLen = wcscspn(theSrc, L" 	");
	int aCurve;
	if (aLen > 0 && aLen < 32)
	{
		SexyChar aName[32];
		wcsncpy(aName, theSrc, aLen);
		aName[aLen] = L'\0';
		if (DefSymbolValueFromString(gDefTrackEaseSymbols, aName, &aCurve))
		{
			theSrc += aLen;
			goto done;
		}
	}
	aCurve = 1;
done:
	return aCurve;
}

bool DefParseTrackRangeNode(const SexyChar*& theSrc, FloatParameterTrackNode* theNode)
{
	theSrc++;
	if (swscanf(theSrc, L"%f", &theNode->m_lowValue) != 1)
		return false;

	theSrc += wcscspn(theSrc, L"] 	");
	if (*theSrc == 0)
		return false;

	DefSkipSpaces(theSrc);
	if (*theSrc == L']')
	{
		theNode->m_highValue = theNode->m_lowValue;
	}
	else
	{
		theNode->m_distribution = (CurveType)DefParseTrackCurve(theSrc);
		DefSkipSpaces(theSrc);
		if (swscanf(theSrc, L"%f", &theNode->m_highValue) != 1)
			return false;

		theSrc += wcscspn(theSrc, L"]");
		if (*theSrc != L']')
			return false;
	}

	theSrc++;
	return DefParseTrackTime(theSrc, theNode);
}

bool DefParseTrackSimpleNode(const SexyChar*& theSrc, FloatParameterTrackNode* theNode)
{
	if (swscanf(theSrc, L"%f", &theNode->m_lowValue) != 1)
		return false;

	theNode->m_distribution = CURVE_LINEAR;
	theNode->m_highValue = theNode->m_lowValue;
	theSrc += wcscspn(theSrc, L", 	");
	return DefParseTrackTime(theSrc, theNode);
}

int DefGetSizeString(SexyChar** theField)
{
	int aSize = wcslen(*theField) * sizeof(SexyChar);
	return aSize + 4;
}

int DefGetSizeFloatTrack(FloatParameterTrack* theTrack)
{
	return theTrack->m_countNodes * sizeof(FloatParameterTrackNode) + 4;
}

int DefGetSizeArraySSListKey(SSListKey* theKey)
{
	int aSize = 4;
	for (int i = 0; i < theKey->m_keyCount; i++)
	{
		long aCount = theKey->m_key[i].m_dataCount;
		aSize += 4 + aCount;
	}
	return aSize;
}

int DefGetSizeImage(Sexy::Image** theImage)
{
	std::string aPath;
	if (*theImage != NULL)
		TodFindImagePath(*theImage, aPath);
	return aPath.length() + 4;
}

int DefGetSizeFont(Sexy::Font** theFont)
{
	std::string aPath;
	if (*theFont != NULL)
		TodFindFontPath(*theFont, aPath);
	return aPath.length() + 4;
}

int DefinitionGetDeepSize(DefMap* theDefMap, void* theDefinition)
{
	int aSize = 0;
	for (DefField* aField = theDefMap->m_mapFields; *aField->m_fieldName != 0; aField++)
	{
		void* aVarPtr = (char*)theDefinition + aField->m_fieldOffset;
		switch (aField->m_fieldType)
		{
		case DT_STRING:
			aSize += DefGetSizeString((SexyChar**)aVarPtr);
			break;
		case DT_ARRAY:
			aSize += DefinitionGetArraySize((DefinitionArrayDef*)aVarPtr, (DefMap*)aField->m_extraData);
			break;
		case DT_ARRAY_SSL_KEY:
			aSize += DefGetSizeArraySSListKey((SSListKey*)aVarPtr);
			break;
		case DT_TRACK_FLOAT:
			aSize += DefGetSizeFloatTrack((FloatParameterTrack*)aVarPtr);
			break;
		case DT_IMAGE:
			aSize += DefGetSizeImage((Sexy::Image**)aVarPtr);
			break;
		case DT_FONT:
			aSize += DefGetSizeFont((Sexy::Font**)aVarPtr);
			break;
		default:
			break;
		}
	}
	return aSize;
}

int DefinitionGetArraySize(DefinitionArrayDef* theArray, DefMap* theElementMap)
{
	int aSize = theElementMap->m_defSize * theArray->m_arrayCount + 4;
	for (int i = 0; i < theArray->m_arrayCount; i++)
		aSize += DefinitionGetDeepSize(theElementMap, (char*)theArray->m_arrayData + theElementMap->m_defSize * i);
	return aSize;
}

int DefinitionGetSize(DefMap* theDefMap, void* theDefinition)
{
	return theDefMap->m_defSize + DefinitionGetDeepSize(theDefMap, theDefinition);
}

void DefWriteToCacheFloatTrack(void** theWritePtr, const FloatParameterTrack* theTrack)
{
	Sexy::SMemW(theWritePtr, &theTrack->m_countNodes, 4);
	if (theTrack->m_countNodes > 0)
		Sexy::SMemW(theWritePtr, theTrack->m_nodes, theTrack->m_countNodes * sizeof(FloatParameterTrackNode));
}

bool DefReadFromCacheFloatTrack(void** theReadPtr, FloatParameterTrack* theTrack)
{
	Sexy::SMemR(theReadPtr, &theTrack->m_countNodes, 4);
	if (theTrack->m_countNodes > 0)
	{
		theTrack->m_nodes = (FloatParameterTrackNode*)DefinitionAlloc(theTrack->m_countNodes * sizeof(FloatParameterTrackNode));
		Sexy::SMemR(theReadPtr, theTrack->m_nodes, theTrack->m_countNodes * sizeof(FloatParameterTrackNode));
	}
	return true;
}

void DefWriteToCacheString(void** theWritePtr, const SexyChar* theString)
{
	int aLen = wcslen(theString);
	Sexy::SMemW(theWritePtr, &aLen, 4);
	if (aLen > 0)
		Sexy::SMemW(theWritePtr, theString, aLen * sizeof(SexyChar));
}

bool DefReadFromCacheString(void** theReadPtr, SexyChar** theString)
{
	int aLen;
	Sexy::SMemR(theReadPtr, &aLen, 4);
	if (aLen == 0)
	{
		*theString = NULL;
	}
	else
	{
		*theString = (SexyChar*)DefinitionAlloc((aLen + 1) * sizeof(SexyChar));
		Sexy::SMemR(theReadPtr, *theString, aLen * sizeof(SexyChar));
		(*theString)[aLen] = 0;
	}
	return true;
}

void DefWriteToCacheArraySSLKeyBool(void** theWritePtr, const SSListKey* theKey)
{
	Sexy::SMemW(theWritePtr, &theKey->m_keyCount, 4);
	for (int i = 0; i < theKey->m_keyCount; i++)
	{
		Sexy::SMemW(theWritePtr, &theKey->m_key[i].m_dataCount, 4);
		if (theKey->m_key[i].m_dataCount > 0)
			Sexy::SMemW(theWritePtr, theKey->m_key[i].m_data, theKey->m_key[i].m_dataCount);
	}
}

bool DefReadFromCacheArraySSLKeyBool(void** theReadPtr, SSListKey* theKey)
{
	int aCount = 0;
	Sexy::SMemR(theReadPtr, &aCount, 4);
	theKey->m_keyCount = aCount;
	if (aCount != 0)
	{
		theKey->m_key = (CharArrayData*)DefinitionAlloc(aCount * sizeof(CharArrayData));
		for (int i = 0; i < aCount; i++)
		{
			int aDataCount = 0;
			Sexy::SMemR(theReadPtr, &aDataCount, 4);
			theKey->m_key[i].m_dataCount = aDataCount;
			if (aDataCount > 0)
			{
				theKey->m_key[i].m_data = (char*)DefinitionAlloc(aDataCount);
				Sexy::SMemR(theReadPtr, &theKey->m_key[i], aDataCount);
			}
		}
	}
	return true;
}

void DefWriteToCacheImage(void** theWritePtr, Sexy::Image** theImage)
{
	std::string aPath;
	if (*theImage != NULL)
		TodFindImagePath(*theImage, aPath);

	int aLen = aPath.length();
	Sexy::SMemW(theWritePtr, &aLen, 4);
	if (aLen > 0)
		Sexy::SMemW(theWritePtr, aPath.c_str(), aLen);
}

void DefWriteToCacheFont(void** theWritePtr, Sexy::Font** theFont)
{
	std::string aPath;
	if (*theFont != NULL)
		TodFindFontPath(*theFont, aPath);

	int aLen = aPath.length();
	Sexy::SMemW(theWritePtr, &aLen, 4);
	if (aLen > 0)
		Sexy::SMemW(theWritePtr, aPath.c_str(), aLen);
}

bool DefReadFromCacheImage(void** theReadPtr, Sexy::Image** theImage)
{
	int aLen;
	Sexy::SMemR(theReadPtr, &aLen, 4);
	char* aPath = (char*)alloca(aLen + 1);
	Sexy::SMemR(theReadPtr, aPath, aLen);
	aPath[aLen] = 0;
	*theImage = NULL;
	if (aPath[0] != 0)
		return DefinitionLoadImage(theImage, aPath);
	return true;
}

bool DefReadFromCacheFont(void** theReadPtr, Sexy::Font** theFont)
{
	int aLen;
	Sexy::SMemR(theReadPtr, &aLen, 4);
	char* aPath = (char*)alloca(aLen + 1);
	Sexy::SMemR(theReadPtr, aPath, aLen);
	*theFont = NULL;
	aPath[aLen] = 0;
	if (aPath[0] != 0)
		return DefinitionLoadFont(theFont, aPath);
	return true;
}

bool DefinitionIsCompiled(const std::string& theXMLFilePath)
{
	return true;
}

bool DefinitionLoadFont(Sexy::Font** theFont, std::string thePath)
{
	*theFont = NULL;
	return false;
}

bool DefinitionLoadXML(const std::string& theFilename, DefMap* theDefMap, void* theDefinition, bool theSkipCompile, bool theRunConstructor)
{
	return DefinitionCompileAndLoad(theFilename, theDefMap, theDefinition, theSkipCompile, theRunConstructor);
}

void DefinitionFillWithDefaults(DefMap* theDefMap, void* theDefinition)
{
	memset(theDefinition, 0, theDefMap->m_defSize);
	for (DefField* aField = theDefMap->m_mapFields; *aField->m_fieldName != 0; aField++)
	{
		const SexyChar** aVarPtr = (const SexyChar**)((char*)theDefinition + aField->m_fieldOffset);
		if (aField->m_fieldType == DT_STRING)
			*aVarPtr = L"";
	}
}

void DefinitionFreeArraySSLKeyField(SSListKey* theKey)
{
	if (theKey->m_keyCount > 0)
	{
		for (int i = 0; i < theKey->m_keyCount; i++)
		{
			if (theKey->m_key[i].m_dataCount > 0)
			{
				DefinitionFree(theKey->m_key[i].m_data);
				theKey->m_key[i].m_data = NULL;
				theKey->m_key[i].m_dataCount = 0;
			}
		}

		if (theKey->m_keyCount > 0)
		{
			DefinitionFree(theKey->m_key);
			theKey->m_key = NULL;
			theKey->m_keyCount = 0;
		}
	}
}

void DefinitionFreeMap(DefMap* theDefMap, void* theDefinition)
{
	for (DefField* aField = theDefMap->m_mapFields; *aField->m_fieldName != 0; aField++)
	{
		void* aVarPtr = (char*)theDefinition + aField->m_fieldOffset;
		switch (aField->m_fieldType)
		{
		case DT_STRING:
			DefinitionFreeStringField((SexyChar**)aVarPtr);
			break;
		case DT_ARRAY:
			DefinitionFreeArrayField((DefinitionArrayDef*)aVarPtr, (DefMap*)aField->m_extraData);
			break;
		case DT_ARRAY_SSL_KEY:
			DefinitionFreeArraySSLKeyField((SSListKey*)aVarPtr);
			break;
		case DT_TRACK_FLOAT:
			DefinitionFreeFloatTrackField((FloatParameterTrack*)aVarPtr);
			break;
		default:
			break;
		}
	}
}

void DefinitionFreeArrayField(DefinitionArrayDef* theArray, DefMap* theElementMap)
{
	for (int i = 0; i < theArray->m_arrayCount; i++)
		DefinitionFreeMap(theElementMap, (char*)theArray->m_arrayData + i * theElementMap->m_defSize);

	DefinitionFree(theArray->m_arrayData);
	theArray->m_arrayData = NULL;
}

bool IsFileInPakFile(const std::string& theFilename)
{
	if (GetPakPtr() != NULL)
	{
		PFILE* aFile = gPakInterface->FOpen(theFilename.c_str(), "rb", PSEARCH_JUST_PAK);
		if (aFile != NULL)
		{
			gPakInterface->FClose(aFile);
			return true;
		}
	}
	return false;
}

std::string DefinitionGetCompiledFilePathFromXMLFilePath(const std::string& theXMLFilePath)
{
	std::string aDir = Sexy::GetFileDir(theXMLFilePath, true);
	std::string aName = Sexy::GetFileName(theXMLFilePath, false);
	std::string aFolder = GetFolder(Sexy::IFileDriver::PathType_NoBackup);
	return Sexy::StrFormat("%s_compiledXml/%s%s.compiled", aFolder.c_str(), aDir.c_str(), aName.c_str());
}

bool DefinitionCompileFile(const std::string& theXMLFilePath, const std::string& theCompiledFilePath, DefMap* theDefMap, void* theDefinition, bool theRunConstructor)
{
	Sexy::XMLParser aParser;
	aParser.SetEncodingType(Sexy::EncodingParser::UTF_8);
	if (!aParser.OpenFile(theXMLFilePath))
		return false;
	if (!DefinitionLoadMap(&aParser, theDefMap, theDefinition, theRunConstructor))
		return false;

	DefinitionWriteCompiledFile(theCompiledFilePath, theDefMap, theDefinition);
	return true;
}

bool DefinitionCompileAndLoad(const std::string& theFilename, DefMap* theDefMap, void* theDefinition, bool theSkipCompile, bool theRunConstructor)
{
	std::string aCompiledFilePath = DefinitionGetCompiledFilePathFromXMLFilePath(theFilename);
	Sexy::PerfTimer aTimer;
	aTimer.Start();
	return DefinitionCompileFile(theFilename, aCompiledFilePath, theDefMap, theDefinition, theRunConstructor);
}

bool DefinitionReadXMLString(Sexy::XMLParser* theXMLParser, SexyString* theValue)
{
	Sexy::XMLElement aXMLElement;
	if (!theXMLParser->NextElement(&aXMLElement))
	{
		DefinitionXmlError(theXMLParser, L"Missing element value");
		return false;
	}

	if (aXMLElement.mType == Sexy::XMLElement::TYPE_END)
		return true;

	if (aXMLElement.mType != Sexy::XMLElement::TYPE_ELEMENT)
	{
		DefinitionXmlError(theXMLParser, L"unknown element type");
		return false;
	}

	*theValue = aXMLElement.mValue;
	if (!theXMLParser->NextElement(&aXMLElement))
	{
		DefinitionXmlError(theXMLParser, L"Can't read element end");
		return false;
	}

	if (aXMLElement.mType != Sexy::XMLElement::TYPE_END)
	{
		DefinitionXmlError(theXMLParser, L"Missing element end");
		return false;
	}

	return true;
}

bool DefinitionReadStringField(Sexy::XMLParser* theXMLParser, SexyChar** theValue)
{
	SexyString aStringValue;
	bool aResult = DefinitionReadXMLString(theXMLParser, &aStringValue);
	if (aResult)
	{
		bool aEmpty = aStringValue.empty();
		if (aEmpty)
		{
			*theValue = NULL;
			aResult = aEmpty;
		}
		else
		{
			int aLen = aStringValue.length();
			*theValue = (SexyChar*)DefinitionAlloc((aLen + 1) * sizeof(SexyChar));
			wcscpy(*theValue, aStringValue.c_str());
		}
	}
	return aResult;
}

bool DefinitionReadIntField(Sexy::XMLParser* theXMLParser, int* theValue)
{
	SexyString aStringValue;
	bool aResult = DefinitionReadXMLString(theXMLParser, &aStringValue);
	if (aResult)
	{
		SexyChar* aEndPtr;
		*theValue = wcstol(aStringValue.c_str(), &aEndPtr, 10);
		if (aEndPtr == aStringValue)
		{
			aResult = false;
			DefinitionXmlError(theXMLParser, L"Can't parse int value '%s'", aStringValue.c_str());
		}
	}
	return aResult;
}

bool DefinitionReadFloatField(Sexy::XMLParser* theXMLParser, float* theValue)
{
	SexyString aStringValue;
	bool aResult = DefinitionReadXMLString(theXMLParser, &aStringValue);
	if (aResult)
	{
		if (swscanf(aStringValue.c_str(), L"%f", theValue) != 1)
		{
			aResult = false;
			DefinitionXmlError(theXMLParser, L"Can't parse float value '%s'", aStringValue.c_str());
		}
	}
	return aResult;
}

bool DefinitionReadBoolField(Sexy::XMLParser* theXMLParser, bool* theValue)
{
	SexyString aStringValue;
	bool aResult = DefinitionReadXMLString(theXMLParser, &aStringValue);
	if (aResult)
	{
		if (wcscasecmp_prime(aStringValue.c_str(), L"true") == 0)
			*theValue = true;
		else
			*theValue = false;
	}
	return aResult;
}

bool DefinitionReadEnumField(Sexy::XMLParser* theXMLParser, int* theValue, DefSymbol* theSymbolMap)
{
	SexyString aStringValue;
	bool aResult = DefinitionReadXMLString(theXMLParser, &aStringValue);
	if (aResult)
	{
		aResult = DefSymbolValueFromString(theSymbolMap, aStringValue.c_str(), theValue);
		if (!aResult)
			DefinitionXmlError(theXMLParser, L"Can't parse enum value '%s'", aStringValue.c_str());
	}
	return aResult;
}

bool DefinitionReadVector2Field(Sexy::XMLParser* theXMLParser, Sexy::SexyVector2* theValue)
{
	SexyString aStringValue;
	bool aResult = DefinitionReadXMLString(theXMLParser, &aStringValue);
	if (aResult)
	{
		if (swscanf(aStringValue.c_str(), L"%f %f", &theValue->x, &theValue->y) != 2)
		{
			aResult = false;
			DefinitionXmlError(theXMLParser, L"Can't parse vector2 value '%s'", aStringValue.c_str());
		}
	}
	return aResult;
}

bool DefinitionReadVector3Field(Sexy::XMLParser* theXMLParser, Sexy::SexyVector3* theValue)
{
	SexyString aStringValue;
	bool aResult = DefinitionReadXMLString(theXMLParser, &aStringValue);
	if (aResult)
	{
		if (swscanf(aStringValue.c_str(), L"%f %f %f", &theValue->x, &theValue->y, &theValue->z) != 3)
		{
			aResult = false;
			DefinitionXmlError(theXMLParser, L"Can't parse vector3 value '%s'", aStringValue.c_str());
		}
	}
	return aResult;
}

bool DefinitionReadRectField(Sexy::XMLParser* theXMLParser, Sexy::Rect* theValue)
{
	SexyString aStringValue;
	bool aResult = DefinitionReadXMLString(theXMLParser, &aStringValue);
	if (aResult)
	{
		if (swscanf(aStringValue.c_str(), L"%d %d %d %d", &theValue->mX, &theValue->mY, &theValue->mWidth, &theValue->mHeight) != 4)
		{
			aResult = false;
			DefinitionXmlError(theXMLParser, L"Can't parse rect value '%s'", aStringValue.c_str());
		}
	}
	return aResult;
}

bool DefinitionReadImageField(Sexy::XMLParser* theXMLParser, Sexy::Image** theValue)
{
	SexyString aStringValue;
	bool aResult = DefinitionReadXMLString(theXMLParser, &aStringValue);
	if (aResult)
	{
		std::string aPath = Sexy::SexyStringToString(aStringValue);
		if (!DefinitionLoadImage(theValue, aPath))
		{
			std::string aMessage = Sexy::StrFormat("Failed to find image '%s' in %s", Sexy::WStringToString(aStringValue).c_str(), theXMLParser->GetFileName().c_str());
			TodErrorMessageBox(aMessage.c_str(), "Missing image");
		}
	}
	return aResult;
}

bool DefinitionReadFontField(Sexy::XMLParser* theXMLParser, Sexy::Font** theValue)
{
	SexyString aStringValue;
	bool aResult = DefinitionReadXMLString(theXMLParser, &aStringValue);
	if (aResult)
	{
		aResult = DefinitionLoadFont(theValue, Sexy::SexyStringToString(aStringValue));
		if (!aResult)
		{
			std::string aMessage = Sexy::StrFormat("Failed to find font '%s' in %s", aStringValue.c_str(), theXMLParser->GetFileName().c_str());
			TodErrorMessageBox(aMessage.c_str(), "Missing font");
			aResult = true;
		}
	}
	return aResult;
}

bool DefinitionReadFlagField(Sexy::XMLParser* theXMLParser, SexyString theFlagName, unsigned int* theFlags, DefSymbol* theSymbolMap)
{
	unsigned int aFlag;
	bool aResult = DefSymbolValueFromString(theSymbolMap, theFlagName.c_str(), (int*)&aFlag);
	if (aResult)
	{
		SexyString aStringValue;
		aResult = DefinitionReadXMLString(theXMLParser, &aStringValue);
		if (aResult)
		{
			std::string aFlagNameString = Sexy::SexyStringToString(theFlagName);
			int aValue;
			if (swscanf(aStringValue.c_str(), L"%d", &aValue) == 1)
			{
				SetFlag<unsigned int>(*theFlags, aFlag, aValue != 0);
			}
			else
			{
				aResult = false;
				DefinitionXmlError(theXMLParser, L"Can't parse int value '%s'", aStringValue.c_str());
			}
		}
	}
	return aResult;
}

static float DefTrackMissingNodeTime(FloatParameterTrack* theTrack, int theIndex)
{
	if (theIndex == 0)
		return 0.0f;

	int aNextIndex = theTrack->m_countNodes - 1;
	if (aNextIndex == theIndex)
		return 1.0f;

	float aNextTime = 1.0f;
	for (int i = theIndex + 1; i < theTrack->m_countNodes; i++)
	{
		float aTime = theTrack->m_nodes[i].m_time;
		if (aTime >= 0.0f)
		{
			aNextTime = aTime;
			aNextIndex = i;
		}
	}

	float aPrevTime = theTrack->m_nodes[theIndex - 1].m_time;
	return aPrevTime + (aNextTime - aPrevTime) * (1.0f / (float)(aNextIndex - theIndex + 1));
}

bool DefinitionReadFloatTrackField(Sexy::XMLParser* theXMLParser, FloatParameterTrack* theTrack)
{
	SexyString aStringValue;
	bool aResult = DefinitionReadXMLString(theXMLParser, &aStringValue);
	if (aResult)
	{
		theTrack->m_countNodes = 0;
		const SexyChar* aSrc = aStringValue.c_str();
		FloatParameterTrackNode aNodes[10] = {};
		int aCount;
		for (int n = 0; n < 10; n++)
		{
			FloatParameterTrackNode* aNode = &aNodes[n];
			DefSkipSpaces(aSrc);
			if (*aSrc == 0)
			{
				aCount = theTrack->m_countNodes;
				break;
			}

			bool aParsed;
			if (*aSrc == L'[')
				aParsed = DefParseTrackRangeNode(aSrc, aNode);
			else
				aParsed = DefParseTrackSimpleNode(aSrc, aNode);

			if (!aParsed)
			{
				DefinitionXmlError(theXMLParser, L"Can't parse track '%s'", aStringValue.c_str());
				aResult = aParsed;
				goto done;
			}

			DefSkipSpaces(aSrc);
			aNode->m_curveType = (CurveType)DefParseTrackCurve(aSrc);
			aCount = ++theTrack->m_countNodes;
		}

		if (aCount == 0)
		{
			DefinitionXmlError(theXMLParser, L"track must have node");
			aResult = false;
		}
		else
		{
			theTrack->m_nodes = (FloatParameterTrackNode*)DefinitionAlloc(aCount * sizeof(FloatParameterTrackNode));
			memcpy(theTrack->m_nodes, aNodes, aCount * sizeof(FloatParameterTrackNode));

			float aLastTime = 0.0f;
			for (int i = 0; i < theTrack->m_countNodes; i++)
			{
				FloatParameterTrackNode* aCur = &theTrack->m_nodes[i];
				float aTime = aCur->m_time;
				if (aTime >= 0.0f)
				{
					if (aTime < aLastTime)
					{
						aResult = false;
						DefinitionXmlError(theXMLParser, L"track time is out of order");
						break;
					}
					if (aTime > 1.0f)
					{
						aResult = false;
						DefinitionXmlError(theXMLParser, L"track time is too high");
						break;
					}
				}
				else
				{
					aTime = DefTrackMissingNodeTime(theTrack, i);
					aCur->m_time = aTime;
				}
				aLastTime = aTime;
			}
		}
	}
done:
	return aResult;
}

bool DefinitionReadSpaceSeparatedList(Sexy::XMLParser* theXMLParser, std::vector<int>* theList)
{
	SexyString aStringValue;
	bool aResult = DefinitionReadXMLString(theXMLParser, &aStringValue);
	if (aResult)
	{
		theList->clear();
		const SexyChar* aSrc = aStringValue.c_str();
		SexyString aToken;
		DefSkipSpaces(aSrc);
		int aValue;
		while (swscanf(aSrc, L"%d", &aValue) == 1)
		{
			swscanf(aSrc, L"%ls", aToken.c_str());
			swscanf(aSrc, L"%s", aToken.c_str());
			theList->push_back(aValue);
			aSrc += wcslen(aToken.c_str());
			DefSkipSpaces(aSrc);
		}
	}
	return aResult;
}

bool DefinitionLoadMap(Sexy::XMLParser* theXMLParser, DefMap* theDefMap, void* theDefinition, bool theRunConstructor)
{
	if (theRunConstructor)
	{
		if (theDefMap->m_constructorFunc != NULL)
			theDefMap->m_constructorFunc(theDefinition);
		else
			DefinitionFillWithDefaults(theDefMap, theDefinition);
	}

	bool aDone = false;
	bool aResult = true;
	while (aResult && !aDone)
		aResult = DefinitionReadField(theXMLParser, theDefMap, theDefinition, aDone);
	return aResult;
}

static bool DefIsPowerOfTwo(unsigned int theValue)
{
	return theValue != 0 && (theValue & (theValue - 1)) == 0;
}

bool DefinitionReadArrayField(Sexy::XMLParser* theXMLParser, DefinitionArrayDef* theArray, DefField* theField)
{
	DefMap* anElementMap = (DefMap*)theField->m_extraData;
	unsigned int aCount = theArray->m_arrayCount;
	void* aData;
	int aNewCount;
	if (aCount == 0)
	{
		theArray->m_arrayCount = 1;
		aData = DefinitionAlloc(anElementMap->m_defSize);
		aNewCount = theArray->m_arrayCount;
		theArray->m_arrayData = aData;
	}
	else
	{
		if (DefIsPowerOfTwo(aCount))
		{
			void* aOldData = theArray->m_arrayData;
			aData = DefinitionAlloc(aCount * anElementMap->m_defSize * 2);
			theArray->m_arrayData = aData;
			memcpy(aData, aOldData, theArray->m_arrayCount * anElementMap->m_defSize);
			DefinitionFree(aOldData);
			aCount = theArray->m_arrayCount;
		}
		aData = theArray->m_arrayData;
		aNewCount = aCount + 1;
		theArray->m_arrayCount = aNewCount;
	}

	void* anElement = (char*)aData + (aNewCount - 1) * anElementMap->m_defSize;
	bool aResult = DefinitionLoadMap(theXMLParser, anElementMap, anElement, true);
	if (!aResult)
		DefinitionXmlError(theXMLParser, L"failed to read sub def");
	return aResult;
}

bool DefinitionReadField(Sexy::XMLParser* theXMLParser, DefMap* theDefMap, void* theDefinition, bool& theDone)
{
	bool aFailed = theXMLParser->HasFailed();
	if (aFailed)
	{
		aFailed = false;
	}
	else
	{
		Sexy::XMLElement aXMLElement;
		bool aResult = theXMLParser->NextElement(&aXMLElement);
		if (!aResult || aXMLElement.mType == Sexy::XMLElement::TYPE_END)
		{
			aResult = true;
			theDone = true;
		}
		else
		{
			if (aXMLElement.mType != Sexy::XMLElement::TYPE_START)
			{
				DefinitionXmlError(theXMLParser, L"Missing element start");
				aResult = aFailed;
			}
			else
			{
				DefField* aField = theDefMap->m_mapFields;
				while (*aField->m_fieldName != 0)
				{
					void* aVarPtr = (char*)theDefinition + aField->m_fieldOffset;
					if (aField->m_fieldType == DT_FLAGS)
					{
						if (DefinitionReadFlagField(theXMLParser, aXMLElement.mValue, (unsigned int*)aVarPtr, (DefSymbol*)aField->m_extraData))
							goto done;
					}

					if (wcscasecmp_prime(aXMLElement.mValue.c_str(), aField->m_fieldName) == 0)
					{
						bool aOK;
						switch (aField->m_fieldType)
						{
						case DT_INT:
							aOK = DefinitionReadIntField(theXMLParser, (int*)aVarPtr);
							break;
						case DT_FLOAT:
							aOK = DefinitionReadFloatField(theXMLParser, (float*)aVarPtr);
							break;
						case DT_STRING:
							aOK = DefinitionReadStringField(theXMLParser, (SexyChar**)aVarPtr);
							break;
						case DT_ENUM:
							aOK = DefinitionReadEnumField(theXMLParser, (int*)aVarPtr, (DefSymbol*)aField->m_extraData);
							break;
						case DT_VECTOR2:
							aOK = DefinitionReadVector2Field(theXMLParser, (Sexy::SexyVector2*)aVarPtr);
							break;
						case DT_VECTOR3:
							aOK = DefinitionReadVector3Field(theXMLParser, (Sexy::SexyVector3*)aVarPtr);
							break;
						case DT_RECT:
							aOK = DefinitionReadRectField(theXMLParser, (Sexy::Rect*)aVarPtr);
							break;
						case DT_BOOL:
							aOK = DefinitionReadBoolField(theXMLParser, (bool*)aVarPtr);
							break;
						case DT_ARRAY:
							aOK = DefinitionReadArrayField(theXMLParser, (DefinitionArrayDef*)aVarPtr, aField);
							break;
						case DT_ARRAY_SSL_KEY:
							aOK = DefinitionReadSpaceSeparatedListWithKey(theXMLParser, (SSListKey*)aVarPtr, (DefSymbol*)aField->m_extraData);
							break;
						case DT_TRACK_FLOAT:
							aOK = DefinitionReadFloatTrackField(theXMLParser, (FloatParameterTrack*)aVarPtr);
							break;
						case DT_IMAGE:
							aOK = DefinitionReadImageField(theXMLParser, (Sexy::Image**)aVarPtr);
							break;
						case DT_FONT:
							aOK = DefinitionReadFontField(theXMLParser, (Sexy::Font**)aVarPtr);
							break;
						case DT_INT_SSL:
							aOK = DefinitionReadSpaceSeparatedList(theXMLParser, (std::vector<int>*)aVarPtr);
							break;
						default:
							aOK = false;
							break;
						}

						if (!aOK)
						{
							DefinitionXmlError(theXMLParser, L"Failed to read '%s' field", aField->m_fieldName);
							aResult = aFailed;
						}
						goto done;
					}
					aField++;
				}

				DefinitionXmlError(theXMLParser, L"Ignoring unknown element '%s'", aXMLElement.mValue.c_str());
				aResult = aFailed;
			
			}
		}


	done:
		aFailed = aResult;
	}
	return aFailed;
}

bool DefinitionReadSpaceSeparatedListWithKey(Sexy::XMLParser* theXMLParser, SSListKey* theKey, DefSymbol* theSymbolMap)
{
	SexyString aStringValue;
	bool aResult = DefinitionReadXMLString(theXMLParser, &aStringValue);
	if (aResult)
	{
		const SexyChar* aSrc = aStringValue.c_str();
		DefSkipSpaces(aSrc);

		size_t aKeyLen = aStringValue.find(L' ', 0);
		if (aKeyLen == SexyString::npos)
		{
			aResult = false;
			DefinitionXmlError(theXMLParser, L"Key wasn't found in value '%s'", aStringValue.c_str());
		}
		else
		{
			SexyString aKeyString(aKeyLen, L' ');
			if (swscanf(aSrc, L"%ls", aKeyString.c_str()) == 1)
			{
				int aKeyIndex;
				aResult = DefSymbolValueFromString(theSymbolMap, aKeyString.c_str(), &aKeyIndex);
				if (!aResult)
				{
					DefinitionXmlError(theXMLParser, L"Can't parse key from key value '%s'", aStringValue.c_str());
				}
				else if (aKeyIndex < 0 || theKey->m_keyCount <= aKeyIndex)
				{
					aResult = false;
					DefinitionXmlError(theXMLParser, L"Can't add vector data to invalid index", aStringValue.c_str());
				}
				else
				{
					int aDataIndex = 0;
					aSrc += wcslen(aKeyString.c_str());
					DefSkipSpaces(aSrc);

					std::string aValueString;
					unsigned int aValue = 0;
					while (swscanf(aSrc, L"%d", &aValue) == 1)
					{
						CharArrayData* aData = &theKey->m_key[aKeyIndex];
						unsigned int aCount = aData->m_dataCount;
						if (aCount == 0)
						{
							aData->m_dataCount = 1;
							aData->m_data = (char*)DefinitionAlloc(1);
							aData = &theKey->m_key[aKeyIndex];
						}
						else
						{
							if (DefIsPowerOfTwo(aCount))
							{
								char* aOldData = aData->m_data;
								aData->m_data = (char*)DefinitionAlloc(aCount << 1);
								memcpy(theKey->m_key[aKeyIndex].m_data, aOldData, aData->m_dataCount);
								DefinitionFree(aOldData);
								aData = &theKey->m_key[aKeyIndex];
								aCount = aData->m_dataCount;
							}
							aData->m_dataCount = aCount + 1;
						}

						if (aValue == 1)
							aData->m_data[aDataIndex] = 1;
						else
							aData->m_data[aDataIndex] = 0;
						aDataIndex++;

						aValueString = Sexy::StrFormat("%d", aValue, aDataIndex);
						aSrc += aValueString.length();
						DefSkipSpaces(aSrc);
					}
				}
			}
			else
			{
				aResult = false;
				DefinitionXmlError(theXMLParser, L"Can't parse key from value '%s'", aStringValue.c_str());
			}
		}
	}
	return aResult;
}

unsigned char* DefinitionCompressCompiledBuffer(unsigned char* theData, unsigned int theSize, unsigned int* theOutSize)
{
	unsigned int aDestSize = theSize / 100 + 12 + theSize;
	unsigned char* aBuffer = (unsigned char*)DefinitionAlloc(aDestSize + 16);
	unsigned long aDestLen = aDestSize;
	compress(aBuffer + 16, &aDestLen, theData, theSize);
	*(unsigned long*)(aBuffer + 8) = theSize;
	*(unsigned int*)aBuffer = 0xDEADFED4;
	*theOutSize = aDestLen + 16;
	return aBuffer;
}

unsigned char* DefinitionUncompressCompiledBuffer(unsigned char* theData, unsigned int theSize, unsigned int* theOutSize, const std::string& theFilename)
{
	if (theSize < 16)
		return NULL;
	if (*(unsigned int*)theData != 0xDEADFED4)
		return NULL;

	unsigned char* aBuffer = (unsigned char*)DefinitionAlloc(*(int*)(theData + 8));
	unsigned long aDestLen = *(unsigned long*)(theData + 8);
	uncompress(aBuffer, &aDestLen, theData + 16, theSize - 16);
	*theOutSize = *(unsigned long*)(theData + 8);
	return aBuffer;
}

bool DefinitionLoadImage(Sexy::Image** theImage, const std::string& thePath)
{
	Sexy::Image::InfoClass* anInfo = Sexy::gSexyAppBase->mResourceManager->GetResInfoForStringIdT<Sexy::Image>(thePath);
	*theImage = NULL;
	if (anInfo != NULL)
	{
		*theImage = anInfo->GetImage();
		return true;
	}
	return false;
}

int DefinitionCalcHashDefMap(int theHash, DefMap* theDefMap, TodList<DefMap*>& theDefMapList)
{
	if (theDefMapList.Find(theDefMap) == NULL)
	{
		theDefMapList.AddTail(theDefMap);
		theHash = TodCrc32(theHash, &theDefMap->m_defSize, 4);
		for (DefField* aField = theDefMap->m_mapFields; *aField->m_fieldName != 0; aField++)
		{
			theHash = TodCrc32(theHash, &aField->m_fieldType, 4);
			theHash = TodCrc32(theHash, &aField->m_fieldOffset, 4);
			if (aField->m_fieldType == DT_ARRAY)
				theHash = DefinitionCalcHashDefMap(theHash, (DefMap*)aField->m_extraData, theDefMapList);
			else if (aField->m_fieldType == DT_ENUM || aField->m_fieldType == DT_FLAGS)
				theHash = DefinitionCalcHashSymbolMap(theHash, (DefSymbol*)aField->m_extraData);
		}
	}
	return theHash;
}

int DefinitionCalcHash(DefMap* theDefMap)
{
	TodList<DefMap*> aDefMapList;
	int aHash = TodCrc32(0, NULL, 0) + 1;
	return DefinitionCalcHashDefMap(aHash, theDefMap, aDefMapList);
}

void DefMapWriteToCache(void** theWritePtr, DefMap* theDefMap, void* theDefinition)
{
	for (DefField* aField = theDefMap->m_mapFields; *aField->m_fieldName != 0; aField++)
	{
		void* aVarPtr = (char*)theDefinition + aField->m_fieldOffset;
		switch (aField->m_fieldType)
		{
		case DT_STRING:
			DefWriteToCacheString(theWritePtr, *(SexyChar**)aVarPtr);
			break;
		case DT_ARRAY:
			DefWriteToCacheArray(theWritePtr, (DefinitionArrayDef*)aVarPtr, (DefMap*)aField->m_extraData);
			break;
		case DT_ARRAY_SSL_KEY:
			DefWriteToCacheArraySSLKeyBool(theWritePtr, (SSListKey*)aVarPtr);
			break;
		case DT_TRACK_FLOAT:
			DefWriteToCacheFloatTrack(theWritePtr, (FloatParameterTrack*)aVarPtr);
			break;
		case DT_IMAGE:
			DefWriteToCacheImage(theWritePtr, (Sexy::Image**)aVarPtr);
			break;
		case DT_FONT:
			DefWriteToCacheFont(theWritePtr, (Sexy::Font**)aVarPtr);
			break;
		default:
			break;
		}
	}
}

void DefWriteToCacheArray(void** theWritePtr, DefinitionArrayDef* theArray, DefMap* theElementMap)
{
	Sexy::SMemW(theWritePtr, &theElementMap->m_defSize, 4);
	Sexy::SMemW(theWritePtr, theArray->m_arrayData, theArray->m_arrayCount * theElementMap->m_defSize);
	for (int i = 0; i < theArray->m_arrayCount; i++)
		DefMapWriteToCache(theWritePtr, theElementMap, (char*)theArray->m_arrayData + i * theElementMap->m_defSize);
}

bool DefMapReadFromCache(void** theReadPtr, DefMap* theDefMap, void* theDefinition)
{
	for (DefField* aField = theDefMap->m_mapFields; *aField->m_fieldName != 0; aField++)
	{
		void* aVarPtr = (char*)theDefinition + aField->m_fieldOffset;
		switch (aField->m_fieldType)
		{
		case DT_STRING:
			if (!DefReadFromCacheString(theReadPtr, (SexyChar**)aVarPtr))
				return false;
			break;
		case DT_ARRAY:
			if (!DefReadFromCacheArray(theReadPtr, (DefinitionArrayDef*)aVarPtr, (DefMap*)aField->m_extraData))
				return false;
			break;
		case DT_ARRAY_SSL_KEY:
			if (!DefReadFromCacheArraySSLKeyBool(theReadPtr, (SSListKey*)aVarPtr))
				return false;
			break;
		case DT_TRACK_FLOAT:
			if (!DefReadFromCacheFloatTrack(theReadPtr, (FloatParameterTrack*)aVarPtr))
				return false;
			break;
		case DT_IMAGE:
			if (!DefReadFromCacheImage(theReadPtr, (Sexy::Image**)aVarPtr))
				return false;
			break;
		case DT_FONT:
			if (!DefReadFromCacheFont(theReadPtr, (Sexy::Font**)aVarPtr))
				return false;
			break;
		default:
			break;
		}
	}
	return true;
}

bool DefReadFromCacheArray(void** theReadPtr, DefinitionArrayDef* theArray, DefMap* theElementMap)
{
	int aSize;
	Sexy::SMemR(theReadPtr, &aSize, 4);
	if (theElementMap->m_defSize != aSize)
		return false;

	if (theArray->m_arrayCount != 0)
	{
		theArray->m_arrayData = DefinitionAlloc(theElementMap->m_defSize * theArray->m_arrayCount);
		Sexy::SMemR(theReadPtr, theArray->m_arrayData, theArray->m_arrayCount * theElementMap->m_defSize);
		for (int i = 0; i < theArray->m_arrayCount; i++)
		{
			if (!DefMapReadFromCache(theReadPtr, theElementMap, (char*)theArray->m_arrayData + i * theElementMap->m_defSize))
				return false;
		}
	}
	return true;
}

static bool DefinitionCacheEnabled()
{
	return false;
}

static void* DefinitionCacheBegin(const std::string& theName, int theSize)
{
	return NULL;
}

static bool DefinitionCacheLoad(const std::string& theFilePath, const std::string& theName, DefMap* theDefMap, void* theDefinition)
{
	return false;
}

static void DefinitionCacheEnd(const std::string& theName, void* theBuffer)
{
}

bool DefinitionReadFromCache(const std::string& theFilePath, DefMap* theDefMap, void* theDefinition)
{
	std::string aFullPath = Sexy::GetFullPath(theFilePath);
	DefinitionCacheLoad(aFullPath, std::string("TodDefinition"), theDefMap, theDefinition);
	return false;
}

void DefinitionWriteToCache(const std::string& theFilePath, DefMap* theDefMap, void* theDefinition)
{
	if (DefinitionCacheEnabled())
	{
		DefinitionGetSize(theDefMap, theDefinition);
		void* aBuffer = DefinitionCacheBegin(std::string("TodDefinition"), 0);
		if (aBuffer != NULL)
		{
			void* aWritePtr = aBuffer;
			int aHash = DefinitionCalcHash(theDefMap);
			Sexy::SMemW(&aWritePtr, &aHash, 4);
			Sexy::SMemW(&aWritePtr, theDefinition, theDefMap->m_defSize);
			DefMapWriteToCache(&aWritePtr, theDefMap, theDefinition);
			DefinitionCacheEnd(std::string("TodDefinition"), aBuffer);
		}
	}
}

bool DefinitionWriteCompiledFile(const std::string& theCompiledFilePath, DefMap* theDefMap, void* theDefinition)
{
	long aSize = (long)DefinitionGetSize(theDefMap, theDefinition) + 4;
	void* aBuffer = DefinitionAlloc(aSize);
	void* aWritePtr = aBuffer;
	int aHash = DefinitionCalcHash(theDefMap);
	Sexy::SMemW(&aWritePtr, &aHash, 4);
	Sexy::SMemW(&aWritePtr, theDefinition, theDefMap->m_defSize);
	DefMapWriteToCache(&aWritePtr, theDefMap, theDefinition);

	unsigned int aCompressedSize;
	unsigned char* aCompressed = DefinitionCompressCompiledBuffer((unsigned char*)aBuffer, aSize, &aCompressedSize);
	DefinitionFree(aBuffer);

	Sexy::MkDir(Sexy::GetFileDir(theCompiledFilePath, false));
	FILE* aFile = fopen(theCompiledFilePath.c_str(), "wb");
	if (aFile == NULL)
	{
		DefinitionFree(aCompressed);
		return false;
	}

	size_t aWritten = fwrite(aCompressed, 1, aCompressedSize, aFile);
	DefinitionFree(aCompressed);
	fclose(aFile);
	return aWritten == aCompressedSize;
}
