//
//  md5.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-04.
//

#include "logServer/md5.h"

#include <cstring>

/* Constants for MD5Transform routine. */
#define s11 7
#define s12 12
#define s13 17
#define s14 22
#define s21 5
#define s22 9
#define s23 14
#define s24 20
#define s31 4
#define s32 11
#define s33 16
#define s34 23
#define s41 6
#define s42 10
#define s43 15
#define s44 21

/* F, G, H and I are basic MD5 functions. */
#define F(x, y, z) (((x) & (y)) | (~(x) & (z)))
#define G(x, y, z) (((x) & (z)) | ((y) & ~(z)))
#define H(x, y, z) ((x) ^ (y) ^ (z))
#define I(x, y, z) ((y) ^ ((x) | ~(z)))

/* ROTATE_LEFT rotates x left n bits. */
#define ROTATE_LEFT(x, n) (((x) << (n)) | ((x) >> (32 - (n))))

/* FF, GG, HH, and II transformations for rounds 1, 2, 3, and 4.
Rotation is separate from addition to prevent recomputation. */
#define FF(a, b, c, d, x, s, ac) { \
	(a) += F ((b), (c), (d)) + (x) + ac; \
	(a) = ROTATE_LEFT ((a), (s)); \
	(a) += (b); \
}
#define GG(a, b, c, d, x, s, ac) { \
	(a) += G ((b), (c), (d)) + (x) + ac; \
	(a) = ROTATE_LEFT ((a), (s)); \
	(a) += (b); \
}
#define HH(a, b, c, d, x, s, ac) { \
	(a) += H ((b), (c), (d)) + (x) + ac; \
	(a) = ROTATE_LEFT ((a), (s)); \
	(a) += (b); \
}
#define II(a, b, c, d, x, s, ac) { \
	(a) += I ((b), (c), (d)) + (x) + ac; \
	(a) = ROTATE_LEFT ((a), (s)); \
	(a) += (b); \
}

const byte MD5::PADDING[64] = { 0x80 };
const char MD5::HEX[16] = {
	'0', '1', '2', '3',
	'4', '5', '6', '7',
	'8', '9', 'a', 'b',
	'c', 'd', 'e', 'f'
};

/* Default construct. */
MD5::MD5() {
	reset();
}

/* Construct a MD5 object with a input buffer. */
MD5::MD5(const void* input, size_t length) {
	reset();
	update(input, length);
}

/* Construct a MD5 object with a string. */
MD5::MD5(const string& str) {
	reset();
	update(str);
}

/* Construct a MD5 object with a file. */
MD5::MD5(ifstream& in) {
	reset();
	update(in);
}

/* Return the message-digest */
const byte* MD5::digest() {
	if (!_finished) {
		_finished = true;
		final();
	}
	return _digest;
}

/* Reset the calculate state */
void MD5::reset() {

	_finished = false;
	/* reset number of bits. */
	_count[0] = _count[1] = 0;
	/* Load magic initialization constants. */
	_state[0] = 0x67452301;
	_state[1] = 0xefcdab89;
	_state[2] = 0x98badcfe;
	_state[3] = 0x10325476;
}

/* Updating the context with a input buffer. */
void MD5::update(const void* input, size_t length) {
	update((const byte*)input, length);
}

/* Updating the context with a string. */
void MD5::update(const string& str) {
	update((const byte*)str.c_str(), str.length());
}

/* Updating the context with a file. */
void MD5::update(ifstream& in) {

	if (!in) {
		return;
	}

	std::streamsize length;
	char buffer[BUFFER_SIZE];
	while (!in.eof()) {
		in.read(buffer, BUFFER_SIZE);
		length = in.gcount();
		if (length > 0) {
			update(buffer, length);
		}
	}
	in.close();
}

