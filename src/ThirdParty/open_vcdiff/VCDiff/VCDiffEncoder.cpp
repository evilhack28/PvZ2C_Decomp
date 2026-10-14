//
//  VCDiffEncoder.cpp
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

/////////////// Logic ///////////////

bool VCDiffEncoder::EncodeToInterface(const char* target_data,
                                      size_t target_len,
                                      OutputStringInterface* out) {
  out->clear();
  if (!encoder_) {
    if (!dictionary_.Init()) {
      VCD_ERROR << "Error initializing HashedDictionary" << VCD_ENDL;
      return false;
    }
    encoder_ = new VCDiffStreamingEncoder(&dictionary_,
                                          flags_,
                                          look_for_target_matches_);
  }
  if (!encoder_->StartEncodingToInterface(out)) {
    return false;
  }
  if (!encoder_->EncodeChunkToInterface(target_data, target_len, out)) {
    return false;
  }
  return encoder_->FinishEncodingToInterface(out);
}

}
