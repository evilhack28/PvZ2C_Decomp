//
//  FirstInstructionMap.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-10-14.
//  Based on open-vcdiff (Apache License 2.0, Copyright Google Inc.).
//

#include "open_vcdiff/config.h"
#include "open_vcdiff/instruction_map.h"
#include <string.h>  // memset
#include "open_vcdiff/addrcache.h"
#include "open_vcdiff/vcdiff_defs.h"

namespace open_vcdiff {

static unsigned char FindMaxSize(
    const unsigned char size_array[VCDiffCodeTableData::kCodeTableSize]) {
  unsigned char max_size = size_array[0];
  for (int i = 1; i < VCDiffCodeTableData::kCodeTableSize; ++i) {
    if (size_array[i] > max_size) {
      max_size = size_array[i];
    }
  }
  return max_size;
}

static void ClearSizeOpcodeArray(int length, OpcodeOrNone* array) {
  for (int i = 0; i < length; ++i) {
    array[i] = kNoOpcode;
  }
}

static OpcodeOrNone* NewSizeOpcodeArray(int length) {
  OpcodeOrNone* array = new OpcodeOrNone[length];
  ClearSizeOpcodeArray(length, array);
  return array;
}

/////////////// Lifecycle ///////////////

VCDiffInstructionMap::FirstInstructionMap::FirstInstructionMap(
    int num_insts_and_modes,
    int max_size_1)
    : num_instruction_type_modes_(num_insts_and_modes),
      max_size_1_(max_size_1) {
  first_opcodes_ = new OpcodeOrNone*[num_instruction_type_modes_];
  for (int i = 0; i < num_instruction_type_modes_; ++i) {
    // There must be at least (max_size_1_ + 1) elements in first_opcodes_
    // because the element first_opcodes[max_size_1_] will be referenced.
    first_opcodes_[i] = NewSizeOpcodeArray(max_size_1_ + 1);
  }
}

VCDiffInstructionMap::FirstInstructionMap::~FirstInstructionMap() {
  for (int i = 0; i < num_instruction_type_modes_; ++i) {
    delete[] first_opcodes_[i];
  }
  delete[] first_opcodes_;
}

}
