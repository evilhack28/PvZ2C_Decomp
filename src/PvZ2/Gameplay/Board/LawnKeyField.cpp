//
//  LawnKeyField.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-05.
//

#include "SexyAppFramework/Common.h"

#include "LawnKeyField.h"

/////////////// LawnKeyField ///////////////

LawnKeyField::LawnKeyField()
{
	data = 0;
	seednum = MAGIC_SEED_NUM;
}

LawnKeyField::LawnKeyField(int32 value)
{
	data = 0;
	seednum = MAGIC_SEED_NUM;

	U_signed_unsigned u;
	u.int_ = value;
	data = encode(u.long_);
}

void LawnKeyField::updateToAug05LawnKey()
{
	U_signed_unsigned u;
	u.long_ = (data >> MAGIC_SEED_NUM) | (data << (DATA_WIDTH - MAGIC_SEED_NUM));
	this->data = encode(u.long_);
}

LawnKeyField& LawnKeyField::operator= (int32 value)
{
	U_signed_unsigned u;
	u.int_ = value;
	data = encode(u.long_);

	return *this;
}

int32 LawnKeyField::operator +(int32 value)
{
	U_signed_unsigned u;
	u.long_ = decode(data);
	u.int_ += value;
	return u.int_;
}

int32 LawnKeyField::operator -(int32 value)
{
	U_signed_unsigned u;
	u.long_ = decode(data);
	u.int_ -= value;
	return u.int_;
}

LawnKeyField& LawnKeyField::operator +=(int32 value)
{
	U_signed_unsigned u;
	u.long_ = decode(data);
	u.int_ += value;
	data = encode(u.long_);

	return *this;
}

LawnKeyField& LawnKeyField::operator -=(int32 value)
{
	U_signed_unsigned u;
	u.long_ = decode(data);
	u.int_ -= value;
	data = encode(u.long_);

	return *this;
}

bool LawnKeyField::operator <(int32 value)
{
	U_signed_unsigned u;
	u.long_ = decode(data);
	return (u.int_ < value);
}

bool LawnKeyField::operator >(int32 value)
{
	U_signed_unsigned u;
	u.long_ = decode(data);
	return (u.int_ > value);
}

LawnKeyField::operator int32()
{
	U_signed_unsigned u1;
	u1.long_ = decode(data);
	return u1.int_;
}

LawnKeyField::operator int32() const
{
	U_signed_unsigned u1;
	u1.long_ = decode(data);
	return u1.int_;
}
