#include <stdexcept>

#include "mini_rpc/client/client.h"

namespace mini_rpc::client {
using namespace mini_rpc::server;
Client::Client(const Address& address) {
  _des_server = std::make_shared<Server>(address);
  if (!_des_server) {
    throw std::runtime_error("Failed to create server instance");
  }
}

}  // namespace mini_rpc::client
