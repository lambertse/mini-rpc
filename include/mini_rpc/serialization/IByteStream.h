#pragma once

#include <cstring>

#include "Buffer.h"

namespace mini_rpc {
namespace details {
template <class BufferType>
class BasicIByteStream {
  enum State { Good = 1 << 0, Failed = 1 << 1, Eof = 1 << 2 };

 public:
  using SizeType = size_t;
  BasicIByteStream(BufferType buff, SizeType currentPos = 0, State state = Good)
      : buffer_(std::move(buff)), currentPos_{currentPos}, state_{state} {}

  BasicIByteStream(BasicIByteStream &&other) noexcept { other.moveTo(*this); }
  BasicIByteStream &operator=(BasicIByteStream &&other) noexcept {
    if (&other != this) {
      other.moveTo(*this);
    }
    return *this;
  }

  void read(char *buf, SizeType size) noexcept {
    if (!good()) {
      (state_ &= ~Good) |= Failed;
      return;
    }

    if (currentPos_ + size > buffer_.size()) {
      (state_ &= ~Good) |= Failed;
      return;
    }
    std::memcpy(buf, buffer_.data() + currentPos_, size);
    currentPos_ += size;
    if (currentPos_ == buffer_.size()) {
      state_ |= Eof;
    }
  }

  bool eof() const noexcept { return state_ & Eof; }
  bool good() const noexcept { return state_ & Good; }
  bool fail() const noexcept { return state_ & Failed; }
  void clear(State state) { state_ &= ~state; }

  void reset() noexcept {
    currentPos_ = 0;
    state_ = Good;
    buffer_.clear();
  }

  State state() const noexcept { return state_; }
  SizeType currentPos() const noexcept { return currentPos_; }

 protected:
  void moveTo(BasicIByteStream &other) noexcept {
    other.buffer_ = std::move(buffer_);
    other.currentPos_ = currentPos_;
    other.state_ = state_;
    state_ = Good;
    currentPos_ = 0;
  }
  BufferType buffer_;
  SizeType currentPos_ = 0;
  State state_ = Good;
};
}  // namespace details

class IByteStream : public details::BasicIByteStream<Buffer> {
 public:
  using BasicIByteStream<Buffer>::BasicIByteStream;
  IByteStream(const IByteStream &other)
      : BasicIByteStream<Buffer>(other.buffer_, other.currentPos_,
                                 other.state_) {}
  Buffer &bytes() noexcept { return buffer_; }
  const Buffer &bytes() const noexcept { return buffer_; }
  decltype(auto) buffer() const { return bytes(); }

 private:
};

}  // namespace mini_rpc
