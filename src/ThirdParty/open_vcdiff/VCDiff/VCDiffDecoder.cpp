//
//  VCDiffDecoder.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-10-14.
//  Based on open-vcdiff (Apache License 2.0, Copyright Google Inc.).
//

#include "open_vcdiff/config.h"
#include "open_vcdiff/google/vcdecoder.h"
#include <stddef.h>  // size_t, ptrdiff_t
#include <stdint.h>  // int32_t
#include <string.h>  // memcpy, memset
#include <string>
#include "open_vcdiff/addrcache.h"
#include "open_vcdiff/checksum.h"
#include "open_vcdiff/codetable.h"
#include "open_vcdiff/decodetable.h"
#include "open_vcdiff/headerparser.h"
#include "open_vcdiff/logging.h"
#include "open_vcdiff/google/output_string.h"
#include "open_vcdiff/unique_ptr.h" // auto_ptr, unique_ptr
#include "open_vcdiff/varint_bigendian.h"
#include "open_vcdiff/vcdiff_defs.h"

// The FALLTHROUGH_INTENDED macro can be used to annotate implicit fall-through
// between switch labels.
#if defined(__clang__) && __cplusplus >= 201103L && defined(__has_warning)
#if __has_feature(cxx_attributes) && __has_warning("-Wimplicit-fallthrough")
#define FALLTHROUGH_INTENDED [[clang::fallthrough]]  // NOLINT
#endif
#endif

#ifndef FALLTHROUGH_INTENDED
#define FALLTHROUGH_INTENDED do { } while (0)
#endif
#include "open_vcdiff/vcdecoder_impl.h"

namespace open_vcdiff {

/////////////// Logic ///////////////

bool VCDiffDecoder::DecodeToInterface(const char* dictionary_ptr,
                                      size_t dictionary_size,
                                      const string& encoding,
                                      OutputStringInterface* target) {
  target->clear();
  decoder_.StartDecoding(dictionary_ptr, dictionary_size);
  if (!decoder_.DecodeChunkToInterface(encoding.data(),
                                       encoding.size(),
                                       target)) {
    return false;
  }
  return decoder_.FinishDecoding();
}

}
