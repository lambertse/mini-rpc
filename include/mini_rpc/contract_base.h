#pragma once
#include <string>

#include "mini_rpc/define.h"
#include "mini_rpc/shared/protobuf_handler.h"

namespace mini_rpc {

template <typename RequestType, typename ResponseType>
class ContractBase {
 public:
  ContractBase(const RequestID& request_id) : _request_id(request_id) {}

  static RequestType deserializeRequest(const Buffer& data) {
    return shared::ProtobufHandler::deserialize<RequestType>(data);
  }
  static ResponseType deserializeResponse(const Buffer& data) {
    return shared::ProtobufHandler::deserialize<ResponseType>(data);
  }
  static Buffer serializeResponse(const ResponseType& response) {
    return shared::ProtobufHandler::serialize(response);
  }
  static Buffer serializeRequest(const RequestType& request) {
    return shared::ProtobufHandler::serialize(request);
  }
  virtual ~ContractBase() = default;

 private:
  std::string _request_id;
};

}  // namespace mini_rpc
