#pragma once
#include <map>
#include <memory>
#include <string>
constexpr int k_max_msg = 1024;

enum ConnectionState {
  REQUEST = 0,
  RESPONSE,
  END,
};

using Buffer = std::string;

struct Connection {
  int fd;
  ConnectionState state;
  // Buffer for reading
  Buffer rbuf;
  // Buffer for writing
  size_t wbuf_sent = 0;
  Buffer wbuf;
};
using ConnectionSharedPtr = std::shared_ptr<Connection>;
using FDConnectionMap = std::map<int, ConnectionSharedPtr>;
