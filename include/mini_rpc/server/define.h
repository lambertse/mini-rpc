#pragma once
#include <map>
#include <memory>
#include <string>

namespace mini_rpc::server {
enum ConnectionState {
  REQUEST = 0,
  RESPONSE,
  END,
};

using Buffer = std::string;

struct Connection {
  int fd;
  ConnectionState state;
  Buffer rbuf;
  size_t wbuf_sent = 0;
  Buffer wbuf;
};

using ConnectionSharedPtr = std::shared_ptr<Connection>;
using FDConnectionMap = std::map<int, ConnectionSharedPtr>;
}  // namespace mini_rpc::server
