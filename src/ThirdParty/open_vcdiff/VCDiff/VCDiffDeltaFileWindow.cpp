//
//  VCDiffDeltaFileWindow.cpp
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

// *** Inline methods for VCDiffDeltaFileWindow

inline VCDiffDeltaFileWindow::VCDiffDeltaFileWindow() : parent_(NULL) {
  Reset();
}

inline VCDiffDeltaFileWindow::~VCDiffDeltaFileWindow() { }

inline void VCDiffDeltaFileWindow::Init(VCDiffStreamingDecoderImpl* parent) {
  parent_ = parent;
}

/////////////// Logic ///////////////

// *** Methods for VCDiffDeltaFileWindow

void VCDiffDeltaFileWindow::Reset() {
  found_header_ = false;

  // Mark the start of the current target window.
  target_window_start_pos_ = parent_ ? parent_->decoded_target()->size() : 0U;
  target_window_length_ = 0;

  source_segment_ptr_ = NULL;
  source_segment_length_ = 0;

  instructions_and_sizes_.Invalidate();
  data_for_add_and_run_.Invalidate();
  addresses_for_copy_.Invalidate();

  interleaved_bytes_expected_ = 0;

  has_checksum_ = false;
  expected_checksum_ = 0;
}

VCDiffResult VCDiffDeltaFileWindow::SetUpWindowSections(
    VCDiffHeaderParser* header_parser) {
  size_t add_and_run_data_length = 0;
  size_t instructions_and_sizes_length = 0;
  size_t addresses_length = 0;
  if (!header_parser->ParseSectionLengths(has_checksum_,
                                          &add_and_run_data_length,
                                          &instructions_and_sizes_length,
                                          &addresses_length,
                                          &expected_checksum_)) {
    return header_parser->GetResult();
  }
  if (parent_->AllowInterleaved() &&
      (add_and_run_data_length == 0) &&
      (addresses_length == 0)) {
    // The interleaved format is being used.
    interleaved_bytes_expected_ =
        static_cast<int>(instructions_and_sizes_length);
    UpdateInterleavedSectionPointers(header_parser->UnparsedData(),
                                     header_parser->End());
  } else {
    // If interleaved format is not used, then the whole window contents
    // must be available before decoding can begin.  If only part of
    // the current window is available, then report end of data
    // and re-parse the whole header when DecodeChunk() is called again.
    if (header_parser->UnparsedSize() < (add_and_run_data_length +
                                         instructions_and_sizes_length +
                                         addresses_length)) {
      return RESULT_END_OF_DATA;
    }
    data_for_add_and_run_.Init(header_parser->UnparsedData(),
                               add_and_run_data_length);
    instructions_and_sizes_.Init(data_for_add_and_run_.End(),
                                 instructions_and_sizes_length);
    addresses_for_copy_.Init(instructions_and_sizes_.End(), addresses_length);
    if (addresses_for_copy_.End() != header_parser->EndOfDeltaWindow()) {
      VCD_ERROR << "The end of the instructions section "
                   "does not match the end of the delta window" << VCD_ENDL;
      return RESULT_ERROR;
    }
  }
  reader_.Init(instructions_and_sizes_.UnparsedDataAddr(),
               instructions_and_sizes_.End());
  return RESULT_SUCCESS;
}

