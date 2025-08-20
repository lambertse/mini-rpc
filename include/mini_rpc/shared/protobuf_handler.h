#pragma once
#include <string>

#include "mini_rpc/proto/request.pb.h"

namespace mini_rpc::shared {
class ProtobufHandler {
 public:
  static proto::request::Request deserialize(const std::string& data);
  static std::string serialize(const proto::request::Request& object);
};
}  // namespace mini_rpc::shared
