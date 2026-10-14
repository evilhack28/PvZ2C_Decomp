//
//  VCDiffStreamingEncoder.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-10-14.
//  Based on open-vcdiff (Apache License 2.0, Copyright Google Inc.).
//

#include "open_vcdiff/config.h"
#include "open_vcdiff/checksum.h"
#include "open_vcdiff/encodetable.h"
#include "open_vcdiff/google/output_string.h"
#include "open_vcdiff/google/vcencoder.h"
#include "open_vcdiff/jsonwriter.h"
#include "open_vcdiff/logging.h"
#include "open_vcdiff/unique_ptr.h" // auto_ptr, unique_ptr
#include "open_vcdiff/vcdiffengine.h"
#include "open_vcdiff/vcencoder_impl.h"

namespace open_vcdiff {

/////////////// Lifecycle ///////////////

VCDiffStreamingEncoder::VCDiffStreamingEncoder(
    const HashedDictionary* dictionary,
    VCDiffFormatExtensionFlags format_extensions,
    bool look_for_target_matches)
    : impl_(new VCDiffStreamingEncoderImpl(dictionary,
                                           format_extensions,
                                           look_for_target_matches)) { }

VCDiffStreamingEncoder::~VCDiffStreamingEncoder() { delete impl_; }

bool VCDiffStreamingEncoder::StartEncodingToInterface(
    OutputStringInterface* out) {
  return impl_->StartEncoding(out);
}

/////////////// Logic ///////////////

bool VCDiffStreamingEncoder::EncodeChunkToInterface(
    const char* data,
    size_t len,
    OutputStringInterface* out) {
  return impl_->EncodeChunk(data, len, out);
}

bool VCDiffStreamingEncoder::FinishEncodingToInterface(
    OutputStringInterface* out) {
  return impl_->FinishEncoding(out);
}

}
