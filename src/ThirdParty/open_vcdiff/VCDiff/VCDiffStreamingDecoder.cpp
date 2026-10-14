//
//  VCDiffStreamingDecoder.cpp
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

/////////////// Lifecycle ///////////////

// *** Methods for VCDiffStreamingDecoder

VCDiffStreamingDecoder::VCDiffStreamingDecoder()
: impl_(new VCDiffStreamingDecoderImpl) { }

VCDiffStreamingDecoder::~VCDiffStreamingDecoder() { delete impl_; }

void VCDiffStreamingDecoder::StartDecoding(const char* source, size_t len) {
  impl_->StartDecoding(source, len);
}

/////////////// Logic ///////////////

bool VCDiffStreamingDecoder::DecodeChunkToInterface(
    const char* data,
    size_t len,
    OutputStringInterface* output_string) {
  return impl_->DecodeChunk(data, len, output_string);
}

bool VCDiffStreamingDecoder::FinishDecoding() {
  return impl_->FinishDecoding();
}

bool VCDiffStreamingDecoder::SetMaximumTargetFileSize(
    size_t new_maximum_target_file_size) {
  return impl_->SetMaximumTargetFileSize(new_maximum_target_file_size);
}

bool VCDiffStreamingDecoder::SetMaximumTargetWindowSize(
    size_t new_maximum_target_window_size) {
  return impl_->SetMaximumTargetWindowSize(new_maximum_target_window_size);
}

void VCDiffStreamingDecoder::SetAllowVcdTarget(bool allow_vcd_target) {
  impl_->SetAllowVcdTarget(allow_vcd_target);
}

}
