//
//  VCDiffInstructionMap.cpp
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

// Because a constructor should never fail, the caller must already
// have run ValidateCodeTable() against the code table data.
//
VCDiffInstructionMap::VCDiffInstructionMap(
    const VCDiffCodeTableData& code_table_data,
    unsigned char max_mode)
    : first_instruction_map_(VCD_LAST_INSTRUCTION_TYPE + max_mode + 1,
                             FindMaxSize(code_table_data.size1)),
      second_instruction_map_(VCD_LAST_INSTRUCTION_TYPE + max_mode + 1,
                              FindMaxSize(code_table_data.size2)) {
  // First pass to fill up first_instruction_map_
  for (int opcode = 0; opcode < VCDiffCodeTableData::kCodeTableSize; ++opcode) {
    if (code_table_data.inst2[opcode] == VCD_NOOP) {
      // Single instruction.  If there is more than one opcode for the same
      // inst, mode, and size, then the lowest-numbered opcode will always
      // be used by the encoder, because of the descending loop.
      first_instruction_map_.Add(code_table_data.inst1[opcode],
                                 code_table_data.size1[opcode],
                                 code_table_data.mode1[opcode],
                                 opcode);
    } else if (code_table_data.inst1[opcode] == VCD_NOOP) {
      // An unusual case where inst1 == NOOP and inst2 == ADD, RUN, or COPY.
      // This is valid under the standard, but unlikely to be used.
      // Add it to the first instruction map as if inst1 and inst2 were swapped.
      first_instruction_map_.Add(code_table_data.inst2[opcode],
                                 code_table_data.size2[opcode],
                                 code_table_data.mode2[opcode],
                                 opcode);
    }
  }
  // Second pass to fill up second_instruction_map_ (depends on first pass)
  for (int opcode = 0; opcode < VCDiffCodeTableData::kCodeTableSize; ++opcode) {
    if ((code_table_data.inst1[opcode] != VCD_NOOP) &&
        (code_table_data.inst2[opcode] != VCD_NOOP)) {
      // Double instruction.  Find the corresponding single instruction opcode
      const OpcodeOrNone single_opcode =
          LookupFirstOpcode(code_table_data.inst1[opcode],
                            code_table_data.size1[opcode],
                            code_table_data.mode1[opcode]);
      if (single_opcode == kNoOpcode) continue;  // No single opcode found
      second_instruction_map_.Add(static_cast<unsigned char>(single_opcode),
                                  code_table_data.inst2[opcode],
                                  code_table_data.size2[opcode],
                                  code_table_data.mode2[opcode],
                                  opcode);
    }
  }
}

/////////////// Logic ///////////////

// VCDiffInstructionMap members and methods

VCDiffInstructionMap* VCDiffInstructionMap::default_instruction_map = NULL;

VCDiffInstructionMap* VCDiffInstructionMap::GetDefaultInstructionMap() {
  if (!default_instruction_map) {
    default_instruction_map = new VCDiffInstructionMap(
        VCDiffCodeTableData::kDefaultCodeTableData,
        VCDiffAddressCache::DefaultLastMode());
  }
  return default_instruction_map;
}

}
