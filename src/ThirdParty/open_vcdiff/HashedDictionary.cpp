//
//  HashedDictionary.cpp
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

HashedDictionary::HashedDictionary(const char* dictionary_contents,
                                   size_t dictionary_size)
    : engine_(new VCDiffEngine(dictionary_contents, dictionary_size)) { }

HashedDictionary::~HashedDictionary() { delete engine_; }

bool HashedDictionary::Init() {
  return const_cast<VCDiffEngine*>(engine_)->Init();
}

}