// Here are the elements of the delta window header to be parsed,
// from section 4 of the RFC:
//
//     Window1
//         Win_Indicator                            - byte
//         [Source segment size]                    - integer
//         [Source segment position]                - integer
//         The delta encoding of the target window
//             Length of the delta encoding         - integer
//             The delta encoding
//                 Size of the target window        - integer
//                 Delta_Indicator                  - byte
//                 Length of data for ADDs and RUNs - integer
//                 Length of instructions and sizes - integer
//                 Length of addresses for COPYs    - integer
//                 Data section for ADDs and RUNs   - array of bytes
//                 Instructions and sizes section   - array of bytes
//                 Addresses section for COPYs      - array of bytes
//
VCDiffResult VCDiffDeltaFileWindow::ReadHeader(
    ParseableChunk* parseable_chunk) {
  std::string* decoded_target = parent_->decoded_target();
  VCDiffHeaderParser header_parser(parseable_chunk->UnparsedData(),
                                   parseable_chunk->End());
  size_t source_segment_position = 0;
  unsigned char win_indicator = 0;
  if (!header_parser.ParseWinIndicatorAndSourceSegment(
          parent_->dictionary_size(),
          decoded_target->size(),
          parent_->allow_vcd_target(),
          &win_indicator,
          &source_segment_length_,
          &source_segment_position)) {
    return header_parser.GetResult();
  }
  has_checksum_ = parent_->AllowChecksum() && (win_indicator & VCD_CHECKSUM);
  if (!header_parser.ParseWindowLengths(&target_window_length_)) {
    return header_parser.GetResult();
  }
  if (parent_->TargetWindowWouldExceedSizeLimits(target_window_length_)) {
    // An error has been logged by TargetWindowWouldExceedSizeLimits().
    return RESULT_ERROR;
  }
  header_parser.ParseDeltaIndicator();
  VCDiffResult setup_return_code = SetUpWindowSections(&header_parser);
  if (RESULT_SUCCESS != setup_return_code) {
    return setup_return_code;
  }
  // Reserve enough space in the output string for the current target window.
  const size_t wanted_capacity =
      target_window_start_pos_ + target_window_length_;
  if (decoded_target->capacity() < wanted_capacity) {
    decoded_target->reserve(wanted_capacity);
  }
  // Get a pointer to the start of the source segment.
  if (win_indicator & VCD_SOURCE) {
    source_segment_ptr_ = parent_->dictionary_ptr() + source_segment_position;
  } else if (win_indicator & VCD_TARGET) {
    // This assignment must happen after the reserve().
    // decoded_target should not be resized again while processing this window,
    // so source_segment_ptr_ should remain valid.
    source_segment_ptr_ = decoded_target->data() + source_segment_position;
  }
  // The whole window header was found and parsed successfully.
  found_header_ = true;
  parseable_chunk->Advance(header_parser.ParsedSize());
  parent_->AddToTotalTargetWindowSize(target_window_length_);
  return RESULT_SUCCESS;
}

void VCDiffDeltaFileWindow::UpdateInstructionPointer(
    ParseableChunk* parseable_chunk) {
  if (IsInterleaved()) {
    size_t bytes_parsed = instructions_and_sizes_.ParsedSize();
    // Reduce expected instruction segment length by bytes parsed
    interleaved_bytes_expected_ -= static_cast<int>(bytes_parsed);
    parseable_chunk->Advance(bytes_parsed);
  }
}

inline size_t VCDiffDeltaFileWindow::TargetBytesDecoded() {
  return parent_->decoded_target()->size() - target_window_start_pos_;
}

size_t VCDiffDeltaFileWindow::TargetBytesRemaining() {
  if (target_window_length_ == 0) {
    // There is no window being decoded at present
    return 0;
  } else {
    return target_window_length_ - TargetBytesDecoded();
  }
}

inline void VCDiffDeltaFileWindow::CopyBytes(const char* data, size_t size) {
  parent_->decoded_target()->append(data, size);
}

inline void VCDiffDeltaFileWindow::RunByte(unsigned char byte, size_t size) {
  parent_->decoded_target()->append(size, byte);
}

VCDiffResult VCDiffDeltaFileWindow::DecodeAdd(size_t size) {
  if (size > data_for_add_and_run_.UnparsedSize()) {
    return RESULT_END_OF_DATA;
  }
  // Write the next "size" data bytes
  CopyBytes(data_for_add_and_run_.UnparsedData(), size);
  data_for_add_and_run_.Advance(size);
  return RESULT_SUCCESS;
}

VCDiffResult VCDiffDeltaFileWindow::DecodeRun(size_t size) {
  if (data_for_add_and_run_.Empty()) {
    return RESULT_END_OF_DATA;
  }
  // Write "size" copies of the next data byte
  RunByte(*data_for_add_and_run_.UnparsedData(), size);
  data_for_add_and_run_.Advance(1);
  return RESULT_SUCCESS;
}

