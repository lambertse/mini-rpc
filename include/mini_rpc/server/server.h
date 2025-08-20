#pragma once

#include <functional>
#include <memory>

#include "mini_rpc/address.h"
#include "mini_rpc/define.h"
namespace mini_rpc::server {

class Server final {
 public:
  Server() = delete;
  explicit Server(Address address);

  template <typename RequestType, typename ResponseType>
  bool register_request_handler(
      const RequestID& request_id,
      std::function<ResponseType(const RequestType&)> handler);

  bool startServing();
  bool stopServing();
  ~Server();

 private:
  Address _address;
  std::shared_ptr<class ServerImpl> _impl;  // Implementation details hidden
};

using ServerSharedPtr = std::shared_ptr<Server>;
using ServerUniquePtr = std::unique_ptr<Server>;

static ServerSharedPtr createServer(const Address& address);
}  // namespace mini_rpc::server
