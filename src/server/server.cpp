#include <stdexcept>
#include <thread>

#include "mini_rpc/server/server.h"
#include "mini_rpc/server/server_impl.h"

namespace mini_rpc::server {

Server::Server(Address address) : _address(std::move(address)) {
  ServerConfig config = ServerConfig::default_config();
  config.port = address.getPort();

  _impl = std::make_shared<ServerImpl>(config);
}
Server::~Server() {
  if (_impl) {
    _impl->stop();
    _impl->deinit();
  }
}
bool Server::startServing() {
  if (!_impl) {
    return false;
  }
  if (!_impl->init()) {
    throw std::runtime_error("Failed to initialize server");
  }
  return _impl->start();
}

bool Server::stopServing() { return true; }

ServerSharedPtr createServer(const Address& address) {
  return std::make_shared<Server>(address);
}
}  // namespace mini_rpc::server
