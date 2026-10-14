//
//  SecondInstructionMap.cpp
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

VCDiffInstructionMap::SecondInstructionMap::SecondInstructionMap(
    int num_insts_and_modes,
    int max_size_2)
    : num_instruction_type_modes_(num_insts_and_modes),
      max_size_2_(max_size_2) {
  memset(second_opcodes_, 0, sizeof(second_opcodes_));
}

VCDiffInstructionMap::SecondInstructionMap::~SecondInstructionMap() {
  for (int opcode = 0; opcode < VCDiffCodeTableData::kCodeTableSize; ++opcode) {
    if (second_opcodes_[opcode] != NULL) {
      for (int inst_mode = 0;
           inst_mode < num_instruction_type_modes_;
           ++inst_mode) {
        // No need to check for NULL
        delete[] second_opcodes_[opcode][inst_mode];
      }
      delete[] second_opcodes_[opcode];
    }
  }
}

/////////////// Logic ///////////////

void VCDiffInstructionMap::SecondInstructionMap::Add(
    unsigned char first_opcode,
    unsigned char inst,
    unsigned char size,
    unsigned char mode,
    unsigned char second_opcode) {
  OpcodeOrNone**& inst_mode_array = second_opcodes_[first_opcode];
  if (!inst_mode_array) {
    inst_mode_array = new OpcodeOrNone*[num_instruction_type_modes_];
    memset(inst_mode_array,
           0,
           num_instruction_type_modes_ * sizeof(inst_mode_array[0]));
  }
  OpcodeOrNone*& size_array = inst_mode_array[inst + mode];
  if (!size_array) {
    // There must be at least (max_size_2_ + 1) elements in size_array
    // because the element size_array[max_size_2_] will be referenced.
    size_array = NewSizeOpcodeArray(max_size_2_ + 1);
  }
  if (size_array[size] == kNoOpcode) {
    size_array[size] = second_opcode;
  }
}

OpcodeOrNone VCDiffInstructionMap::SecondInstructionMap::Lookup(
    unsigned char first_opcode,
    unsigned char inst,
    unsigned char size,
    unsigned char mode) const {
  if (size > max_size_2_) {
    return kNoOpcode;
  }
  const OpcodeOrNone* const * const inst_mode_array =
    second_opcodes_[first_opcode];
  if (!inst_mode_array) {
    return kNoOpcode;
  }
  int inst_mode = (inst == VCD_COPY) ? (inst + mode) : inst;
  const OpcodeOrNone* const size_array = inst_mode_array[inst_mode];
  if (!size_array) {
    return kNoOpcode;
  }
  return size_array[size];
}

}
