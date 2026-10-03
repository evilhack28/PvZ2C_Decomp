//
//  BigInt.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-10-03.
//

#include "SexyAppFramework/Crypt/BigInt.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

/////////////// Construction ///////////////

BigInt::BigInt()
{
	mNeg = false;
	mWords = NULL;
	mNumWords = 0;
	mAllocWords = 0;
}

BigInt::BigInt(const BigInt& theBigInt)
{
	mWords = NULL;
	mNumWords = 0;
	mAllocWords = 0;
	*this = theBigInt;
}

BigInt::~BigInt()
{
	delete [] mWords;
}

BigInt::BigInt(const std::string& theString)
{
	mWords = NULL;
	mNumWords = 0;
	mAllocWords = 0;

	for (int i = 0; i < (int) theString.length(); i++)
	{
		uchar aChar = theString[i];
		int aVal = 0;
		if (aChar >= '0' && aChar <= '9')
			aVal = aChar - '0';
		else if (aChar >= 'a' && aChar <= 'f')
			aVal = aChar - 'a' + 10;
		if (aChar >= 'A' && aChar <= 'F')
			aVal = aChar - 'A' + 10;

		*this <<= 4;
		*this |= BigInt(aVal);
	}
}

/////////////// Storage ///////////////

void BigInt::Resize(int theNewSize)
{
	ushort* aNewWords = new ushort[mAllocWords = theNewSize];
	if (mNumWords > 0)
		memcpy(aNewWords, mWords, mNumWords * sizeof(ushort));
	delete [] mWords;
	mWords = aNewWords;
}

BigInt::BigInt(int theInt)
{
	mWords = new ushort[8];
	mAllocWords = 8;
	mNumWords = 2;

	if (theInt < 0)
	{
		mNeg = true;
		theInt = -theInt;
	}
	else
		mNeg = false;

	mWords[0] = (ushort) theInt;
	mWords[1] = (ushort) (theInt >> 16);
	Trim();
}

BigInt::BigInt(int64 theInt)
{
	mWords = new ushort[8];
	mAllocWords = 8;
	mNumWords = 4;

	if (theInt < 0)
	{
		mNeg = true;
		theInt = -theInt;
	}
	else
		mNeg = false;

	mWords[0] = (ushort) theInt;
	mWords[1] = (ushort) (theInt >> 16);
	mWords[2] = (ushort) (theInt >> 32);
	mWords[3] = (ushort) (theInt >> 48);
	Trim();
}

void BigInt::DoubleSize()
{
	if (mAllocWords == 0)
		Resize(8);
	else
		Resize(mAllocWords * 2);
}

void BigInt::Trim()
{
	while ((mNumWords > 0) && (mWords[mNumWords - 1] == 0))
		mNumWords--;
}

void BigInt::SetZero()
{
	mNeg = false;
	mNumWords = 0;
}

bool BigInt::IsEven()
{
	if (mNumWords == 0)
		return true;
	return (mWords[0] & 1) == 0;
}

bool BigInt::IsOdd()
{
	if (mNumWords == 0)
		return false;
	return (mWords[0] & 1) != 0;
}

void BigInt::SetWord(int theWordIdx, ushort theValue)
{
	while (theWordIdx > mNumWords)
	{
		if (mAllocWords <= mNumWords)
			DoubleSize();
		mWords[mNumWords++] = 0;
	}

	if (theWordIdx < mNumWords)
	{
		mWords[theWordIdx] = theValue;
	}
	else
	{
		if (mAllocWords <= mNumWords)
			DoubleSize();
		mWords[mNumWords++] = theValue;
	}
}

void BigInt::SetBit(int theBitNum)
{
	int aWordIdx = theBitNum / 16;
	if (aWordIdx >= mNumWords)
		SetWord(aWordIdx, 1 << (theBitNum % 16));
	mWords[aWordIdx] |= 1 << (theBitNum % 16);
}

/////////////// Shifts ///////////////

