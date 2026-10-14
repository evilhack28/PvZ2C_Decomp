//
//  VCDiffStreamingDecoderImpl.cpp
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

VCDiffStreamingDecoderImpl::VCDiffStreamingDecoderImpl()
    : maximum_target_file_size_(kDefaultMaximumTargetFileSize),
      maximum_target_window_size_(kDefaultMaximumTargetFileSize),
      allow_vcd_target_(true) {
  delta_window_.Init(this);
  Reset();
}

// Reset() will delete the component objects without reallocating them.
VCDiffStreamingDecoderImpl::~VCDiffStreamingDecoderImpl() { Reset(); }

void VCDiffStreamingDecoderImpl::Reset() {
  start_decoding_was_called_ = false;
  dictionary_ptr_ = NULL;
  dictionary_size_ = 0;
  vcdiff_version_code_ = '\0';
  planned_target_file_size_ = kUnlimitedBytes;
  total_of_target_window_sizes_ = 0;
  addr_cache_.reset();
  custom_code_table_.reset();
  custom_code_table_decoder_.reset();
  delta_window_.Reset();
  decoded_target_output_position_ = 0;
}

/////////////// Logic ///////////////

// *** Methods for VCDiffStreamingDecoderImpl

const size_t VCDiffStreamingDecoderImpl::kDefaultMaximumTargetFileSize;

const size_t VCDiffStreamingDecoderImpl::kUnlimitedBytes;

void VCDiffStreamingDecoderImpl::StartDecoding(const char* dictionary_ptr,
                                               size_t dictionary_size) {
  if (start_decoding_was_called_) {
    VCD_DFATAL << "StartDecoding() called twice without FinishDecoding()"
               << VCD_ENDL;
    return;
  }
  unparsed_bytes_.clear();
  decoded_target_.clear();  // delta_window_.Reset() depends on this
  Reset();
  dictionary_ptr_ = dictionary_ptr;
  dictionary_size_ = dictionary_size;
  start_decoding_was_called_ = true;
}

// Reads the VCDiff delta file header section as described in RFC section 4.1:
//
//     Header1                                  - byte = 0xD6 (ASCII 'V' | 0x80)
//     Header2                                  - byte = 0xC3 (ASCII 'C' | 0x80)
//     Header3                                  - byte = 0xC4 (ASCII 'D' | 0x80)
//     Header4                                  - byte
//     Hdr_Indicator                            - byte
//     [Secondary compressor ID]                - byte
//     [Length of code table data]              - integer
//     [Code table data]
//
// Initializes the code table and address cache objects.  Returns RESULT_ERROR
// if an error occurred, and RESULT_END_OF_DATA if the end of available data was
// reached before the entire header could be read.  (The latter may be an error
// condition if there is no more data available.)  Otherwise, returns
// RESULT_SUCCESS, and removes the header bytes from the data string.
//
// It's relatively inefficient to expect this function to parse any number of
// input bytes available, down to 1 byte, but it is necessary in case the input
// is not a properly formatted VCDIFF delta file.  If the entire input consists
// of two bytes "12", then we should recognize that it does not match the
// initial VCDIFF magic number "VCD" and report an error, rather than waiting
// indefinitely for more input that will never arrive.
//
VCDiffResult VCDiffStreamingDecoderImpl::ReadDeltaFileHeader(
    ParseableChunk* data) {
  if (FoundFileHeader()) {
    return RESULT_SUCCESS;
  }
  size_t data_size = data->UnparsedSize();
  const DeltaFileHeader* header =
      reinterpret_cast<const DeltaFileHeader*>(data->UnparsedData());
  bool wrong_magic_number = false;
  switch (data_size) {
    // Verify only the bytes that are available.
    default:
      // Found header contents up to and including VCDIFF version
      vcdiff_version_code_ = header->header4;
      if ((vcdiff_version_code_ != 0x00) &&  // Draft standard VCDIFF (RFC 3284)
          (vcdiff_version_code_ != 'S')) {   // Enhancements for SDCH protocol
        VCD_ERROR << "Unrecognized VCDIFF format version" << VCD_ENDL;
        return RESULT_ERROR;
      }
      FALLTHROUGH_INTENDED;
    case 3:
      if (header->header3 != 0xC4) {  // magic value 'D' | 0x80
        wrong_magic_number = true;
      }
      FALLTHROUGH_INTENDED;
    case 2:
      if (header->header2 != 0xC3) {  // magic value 'C' | 0x80
        wrong_magic_number = true;
      }
      FALLTHROUGH_INTENDED;
    case 1:
      if (header->header1 != 0xD6) {  // magic value 'V' | 0x80
        wrong_magic_number = true;
      }
      FALLTHROUGH_INTENDED;
    case 0:
      if (wrong_magic_number) {
        VCD_ERROR << "Did not find VCDIFF header bytes; "
                      "input is not a VCDIFF delta file" << VCD_ENDL;
        return RESULT_ERROR;
      }
      if (data_size < sizeof(DeltaFileHeader)) return RESULT_END_OF_DATA;
      break;
  }
  // Secondary compressor not supported.
  if (header->hdr_indicator & VCD_DECOMPRESS) {
    VCD_ERROR << "Secondary compression is not supported" << VCD_ENDL;
    return RESULT_ERROR;
  }
  if (header->hdr_indicator & VCD_CODETABLE) {
    int bytes_parsed = InitCustomCodeTable(
        data->UnparsedData() + sizeof(DeltaFileHeader),
        data->End());
    switch (bytes_parsed) {
      case RESULT_ERROR:
        return RESULT_ERROR;
      case RESULT_END_OF_DATA:
        return RESULT_END_OF_DATA;
      default:
        data->Advance(sizeof(DeltaFileHeader) + bytes_parsed);
    }
  } else {
    addr_cache_.reset(new VCDiffAddressCache);
    // addr_cache_->Init() will be called
    // from VCDiffStreamingDecoderImpl::DecodeChunk()
    data->Advance(sizeof(DeltaFileHeader));
  }
  return RESULT_SUCCESS;
}

