//
//  ParseableChunk.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-10-14.
//  Based on open-vcdiff (Apache License 2.0, Copyright Google Inc.).
//

#include "open_vcdiff/config.h"
#include "open_vcdiff/headerparser.h"
#include "open_vcdiff/logging.h"
#include "open_vcdiff/varint_bigendian.h"
#include "open_vcdiff/vcdiff_defs.h"

namespace open_vcdiff {

/////////////// Logic ///////////////

// *** Methods for ParseableChunk

void ParseableChunk::Advance(size_t number_of_bytes) {
  if (number_of_bytes > UnparsedSize()) {
    VCD_DFATAL << "Internal error: position advanced by " << number_of_bytes
               << " bytes, current unparsed size " << UnparsedSize()
               << VCD_ENDL;
    position_ = end_;
    return;
  }
  position_ += number_of_bytes;
}

void ParseableChunk::SetPosition(const char* position) {
  if (position < start_) {
    VCD_DFATAL << "Internal error: new data position " << position
               << " is beyond start of data " << start_ << VCD_ENDL;
    position_ = start_;
    return;
  }
  if (position > end_) {
    VCD_DFATAL << "Internal error: new data position " << position
               << " is beyond end of data " << end_ << VCD_ENDL;
    position_ = end_;
    return;
  }
  position_ = position;
}

void ParseableChunk::FinishExcept(size_t number_of_bytes) {
  if (number_of_bytes > UnparsedSize()) {
    VCD_DFATAL << "Internal error: specified number of remaining bytes "
               << number_of_bytes << " is greater than unparsed data size "
               << UnparsedSize() << VCD_ENDL;
    Finish();
    return;
  }
  position_ = end_ - number_of_bytes;
}

}
