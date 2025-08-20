#pragma once

#include <functional>
#include <memory>

#include "mini_rpc/define.h"
#include "mini_rpc/server/request_handler.h"

namespace mini_rpc::server {
class ConnectionManager {
 public:
  explicit ConnectionManager();
  virtual ~ConnectionManager() = default;

  void remove_connection(int fd);
  void handle_connection_io(ConnectionSharedPtr conn);

 private:
  bool try_one_request(ConnectionSharedPtr conn);
  void state_request(ConnectionSharedPtr conn);
  void state_response(ConnectionSharedPtr conn);

  std::unique_ptr<RequestHandler> _req_handler;
};
}  // namespace mini_rpc::server
