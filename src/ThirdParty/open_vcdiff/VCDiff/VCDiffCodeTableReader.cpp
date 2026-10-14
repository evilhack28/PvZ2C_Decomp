//
//  VCDiffCodeTableReader.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-10-14.
//  Based on open-vcdiff (Apache License 2.0, Copyright Google Inc.).
//

#include "open_vcdiff/config.h"
#include "open_vcdiff/decodetable.h"
#include "open_vcdiff/codetable.h"
#include "open_vcdiff/logging.h"
#include "open_vcdiff/varint_bigendian.h"
#include "open_vcdiff/vcdiff_defs.h"

namespace open_vcdiff {

/////////////// Lifecycle ///////////////

VCDiffCodeTableReader::VCDiffCodeTableReader()
    : code_table_data_(&VCDiffCodeTableData::kDefaultCodeTableData),
      non_default_code_table_data_(NULL),
      instructions_and_sizes_(NULL),
      instructions_and_sizes_end_(NULL),
      last_instruction_start_(NULL),
      pending_second_instruction_(kNoOpcode),
      last_pending_second_instruction_(kNoOpcode) {
}

/////////////// Logic ///////////////

bool VCDiffCodeTableReader::UseCodeTable(
    const VCDiffCodeTableData& code_table_data, unsigned char max_mode) {
  if (!code_table_data.Validate(max_mode)) return false;
  if (!non_default_code_table_data_.get()) {
    non_default_code_table_data_.reset(new VCDiffCodeTableData);
  }
  *non_default_code_table_data_ = code_table_data;
  code_table_data_ = non_default_code_table_data_.get();
  return true;
}

VCDiffInstructionType VCDiffCodeTableReader::GetNextInstruction(
    int32_t* size,
    unsigned char* mode) {
  if (!instructions_and_sizes_) {
    VCD_ERROR << "Internal error: GetNextInstruction() called before Init()"
              << VCD_ENDL;
    return VCD_INSTRUCTION_ERROR;
  }
  last_instruction_start_ = *instructions_and_sizes_;
  last_pending_second_instruction_ = pending_second_instruction_;
  unsigned char opcode = 0;
  unsigned char instruction_type = VCD_NOOP;
  int32_t instruction_size = 0;
  unsigned char instruction_mode = 0;
  do {
    if (pending_second_instruction_ != kNoOpcode) {
      // There is a second instruction left over
      // from the most recently processed opcode.
      opcode = static_cast<unsigned char>(pending_second_instruction_);
      pending_second_instruction_ = kNoOpcode;
      instruction_type = code_table_data_->inst2[opcode];
      instruction_size = code_table_data_->size2[opcode];
      instruction_mode = code_table_data_->mode2[opcode];
      break;
    }
    if (*instructions_and_sizes_ >= instructions_and_sizes_end_) {
      // Ran off end of instruction stream
      return VCD_INSTRUCTION_END_OF_DATA;
    }
    opcode = **instructions_and_sizes_;
    if (code_table_data_->inst2[opcode] != VCD_NOOP) {
      // This opcode contains two instructions; process the first one now, and
      // save a pointer to the second instruction, which should be returned
      // by the next call to GetNextInstruction
      pending_second_instruction_ = **instructions_and_sizes_;
    }
    ++(*instructions_and_sizes_);
    instruction_type = code_table_data_->inst1[opcode];
    instruction_size = code_table_data_->size1[opcode];
    instruction_mode = code_table_data_->mode1[opcode];
  // This do-while loop is necessary in case inst1 == VCD_NOOP for an opcode
  // that was actually used in the encoding.  That case is unusual, but it
  // is not prohibited by the standard.
  } while (instruction_type == VCD_NOOP);
  if (instruction_size == 0) {
    // Parse the size as a Varint in the instruction stream.
    switch (*size = VarintBE<int32_t>::Parse(instructions_and_sizes_end_,
                                             instructions_and_sizes_)) {
      case RESULT_ERROR:
        VCD_ERROR << "Instruction size is not a valid variable-length integer"
                  << VCD_ENDL;
        return VCD_INSTRUCTION_ERROR;
      case RESULT_END_OF_DATA:
        UnGetInstruction();  // Rewind to instruction start
        return VCD_INSTRUCTION_END_OF_DATA;
      default:
        break;  // Successfully parsed Varint
    }
  } else {
    *size = instruction_size;
  }
  *mode = instruction_mode;
  return static_cast<VCDiffInstructionType>(instruction_type);
}

}