int VCDiffStreamingDecoderImpl::InitCustomCodeTable(const char* data_start,
                                                    const char* data_end) {
  // A custom code table is being specified.  Parse the variable-length
  // cache sizes and begin parsing the encoded custom code table.
  int32_t near_cache_size = 0, same_cache_size = 0;
  VCDiffHeaderParser header_parser(data_start, data_end);
  if (!header_parser.ParseInt32("size of near cache", &near_cache_size)) {
    return header_parser.GetResult();
  }
  if (!header_parser.ParseInt32("size of same cache", &same_cache_size)) {
    return header_parser.GetResult();
  }
  custom_code_table_.reset(new struct VCDiffCodeTableData);
  memset(custom_code_table_.get(), 0, sizeof(struct VCDiffCodeTableData));
  custom_code_table_string_.clear();
  addr_cache_.reset(new VCDiffAddressCache(near_cache_size, same_cache_size));
  // addr_cache_->Init() will be called
  // from VCDiffStreamingDecoderImpl::DecodeChunk()

  // If we reach this point (the start of the custom code table)
  // without encountering a RESULT_END_OF_DATA condition, then we won't call
  // ReadDeltaFileHeader() again for this delta file.
  //
  // Instantiate a recursive decoder to interpret the custom code table
  // as a VCDIFF encoding of the default code table.
  custom_code_table_decoder_.reset(new VCDiffStreamingDecoderImpl);
  custom_code_table_decoder_->StartDecoding(
      reinterpret_cast<const char*>(
          &VCDiffCodeTableData::kDefaultCodeTableData),
      sizeof(VCDiffCodeTableData::kDefaultCodeTableData));
  custom_code_table_decoder_->SetPlannedTargetFileSize(
      sizeof(*custom_code_table_));
  return static_cast<int>(header_parser.ParsedSize());
}

VCDiffResult VCDiffStreamingDecoderImpl::ReadCustomCodeTable(
    ParseableChunk* data) {
  if (!custom_code_table_decoder_.get()) {
    return RESULT_SUCCESS;
  }
  if (!custom_code_table_.get()) {
    VCD_DFATAL << "Internal error:  custom_code_table_decoder_ is set,"
                  " but custom_code_table_ is NULL" << VCD_ENDL;
    return RESULT_ERROR;
  }
  OutputString<string> output_string(&custom_code_table_string_);
  if (!custom_code_table_decoder_->DecodeChunk(data->UnparsedData(),
                                               data->UnparsedSize(),
                                               &output_string)) {
    return RESULT_ERROR;
  }
  if (custom_code_table_string_.length() < sizeof(*custom_code_table_)) {
    // Skip over the consumed data.
    data->Finish();
    return RESULT_END_OF_DATA;
  }
  if (!custom_code_table_decoder_->FinishDecoding()) {
    return RESULT_ERROR;
  }
  if (custom_code_table_string_.length() != sizeof(*custom_code_table_)) {
    VCD_DFATAL << "Decoded custom code table size ("
               << custom_code_table_string_.length()
               << ") does not match size of a code table ("
               << sizeof(*custom_code_table_) << ")" << VCD_ENDL;
    return RESULT_ERROR;
  }
  memcpy(custom_code_table_.get(),
         custom_code_table_string_.data(),
         sizeof(*custom_code_table_));
  custom_code_table_string_.clear();
  // Skip over the consumed data.
  data->FinishExcept(custom_code_table_decoder_->GetUnconsumedDataSize());
  custom_code_table_decoder_.reset();
  delta_window_.UseCodeTable(*custom_code_table_, addr_cache_->LastMode());
  return RESULT_SUCCESS;
}

void VCDiffStreamingDecoderImpl::FlushDecodedTarget(
    OutputStringInterface* output_string) {
  output_string->append(
      decoded_target_.data() + decoded_target_output_position_,
      decoded_target_.size() - decoded_target_output_position_);
  decoded_target_.clear();
  delta_window_.set_target_window_start_pos(0);
  decoded_target_output_position_ = 0;
}