/* MD5 block update operation. Continues an MD5 message-digest
operation, processing another message block, and updating the
context.
*/
void MD5::update(const byte* input, size_t length) {

	uint32 i, index, partLen;

	_finished = false;

	/* Compute number of bytes mod 64 */
	index = (uint32)((_count[0] >> 3) & 0x3f);

	/* update number of bits */
	if ((_count[0] += ((uint32)length << 3)) < ((uint32)length << 3)) {
		++_count[1];
	}
	_count[1] += ((uint32)length >> 29);

	partLen = 64 - index;

	/* transform as many times as possible. */
	if (length >= partLen) {

		memcpy(&_buffer[index], input, partLen);
		transform(_buffer);

		for (i = partLen; i + 63 < length; i += 64) {
			transform(&input[i]);
		}
		index = 0;

	} else {
		i = 0;
	}

	/* Buffer remaining input */
	memcpy(&_buffer[index], &input[i], length - i);
}

/* MD5 finalization. Ends an MD5 message-digest operation, writing the
the message digest and zeroizing the context.
*/
void MD5::final() {

	byte bits[8];
	uint32 oldState[4];
	uint32 oldCount[2];
	uint32 index, padLen;

	/* Save current state and count. */
	memcpy(oldState, _state, 16);
	memcpy(oldCount, _count, 8);

	/* Save number of bits */
	encode(_count, bits, 8);

	/* Pad out to 56 mod 64. */
	index = (uint32)((_count[0] >> 3) & 0x3f);
	padLen = (index < 56) ? (56 - index) : (120 - index);
	update(PADDING, padLen);

	/* Append length (before padding) */
	update(bits, 8);

	/* Store state in digest */
	encode(_state, _digest, 16);

	/* Restore current state and count. */
	memcpy(_state, oldState, 16);
	memcpy(_count, oldCount, 8);
}