BigInt& BigInt::ShiftLeft(int theNumBits)
{
	int aNumWords = NumWords();
	int aWordShift = theNumBits / 16;
	if (aWordShift > 0)
	{
		while (mNumWords + aWordShift > mAllocWords)
			DoubleSize();

		memcpy(&mWords[aWordShift], mWords, mNumWords * sizeof(ushort));
		for (int i = 0; i < aWordShift; i++)
			mWords[i] = 0;
		mNumWords += aWordShift;
	}

	int aCarry = 0;
	for (int i = 0; i < aNumWords; i++)
	{
		int aVal = (GetWord(i + aWordShift) << (theNumBits % 16)) + aCarry;
		aCarry = aVal >> 16;
		SetWord(i + aWordShift, aVal);
	}
	if (aCarry != 0)
		SetWord(aNumWords + aWordShift, aCarry);

	return *this;
}

BigInt& BigInt::ShiftRight(int theNumBits)
{
	int aWordShift = theNumBits / 16;
	if (aWordShift > 0)
	{
		if (mNumWords <= aWordShift)
		{
			mNumWords = 0;
			mNeg = false;
			return *this;
		}

		mNumWords -= aWordShift;
		memcpy(mWords, &mWords[aWordShift], mNumWords * sizeof(ushort));
	}

	int aCarry = 0;
	for (int i = NumWords() - 1; i >= 0; i--)
	{
		int aWord = GetWord(i);
		int aHigh = aCarry;
		aCarry = (aWord << (16 - theNumBits % 16)) & 0xFFFF;
		SetWord(i, (aWord >> (theNumBits % 16)) + aHigh);
	}

	Trim();
	return *this;
}

/////////////// Number theory ///////////////

BigInt BigInt::Gcd(const BigInt& theBigInt)
{
	BigInt aTemp;
	BigInt aX(*this);
	BigInt aY(theBigInt);
	aX.mNeg = false;
	aY.mNeg = false;

	if (aX.mNumWords == 0 && aY.mNumWords == 0)
		return 0;

	aTemp = aY;
	while (aX.mNumWords > 0)
	{
		aTemp = aX;
		aX = aY % aX;
		aY = aTemp;
	}

	return aTemp;
}

/////////////// Conversion ///////////////

std::string BigInt::ToHex() const
{
	if (mNumWords == 0)
		return "0";

	std::string aResult;
	for (int i = mNumWords - 1; i >= 0; i--)
	{
		char aBuf[8];
		ushort aWord = mWords[i];
		if (i == mNumWords - 1)
			sprintf(aBuf, "%X", aWord);
		else
			sprintf(aBuf, "%04X", aWord);
		aResult += aBuf;
	}

	return aResult;
}

/////////////// Random ///////////////

BigInt BigInt::RandNum(int theNumBits)
{
	BigInt aResult;
	for (int i = 0; i < theNumBits / 16; i++)
	{
		int a = rand() & 0xFF;
		int b = rand();
		aResult <<= 16;
		aResult += BigInt((int) (ushort) (a | (b << 8)));
	}

	aResult <<= theNumBits % 16;
	ushort aWord = (rand() & 0xFF) | ((rand() & 0xFF) << 8);
	aResult += BigInt(aWord >> (16 - theNumBits % 16));
	return aResult;
}

/////////////// Comparison ///////////////

bool BigInt::operator<(const BigInt& theBigInt) const
{
	if (IsNegative())
	{
		if (!theBigInt.IsNegative())
			return true;

		if (mNumWords > theBigInt.mNumWords)
			return true;
		if (mNumWords < theBigInt.mNumWords)
			return false;

		for (int i = mNumWords - 1; i >= 0; i--)
		{
			if (mWords[i] < theBigInt.mWords[i])
				return false;
			if (mWords[i] > theBigInt.mWords[i])
				return true;
		}

		return false;
	}

	if (theBigInt.IsNegative())
		return false;

	if (mNumWords > theBigInt.mNumWords)
		return false;
	if (mNumWords < theBigInt.mNumWords)
		return true;

	for (int i = mNumWords - 1; i >= 0; i--)
	{
		if (mWords[i] < theBigInt.mWords[i])
			return true;
		if (mWords[i] > theBigInt.mWords[i])
			return false;
	}

	return false;
}

/////////////// Arithmetic ///////////////

BigInt BigInt::operator*(const BigInt& theBigInt) const
{
	BigInt aResult;
	for (int i = 0; i < theBigInt.NumWords(); i++)
	{
		ushort aMul = theBigInt.GetWord(i);
		uint aCarry = 0;
		BigInt aPartial;
		for (int j = 0; j < NumWords(); j++)
		{
			uint aProduct = aCarry + GetWord(j) * aMul;
			aCarry = aProduct >> 16;
			aPartial.SetWord(i + j, (ushort) aProduct);
		}

		if (aCarry != 0)
			aPartial.SetWord(i + NumWords(), (ushort) aCarry);

		aResult += aPartial;
	}

	aResult.mNeg = theBigInt.IsNegative() ^ IsNegative();
	return aResult;
}

