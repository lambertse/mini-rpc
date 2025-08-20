#pragma once

#include <memory>

#include "mini_rpc/address.h"
#include "mini_rpc/contract_base.h"
#include "mini_rpc/server/server.h"
namespace mini_rpc::client {

class Client final {
 public:
  Client() = delete;
  explicit Client(const Address& address);
  ~Client();

  template <typename RequestType, typename ResponseType>
  bool register_request(ContractBase<RequestType, ResponseType> request) {
    return true;
  }

 private:
  std::shared_ptr<server::Server> _des_server;
};

using ClientSharedPtr = std::shared_ptr<Client>;
using ClientUniquePtr = std::unique_ptr<Client>;
static ClientSharedPtr createClient(const Address& address);

}  // namespace mini_rpc::client
