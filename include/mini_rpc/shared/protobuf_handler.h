#pragma once
#include <string>

#include "mini_rpc/proto/request.pb.h"

class ProtobufHandler {
 public:
  static request::Request deserialize(const std::string& data);
  static std::string serialize(const request::Request& object);
};