BigInt BigInt::ModPow(const BigInt& thePower, const BigInt& theMod) const
{
	BigInt aResult(1);
	BigInt aBase(*this);
	BigInt aPower(thePower);

	while (aPower > BigInt(0))
	{
		if (aPower.IsOdd())
			aResult = (aResult * aBase) % theMod;

		aPower >>= 1;
		aBase = (aBase * aBase) % theMod;
	}

	return aResult;
}

BigInt BigInt::operator+(const BigInt& theBigInt) const
{
	if (theBigInt.IsNegative())
		return *this - -theBigInt;
	if (IsNegative())
		return theBigInt - -*this;

	BigInt aResult;
	int aNumWords = std::max(NumWords(), theBigInt.NumWords());
	int aCarry = 0;
	int i;
	for (i = 0; i < aNumWords; i++)
	{
		int aSum = GetWord(i) + theBigInt.GetWord(i) + aCarry;
		aResult.SetWord(i, aSum);
		aCarry = aSum >> 16;
	}
	if (aCarry > 0)
		aResult.SetWord(i, aCarry);

	return aResult;
}

BigInt BigInt::operator-(const BigInt& theBigInt) const
{
	if (theBigInt.IsNegative())
		return *this + -theBigInt;
	if (IsNegative())
		return -(-*this + theBigInt);
	if (theBigInt > *this)
		return -(theBigInt - *this);

	BigInt aResult;
	int aNumWords = std::max(NumWords(), theBigInt.NumWords());
	int aBorrow = 0;
	for (int i = 0; i < aNumWords; i++)
	{
		int aVal = GetWord(i) - theBigInt.GetWord(i) - aBorrow;
		aBorrow = 0;
		if (aVal < 0)
		{
			aVal += 0x10000;
			aBorrow = 1;
		}

		aResult.SetWord(i, aVal);
	}

	aResult.Trim();
	return aResult;
}

/////////////// Division ///////////////

void BigInt::Divide(const BigInt& theDivisor, BigInt& theQuotient, BigInt& theRemainder) const
{
	theQuotient.SetZero();
	if (theDivisor > *this)
	{
		theRemainder = *this;
		return;
	}

	int aBits = NumBits();
	int aShift = aBits - theDivisor.NumBits();
	theRemainder = *this;
	if (theRemainder.mAllocWords == 0)
		theRemainder.DoubleSize();
	theRemainder.ShiftRight(aShift + 1);

	for (int aBitNum = aShift; aBitNum >= 0; aBitNum--)
	{
		int aNumWords = theRemainder.mNumWords;
		if (aNumWords > 0)
		{
			int aCarry = 0;
			for (int i = 0; i < aNumWords; i++)
			{
				aCarry += theRemainder.mWords[i] * 2;
				theRemainder.mWords[i] = aCarry;
				aCarry >>= 16;
			}

			if (aCarry != 0)
			{
				if (theRemainder.mAllocWords == aNumWords)
				{
					theRemainder.DoubleSize();
					aNumWords = theRemainder.mNumWords;
				}

				theRemainder.mNumWords = aNumWords + 1;
				theRemainder.mWords[aNumWords] = 1;
			}
		}

		int aWordIdx = aBitNum >> 4;
		int aBit = aBitNum & 0xF;
		if ((mWords[aWordIdx] >> aBit) & 1)
		{
			if (theRemainder.mNumWords == 0)
			{
				theRemainder.mNumWords = 1;
				theRemainder.mWords[0] = 1;
			}
			else
				theRemainder.mWords[0] |= 1;
		}

		if (theRemainder >= theDivisor)
		{
			if (aWordIdx < theQuotient.mNumWords)
				theQuotient.mWords[aWordIdx] |= 1 << aBit;
			else
			{
				while (theQuotient.mAllocWords <= aWordIdx)
					theQuotient.DoubleSize();
				while (aWordIdx > theQuotient.mNumWords)
					theQuotient.mWords[theQuotient.mNumWords++] = 0;
				theQuotient.mWords[theQuotient.mNumWords++] = 1 << aBit;
			}

			int aDivWords = theDivisor.mNumWords;
			if (aDivWords > 0)
			{
				int aBorrow = 0;
				for (int i = 0; i < aDivWords; i++)
				{
					int aVal = theRemainder.mWords[i] - theDivisor.mWords[i] - aBorrow;
					theRemainder.mWords[i] = aVal;
					aBorrow = aVal < 0;
				}

				if (aBorrow != 0)
				{
					ushort aWord = theRemainder.mWords[aDivWords] - 1;
					if (aWord == 0xFFFF)
						aWord = 0xFFFE;
					theRemainder.mWords[aDivWords] = aWord;
				}
			}

			while ((theRemainder.mNumWords > 0) && (theRemainder.mWords[theRemainder.mNumWords - 1] == 0))
				theRemainder.mNumWords--;
		}
	}

	theQuotient.mNeg = IsNegative() ^ theDivisor.IsNegative();
}

