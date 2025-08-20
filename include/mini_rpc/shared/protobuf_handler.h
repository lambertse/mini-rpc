#pragma once
#include <optional>
#include <string>

#include "mini_rpc/define.h"

namespace mini_rpc::shared {
class ProtobufHandler {
 public:
  template <class RequestType>
  static std::optional<RequestType> deserialize(const Buffer& data) {
    RequestType req;
    if (!req.ParseFromArray(data.data(), data.size())) {
      return std::nullopt;
    }
    return req;
  }

  template <class ResponseType>
  static Buffer serialize(const ResponseType& object) {
    std::string buffer;
    buffer.resize(object.ByteSizeLong());
    if (!object.SerializeToArray(buffer.data(), buffer.size())) {
      return {};
    }
    return buffer;
  }
};
}  // namespace mini_rpc::shared