VCDiffResult VCDiffDeltaFileWindow::DecodeCopy(size_t size,
                                               unsigned char mode) {
  // Keep track of the number of target bytes decoded as a local variable
  // to avoid recalculating it each time it is needed.
  size_t target_bytes_decoded = TargetBytesDecoded();
  const VCDAddress here_address =
      static_cast<VCDAddress>(source_segment_length_ + target_bytes_decoded);
  const VCDAddress decoded_address = parent_->addr_cache()->DecodeAddress(
      here_address,
      mode,
      addresses_for_copy_.UnparsedDataAddr(),
      addresses_for_copy_.End());
  switch (decoded_address) {
    case RESULT_ERROR:
      VCD_ERROR << "Unable to decode address for COPY" << VCD_ENDL;
      return RESULT_ERROR;
    case RESULT_END_OF_DATA:
      return RESULT_END_OF_DATA;
    default:
      if ((decoded_address < 0) || (decoded_address > here_address)) {
        VCD_DFATAL << "Internal error: unexpected address " << decoded_address
                   << " returned from DecodeAddress, with here_address = "
                   << here_address << VCD_ENDL;
        return RESULT_ERROR;
      }
      break;
  }
  size_t address = static_cast<size_t>(decoded_address);
  if ((address + size) <= source_segment_length_) {
    // Copy all data from source segment
    CopyBytes(&source_segment_ptr_[address], size);
    return RESULT_SUCCESS;
  }
  // Copy some data from target window...
  if (address < source_segment_length_) {
    // ... plus some data from source segment
    const size_t partial_copy_size = source_segment_length_ - address;
    CopyBytes(&source_segment_ptr_[address], partial_copy_size);
    target_bytes_decoded += partial_copy_size;
    address += partial_copy_size;
    size -= partial_copy_size;
  }
  address -= source_segment_length_;
  // address is now based at start of target window
  const char* const target_segment_ptr = parent_->decoded_target()->data() +
                                         target_window_start_pos_;
  while (size > (target_bytes_decoded - address)) {
    // Recursive copy that extends into the yet-to-be-copied target data
    const size_t partial_copy_size = target_bytes_decoded - address;
    CopyBytes(&target_segment_ptr[address], partial_copy_size);
    target_bytes_decoded += partial_copy_size;
    address += partial_copy_size;
    size -= partial_copy_size;
  }
  CopyBytes(&target_segment_ptr[address], size);
  return RESULT_SUCCESS;
}