extern BigInt gSmallPrimes[53];

bool BigInt::IsPrime() const
{
	if (*this == BigInt(0))
		return false;
	if (*this == BigInt(1))
		return false;

	BigInt aQuotient;
	BigInt aRemainder;
	for (int i = 0; i < 53; i++)
	{
		Divide(gSmallPrimes[i], aQuotient, aRemainder);
		if (aRemainder.mNumWords == 0)
			return false;
	}

	BigInt aNMinus1 = *this - BigInt(1);
	int aS = aNMinus1.mWords[0] & 1;
	if (aS != 0)
	{
		BigInt aD = aNMinus1 >> 0;
		return false;
	}

	do
		aS++;
	while (!((aNMinus1.mWords[aS >> 4] >> (aS & 0xF)) & 1));

	BigInt aD = aNMinus1 >> aS;
	int aNumBits = NumBits();
	for (int aRounds = 5; aRounds > 0; aRounds--)
	{
		BigInt aA = RandNum(aNumBits);
		if (aA >= *this)
			aA = aA - *this;
		if (aA == BigInt(0))
			aA = BigInt(1);

		int r = 0;
		BigInt aX = aA.ModPow(aD, *this);
		if (aX != BigInt(1))
		{
			while (aX != aNMinus1)
			{
				aX = aX.ModPow(BigInt(2), *this);
				if (aX == BigInt(1))
					return false;
				if (++r == aS)
					break;
			}

			if (aX != aNMinus1)
				return false;
		}
	}

	return true;
}

BigInt BigInt::InvMod(const BigInt& theModulus)
{
	BigInt aX(*this);
	BigInt aY(theModulus);
	BigInt a1;
	BigInt a2;
	BigInt a3;
	BigInt a4;
	BigInt a5;
	BigInt a6;

	if (aY < aX)
	{
		BigInt aTemp(aY);
		aY = aX;
		aX = aTemp;
	}

	int aShift = 0;
	while (aY.IsEven() && aX.IsEven())
	{
		aShift++;
		aY >>= 1;
		aX >>= 1;
	}

	a1 = 1;
	a2 = 0;
	a3 = aY;
	a4 = aX;
	a5 = aY - BigInt(1);
	a6 = aX;

	for (;;)
	{
		if (a3.IsEven())
		{
			if (a1.IsOdd() || a2.IsOdd())
			{
				a1 += aX;
				a2 += aY;
			}
			a1 >>= 1;
			a2 >>= 1;
			a3 >>= 1;
		}

		if (a6.IsEven() || a3 < a6)
		{
			BigInt aTemp(a1);
			a1 = a4;
			a4 = aTemp;
			aTemp = a2;
			a2 = a5;
			a5 = aTemp;
			aTemp = a3;
			a3 = a6;
			a6 = aTemp;
		}

		if (a3.IsEven())
			continue;

		while (a1 < a4 || a2 < a5)
		{
			a1 += aX;
			a2 += aY;
		}

		a1 -= a4;
		a2 -= a5;
		a3 -= a6;

		if (!(a6 > BigInt(0)))
			break;
	}

	while (a1 > aX && a2 >= aY)
	{
		a1 -= aX;
		a2 -= aY;
	}

	a1 <<= aShift;
	a2 <<= aShift;
	a3 <<= aShift;
	return aY - a2;
}
