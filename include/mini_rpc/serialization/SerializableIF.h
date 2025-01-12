#pragma once

#include "IByteStream.h"
#include "OByteStream.h"

namespace mini_rpc {
class SerializableIF {
 public:
  virtual ~SerializableIF() = default;
  virtual bool serialize(OByteStream &) const = 0;
  virtual bool deserialize(IByteStream &) = 0;
};
}  // namespace mini_rpc