/* MD5 basic transformation. Transforms _state based on block. */
void MD5::transform(const byte block[64]) {

	uint32 a = _state[0], b = _state[1], c = _state[2], d = _state[3], x[16];

	decode(block, x, 64);

	/* Round 1 */
	FF(a, b, c, d, x[0], s11, 0xd76aa478);
	FF(d, a, b, c, x[1], s12, 0xe8c7b756);
	FF(c, d, a, b, x[2], s13, 0x242070db);
	FF(b, c, d, a, x[3], s14, 0xc1bdceee);
	FF(a, b, c, d, x[4], s11, 0xf57c0faf);
	FF(d, a, b, c, x[5], s12, 0x4787c62a);
	FF(c, d, a, b, x[6], s13, 0xa8304613);
	FF(b, c, d, a, x[7], s14, 0xfd469501);
	FF(a, b, c, d, x[8], s11, 0x698098d8);
	FF(d, a, b, c, x[9], s12, 0x8b44f7af);
	FF(c, d, a, b, x[10], s13, 0xffff5bb1);
	FF(b, c, d, a, x[11], s14, 0x895cd7be);
	FF(a, b, c, d, x[12], s11, 0x6b901122);
	FF(d, a, b, c, x[13], s12, 0xfd987193);
	FF(c, d, a, b, x[14], s13, 0xa679438e);
	FF(b, c, d, a, x[15], s14, 0x49b40821);

	/* Round 2 */
	GG(a, b, c, d, x[1], s21, 0xf61e2562);
	GG(d, a, b, c, x[6], s22, 0xc040b340);
	GG(c, d, a, b, x[11], s23, 0x265e5a51);
	GG(b, c, d, a, x[0], s24, 0xe9b6c7aa);
	GG(a, b, c, d, x[5], s21, 0xd62f105d);
	GG(d, a, b, c, x[10], s22, 0x2441453);
	GG(c, d, a, b, x[15], s23, 0xd8a1e681);
	GG(b, c, d, a, x[4], s24, 0xe7d3fbc8);
	GG(a, b, c, d, x[9], s21, 0x21e1cde6);
	GG(d, a, b, c, x[14], s22, 0xc33707d6);
	GG(c, d, a, b, x[3], s23, 0xf4d50d87);
	GG(b, c, d, a, x[8], s24, 0x455a14ed);
	GG(a, b, c, d, x[13], s21, 0xa9e3e905);
	GG(d, a, b, c, x[2], s22, 0xfcefa3f8);
	GG(c, d, a, b, x[7], s23, 0x676f02d9);
	GG(b, c, d, a, x[12], s24, 0x8d2a4c8a);

	/* Round 3 */
	HH(a, b, c, d, x[5], s31, 0xfffa3942);
	HH(d, a, b, c, x[8], s32, 0x8771f681);
	HH(c, d, a, b, x[11], s33, 0x6d9d6122);
	HH(b, c, d, a, x[14], s34, 0xfde5380c);
	HH(a, b, c, d, x[1], s31, 0xa4beea44);
	HH(d, a, b, c, x[4], s32, 0x4bdecfa9);
	HH(c, d, a, b, x[7], s33, 0xf6bb4b60);
	HH(b, c, d, a, x[10], s34, 0xbebfbc70);
	HH(a, b, c, d, x[13], s31, 0x289b7ec6);
	HH(d, a, b, c, x[0], s32, 0xeaa127fa);
	HH(c, d, a, b, x[3], s33, 0xd4ef3085);
	HH(b, c, d, a, x[6], s34, 0x4881d05);
	HH(a, b, c, d, x[9], s31, 0xd9d4d039);
	HH(d, a, b, c, x[12], s32, 0xe6db99e5);
	HH(c, d, a, b, x[15], s33, 0x1fa27cf8);
	HH(b, c, d, a, x[2], s34, 0xc4ac5665);

	/* Round 4 */
	II(a, b, c, d, x[0], s41, 0xf4292244);
	II(d, a, b, c, x[7], s42, 0x432aff97);
	II(c, d, a, b, x[14], s43, 0xab9423a7);
	II(b, c, d, a, x[5], s44, 0xfc93a039);
	II(a, b, c, d, x[12], s41, 0x655b59c3);
	II(d, a, b, c, x[3], s42, 0x8f0ccc92);
	II(c, d, a, b, x[10], s43, 0xffeff47d);
	II(b, c, d, a, x[1], s44, 0x85845dd1);
	II(a, b, c, d, x[8], s41, 0x6fa87e4f);
	II(d, a, b, c, x[15], s42, 0xfe2ce6e0);
	II(c, d, a, b, x[6], s43, 0xa3014314);
	II(b, c, d, a, x[13], s44, 0x4e0811a1);
	II(a, b, c, d, x[4], s41, 0xf7537e82);
	II(d, a, b, c, x[11], s42, 0xbd3af235);
	II(c, d, a, b, x[2], s43, 0x2ad7d2bb);
	II(b, c, d, a, x[9], s44, 0xeb86d391);

	_state[0] += a;
	_state[1] += b;
	_state[2] += c;
	_state[3] += d;
}

/* Encodes input (usigned long) into output (byte). */
void MD5::encode(const uint32* input, byte* output, size_t length) {

	for (size_t i = 0, j = 0; j < length; ++i, j += 4) {
		output[j] = (byte)(input[i] & 0xff);
		output[j + 1] = (byte)((input[i] >> 8) & 0xff);
		output[j + 2] = (byte)((input[i] >> 16) & 0xff);
		output[j + 3] = (byte)((input[i] >> 24) & 0xff);
	}
}

/* Decodes input (byte) into output (usigned long). Assumes length is
a multiple of 4.
*/
void MD5::decode(const byte* input, uint32* output, size_t length) {

	for (size_t i = 0, j = 0; j < length; ++i, j += 4) {
		output[i] = ((uint32)input[j]) | (((uint32)input[j + 1]) << 8) |
			(((uint32)input[j + 2]) << 16) | (((uint32)input[j + 3]) << 24);
	}
}

/* Convert byte array to hex string. */
string MD5::bytesToHexString(const byte* input, size_t length) {

	string str;
	str.reserve(length << 1);
	for (size_t i = 0; i < length; ++i) {
		int t = input[i];
		int a = t / 16;
		int b = t % 16;
		str.append(1, HEX[a]);
		str.append(1, HEX[b]);
	}

	return str;
}

/* Convert digest to string value */
string MD5::toString() {
	return bytesToHexString(digest(), 16);
}
