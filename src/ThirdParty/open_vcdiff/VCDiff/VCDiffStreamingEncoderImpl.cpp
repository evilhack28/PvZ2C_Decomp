//
//  VCDiffStreamingEncoderImpl.cpp
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

inline VCDiffStreamingEncoderImpl::VCDiffStreamingEncoderImpl(
    const HashedDictionary* dictionary,
    VCDiffFormatExtensionFlags format_extensions,
    bool look_for_target_matches)
    : engine_(dictionary->engine()),
      format_extensions_(format_extensions),
      look_for_target_matches_(look_for_target_matches),
      encode_chunk_allowed_(false) {
  if (format_extensions & VCD_FORMAT_JSON) {
    coder_.reset(new JSONCodeTableWriter());
  } else {
    // This implementation of the encoder uses the default
    // code table.  A VCDiffCodeTableWriter could also be constructed
    // using a custom code table.
    coder_.reset(new VCDiffCodeTableWriter(
        (format_extensions & VCD_FORMAT_INTERLEAVED) != 0));
  }
}

/////////////// Logic ///////////////

inline bool VCDiffStreamingEncoderImpl::StartEncoding(
    OutputStringInterface* out) {
  if (!coder_->Init(engine_->dictionary_size())) {
    VCD_DFATAL << "Internal error: "
                  "Initialization of code table writer failed" << VCD_ENDL;
    return false;
  }
  if (!coder_->VerifyDictionary(engine_->dictionary(),
                                engine_->dictionary_size())) {
    VCD_ERROR << "Dictionary not valid for writer" << VCD_ENDL;
    return false;
  }
  coder_->WriteHeader(out, format_extensions_);
  encode_chunk_allowed_ = true;
  return true;
}

inline bool VCDiffStreamingEncoderImpl::EncodeChunk(
    const char* data,
    size_t len,
    OutputStringInterface* out) {
  if (!encode_chunk_allowed_) {
    VCD_ERROR << "EncodeChunk called before StartEncoding" << VCD_ENDL;
    return false;
  }
  if (!coder_->VerifyChunk(data, len)) {
    VCD_ERROR << "Target chunk not valid for writer" << VCD_ENDL;
    return false;
  }
  if ((format_extensions_ & VCD_FORMAT_CHECKSUM) != 0) {
    coder_->AddChecksum(ComputeAdler32(data, len));
  }
  engine_->Encode(data, len, look_for_target_matches_, out, coder_.get());
  return true;
}

inline bool VCDiffStreamingEncoderImpl::FinishEncoding(
    OutputStringInterface* out) {
  if (!encode_chunk_allowed_) {
    VCD_ERROR << "FinishEncoding called before StartEncoding" << VCD_ENDL;
    return false;
  }
  encode_chunk_allowed_ = false;
  coder_->FinishEncoding(out);
  return true;
}

}
