//
//  JSONCodeTableWriter.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-10-14.
//  Based on open-vcdiff (Apache License 2.0, Copyright Google Inc.).
//

#include "open_vcdiff/config.h"
#include <stdio.h>
#include <string.h>
#include <sstream>
#include <string>
#include "open_vcdiff/jsonwriter.h"
#include "open_vcdiff/logging.h"
#include "open_vcdiff/google/output_string.h"

namespace open_vcdiff {

/////////////// Lifecycle ///////////////

JSONCodeTableWriter::JSONCodeTableWriter()
  : output_called_(false), opcode_added_(false) {}
JSONCodeTableWriter::~JSONCodeTableWriter() {}

bool JSONCodeTableWriter::Init(size_t /*dictionary_size*/) {
  output_ = "[";
  opcode_added_ = false;
  return true;
}

/////////////// Logic ///////////////

void JSONCodeTableWriter::Output(OutputStringInterface* out) {
  output_called_ = true;
  out->append(output_.data(), output_.size());
  output_ = "";
}

void JSONCodeTableWriter::FinishEncoding(OutputStringInterface* out) {
  if (output_called_) {
    out->append("]", 1);
  }
}

void JSONCodeTableWriter::JSONEscape(const char* data,
                                     size_t size,
                                     string* out) {
  for (size_t i = 0; i < size; ++i) {
    const unsigned char c = static_cast<unsigned char>(data[i]);
    switch (c) {
      case '"': out->append("\\\"", 2); break;
      case '\\': out->append("\\\\", 2); break;
      case '\b': out->append("\\b", 2); break;
      case '\f': out->append("\\f", 2); break;
      case '\n': out->append("\\n", 2); break;
      case '\r': out->append("\\r", 2); break;
      case '\t': out->append("\\t", 2); break;
      default:
        // encode zero as unicode, also all control codes.
        if (c < 32 || c >= 127) {
          char unicode_code[8] = "";
          snprintf(unicode_code, sizeof(unicode_code), "\\u%04x", c);
          out->append(unicode_code, strlen(unicode_code));
        } else {
          out->push_back(data[i]);
        }
    }
  }
}

void JSONCodeTableWriter::Add(const char* data, size_t size) {
  // Add leading comma if this is not the first opcode.
  if (opcode_added_) {
    output_.push_back(',');
  }
  output_.push_back('\"');
  JSONEscape(data, size, &output_);
  output_.push_back('\"');
  opcode_added_ = true;
}

void JSONCodeTableWriter::Copy(int32_t offset, size_t size) {
  // Add leading comma if this is not the first opcode.
  if (opcode_added_) {
    output_.push_back(',');
  }
  std::ostringstream copy_code;
  copy_code << offset << "," << size;
  output_.append(copy_code.str());
  opcode_added_ = true;
}

void JSONCodeTableWriter::Run(size_t size, unsigned char byte) {
  // Add leading comma if this is not the first opcode.
  if (opcode_added_) {
    output_.push_back(',');
  }
  output_.push_back('\"');
  output_.append(string(size, byte).data(), size);
  output_.push_back('\"');
  opcode_added_ = true;
}

void JSONCodeTableWriter::WriteHeader(OutputStringInterface *,
                                      VCDiffFormatExtensionFlags) {
  // The JSON format does not need a header.
}

bool JSONCodeTableWriter::VerifyDictionary(const char *dictionary,
                                           size_t size) const {
  // Indexes in the JSON encoding are interpreted as character indexes
  // in a unicode string while the delta is constructed using byte
  // indexes.  To avoid an indexing mismatch and corrupt deltas all
  // characters in the dictionary and target must be single-byte
  // characters, ie 7-bit ASCII.
  VCD_ERROR <<  "JSON writer does not allow non-ASCII characters"
      " in dictionary" << VCD_ENDL;
  return IsAscii(dictionary, size);
}

bool JSONCodeTableWriter::VerifyChunk(const char *chunk, size_t size) const {
  // See comment in VerifyDictionary for explanation of ASCII
  // restriction.
  VCD_ERROR <<  "JSON writer does not allow non-ASCII characters"
      " in target" << VCD_ENDL;
  return IsAscii(chunk, size);
}

bool JSONCodeTableWriter::IsAscii(const char *data, size_t len) {
  for (size_t i = 0; i < len; i++) {
    if (static_cast<unsigned char>(data[i]) >= 128) {
      return false;
    }
  }
  return true;
}

}
