#pragma once
#include "Buffer.h"
#include <cstring>
#include <iostream>
namespace mini_rpc {

class OByteStream {
public:

  using State = uint8_t;
  static constexpr State Good = 1;
  static constexpr State Failed = 2;
  static constexpr State Eof = 4;
 public:
  using SizeType = uint16_t;
  void write(const char *buf, SizeType size) {
    if (prepareNextWrite(size)) {
      std::memcpy(data_.data() + currentPos_, buf, size);
      currentPos_ += size;
    }
  }

  bool prepareNextWrite(SizeType size) {
    if (good()) {
      if (currentPos_ + size > data_.size()) {
        data_.resize(currentPos_ + size);
      }
      return true;
    }
    return false;
  }

  void reset() {
    currentPos_ = 0;
    state_ = Good;
    data_.clear();
  }

  bool good() const { return state_ & Good; }
  bool fail() const { return state_ & Failed; }
  Buffer &bytes() { return data_; }
  const Buffer &bytes() const { return data_; }

 private:
  Buffer data_ = "";
  SizeType currentPos_ = 0;
  State state_ = Good;
};

}  // namespace mini_rpc