void VCDiffStreamingDecoderImpl::AppendNewOutputText(
    OutputStringInterface* output_string) {
  const size_t bytes_decoded_this_chunk =
      decoded_target_.size() - decoded_target_output_position_;
  if (bytes_decoded_this_chunk > 0) {
    size_t target_bytes_remaining = delta_window_.TargetBytesRemaining();
    if (target_bytes_remaining > 0) {
      // The decoder is midway through decoding a target window.  Resize
      // output_string to match the expected length.  The interface guarantees
      // not to resize output_string more than once per target window decoded.
      output_string->ReserveAdditionalBytes(bytes_decoded_this_chunk
                                            + target_bytes_remaining);
    }
    output_string->append(
        decoded_target_.data() + decoded_target_output_position_,
        bytes_decoded_this_chunk);
    decoded_target_output_position_ = decoded_target_.size();
  }
}

bool VCDiffStreamingDecoderImpl::DecodeChunk(
    const char* data,
    size_t len,
    OutputStringInterface* output_string) {
  if (!start_decoding_was_called_) {
    VCD_DFATAL << "DecodeChunk() called without StartDecoding()" << VCD_ENDL;
    Reset();
    return false;
  }
  ParseableChunk parseable_chunk(data, len);
  if (!unparsed_bytes_.empty()) {
    unparsed_bytes_.append(data, len);
    parseable_chunk.SetDataBuffer(unparsed_bytes_.data(),
                                  unparsed_bytes_.size());
  }
  VCDiffResult result = ReadDeltaFileHeader(&parseable_chunk);
  if (RESULT_SUCCESS == result) {
    result = ReadCustomCodeTable(&parseable_chunk);
  }
  if (RESULT_SUCCESS == result) {
    while (!parseable_chunk.Empty()) {
      result = delta_window_.DecodeWindow(&parseable_chunk);
      if (RESULT_SUCCESS != result) {
        break;
      }
      if (ReachedPlannedTargetFileSize()) {
        // Found exactly the length we expected.  Stop decoding.
        break;
      }
      if (!allow_vcd_target()) {
        // VCD_TARGET will never be used to reference target data before the
        // start of the current window, so flush and clear the contents of
        // decoded_target_.
        FlushDecodedTarget(output_string);
      }
    }
  }
  if (RESULT_ERROR == result) {
    Reset();  // Don't allow further DecodeChunk calls
    return false;
  }
  unparsed_bytes_.assign(parseable_chunk.UnparsedData(),
                         parseable_chunk.UnparsedSize());
  AppendNewOutputText(output_string);
  return true;
}

// Finishes decoding after all data has been received.  Returns true
// if decoding of the entire stream was successful.
bool VCDiffStreamingDecoderImpl::FinishDecoding() {
  bool success = true;
  if (!start_decoding_was_called_) {
    VCD_WARNING << "FinishDecoding() called before StartDecoding(),"
                   " or called after DecodeChunk() returned false"
                << VCD_ENDL;
    success = false;
  } else if (!IsDecodingComplete()) {
    VCD_ERROR << "FinishDecoding() called before parsing entire"
                 " delta file window" << VCD_ENDL;
    success = false;
  }
  // Reset the object state for the next decode operation
  Reset();
  return success;
}

bool VCDiffStreamingDecoderImpl::TargetWindowWouldExceedSizeLimits(
    size_t window_size) const {
  if (window_size > maximum_target_window_size_) {
    VCD_ERROR << "Length of target window (" << window_size
              << ") exceeds limit of " << maximum_target_window_size_
              << " bytes" << VCD_ENDL;
    return true;
  }
  if (HasPlannedTargetFileSize()) {
    // The logical expression to check would be:
    //
    //   total_of_target_window_sizes_ + window_size > planned_target_file_size_
    //
    // but the addition might cause an integer overflow if target_bytes_to_add
    // is very large.  So it is better to check target_bytes_to_add against
    // the remaining planned target bytes.
    size_t remaining_planned_target_file_size =
        planned_target_file_size_ - total_of_target_window_sizes_;
    if (window_size > remaining_planned_target_file_size) {
      VCD_ERROR << "Length of target window (" << window_size
                << " bytes) plus previous windows ("
                << total_of_target_window_sizes_
                << " bytes) would exceed planned size of "
                << planned_target_file_size_ << " bytes" << VCD_ENDL;
      return true;
    }
  }
  size_t remaining_maximum_target_bytes =
      maximum_target_file_size_ - total_of_target_window_sizes_;
  if (window_size > remaining_maximum_target_bytes) {
    VCD_ERROR << "Length of target window (" << window_size
              << " bytes) plus previous windows ("
              << total_of_target_window_sizes_
              << " bytes) would exceed maximum target file size of "
              << maximum_target_file_size_ << " bytes" << VCD_ENDL;
    return true;
  }
  return false;
}

}