int VCDiffDeltaFileWindow::DecodeBody(ParseableChunk* parseable_chunk) {
  if (IsInterleaved() && (instructions_and_sizes_.UnparsedData()
                              != parseable_chunk->UnparsedData())) {
    VCD_DFATAL << "Internal error: interleaved format is used, but the"
                  " input pointer does not point to the instructions section"
               << VCD_ENDL;
    return RESULT_ERROR;
  }
  while (TargetBytesDecoded() < target_window_length_) {
    int32_t decoded_size = VCD_INSTRUCTION_ERROR;
    unsigned char mode = 0;
    VCDiffInstructionType instruction =
        reader_.GetNextInstruction(&decoded_size, &mode);
    switch (instruction) {
      case VCD_INSTRUCTION_END_OF_DATA:
        UpdateInstructionPointer(parseable_chunk);
        return RESULT_END_OF_DATA;
      case VCD_INSTRUCTION_ERROR:
        return RESULT_ERROR;
      default:
        break;
    }
    const size_t size = static_cast<size_t>(decoded_size);
    // The value of "size" itself could be enormous (say, INT32_MAX)
    // so check it individually against the limit to protect against
    // overflow when adding it to something else.
    if ((size > target_window_length_) ||
        ((size + TargetBytesDecoded()) > target_window_length_)) {
      VCD_ERROR << VCDiffInstructionName(instruction)
                << " with size " << size
                << " plus existing " << TargetBytesDecoded()
                << " bytes of target data exceeds length of target"
                   " window (" << target_window_length_ << " bytes)"
                << VCD_ENDL;
      return RESULT_ERROR;
    }
    VCDiffResult result = RESULT_SUCCESS;
    switch (instruction) {
      case VCD_ADD:
        result = DecodeAdd(size);
        break;
      case VCD_RUN:
        result = DecodeRun(size);
        break;
      case VCD_COPY:
        result = DecodeCopy(size, mode);
        break;
      default:
        VCD_DFATAL << "Unexpected instruction type " << instruction
                   << "in opcode stream" << VCD_ENDL;
        return RESULT_ERROR;
    }
    switch (result) {
      case RESULT_END_OF_DATA:
        reader_.UnGetInstruction();
        UpdateInstructionPointer(parseable_chunk);
        return RESULT_END_OF_DATA;
      case RESULT_ERROR:
        return RESULT_ERROR;
      case RESULT_SUCCESS:
        break;
    }
  }
  if (TargetBytesDecoded() != target_window_length_) {
    VCD_ERROR << "Decoded target window size (" << TargetBytesDecoded()
              << " bytes) does not match expected size ("
              << target_window_length_ << " bytes)" << VCD_ENDL;
    return RESULT_ERROR;
  }
  const char* const target_window_start =
      parent_->decoded_target()->data() + target_window_start_pos_;
  if (has_checksum_ &&
      (ComputeAdler32(target_window_start, target_window_length_)
           != expected_checksum_)) {
    VCD_ERROR << "Target data does not match checksum; this could mean "
                 "that the wrong dictionary was used" << VCD_ENDL;
    return RESULT_ERROR;
  }
  if (!instructions_and_sizes_.Empty()) {
    VCD_ERROR << "Excess instructions and sizes left over "
                 "after decoding target window" << VCD_ENDL;
      return RESULT_ERROR;
  }
  if (!IsInterleaved()) {
    // Standard format is being used, with three separate sections for the
    // instructions, data, and addresses.
    if (!data_for_add_and_run_.Empty()) {
      VCD_ERROR << "Excess ADD/RUN data left over "
                   "after decoding target window" << VCD_ENDL;
        return RESULT_ERROR;
    }
    if (!addresses_for_copy_.Empty()) {
      VCD_ERROR << "Excess COPY addresses left over "
                   "after decoding target window" << VCD_ENDL;
        return RESULT_ERROR;
    }
    // Reached the end of the window.  Update the ParseableChunk to point to the
    // end of the addresses section, which is the last section in the window.
    parseable_chunk->SetPosition(addresses_for_copy_.End());
  } else {
    // Interleaved format is being used.
    UpdateInstructionPointer(parseable_chunk);
  }
  return RESULT_SUCCESS;
}

VCDiffResult VCDiffDeltaFileWindow::DecodeWindow(
    ParseableChunk* parseable_chunk) {
  if (!parent_) {
    VCD_DFATAL << "Internal error: VCDiffDeltaFileWindow::DecodeWindow() "
                  "called before VCDiffDeltaFileWindow::Init()" << VCD_ENDL;
    return RESULT_ERROR;
  }
  if (!found_header_) {
    switch (ReadHeader(parseable_chunk)) {
      case RESULT_END_OF_DATA:
        return RESULT_END_OF_DATA;
      case RESULT_ERROR:
        return RESULT_ERROR;
      default:
        // Reset address cache between windows (RFC section 5.1)
        if (!parent_->addr_cache()->Init()) {
          VCD_DFATAL << "Error initializing address cache" << VCD_ENDL;
          return RESULT_ERROR;
        }
    }
  } else {
    // We are resuming a window that was partially decoded before a
    // RESULT_END_OF_DATA was returned.  This can only happen on the first
    // loop iteration, and only if the interleaved format is enabled and used.
    if (!IsInterleaved()) {
      VCD_DFATAL << "Internal error: Resumed decoding of a delta file window"
                    " when interleaved format is not being used" << VCD_ENDL;
      return RESULT_ERROR;
    }
    UpdateInterleavedSectionPointers(parseable_chunk->UnparsedData(),
                                     parseable_chunk->End());
    reader_.UpdatePointers(instructions_and_sizes_.UnparsedDataAddr(),
                           instructions_and_sizes_.End());
  }
  switch (DecodeBody(parseable_chunk)) {
    case RESULT_END_OF_DATA:
      if (MoreDataExpected()) {
        return RESULT_END_OF_DATA;
      } else {
        VCD_ERROR << "End of data reached while decoding VCDIFF delta file"
                  << VCD_ENDL;
        FALLTHROUGH_INTENDED;
      }
    case RESULT_ERROR:
      return RESULT_ERROR;
    default:
      break;  // DecodeBody succeeded
  }
  // Get ready to read a new delta window
  Reset();
  return RESULT_SUCCESS;
}

}
