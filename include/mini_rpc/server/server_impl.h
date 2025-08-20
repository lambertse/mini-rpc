#pragma once

#include <netinet/ip.h>

#include <memory>
#include <thread>

#include "config.h"
#include "connection_manager.h"
#include "mini_rpc/define.h"
namespace mini_rpc::server {
class ServerImpl {
 public:
  ServerImpl(ServerConfig config = ServerConfig::default_config());
  ~ServerImpl();

  bool init();
  bool start();
  bool start_sync();
  bool stop();
  bool deinit();

 private:
  void add_conection(int fd);
  void accept_new_connection();
  void handle_connection_io(int fd);
  bool setup_socket();

 private:
  int _server_fd;
  ServerConfig _config;
  struct sockaddr_in _addr;
  FDConnectionMap _fd_2_conn;
  std::unique_ptr<class Poll> _poll;
  std::unique_ptr<ConnectionManager> _connection_manager;

  bool _is_running = false;
  std::thread _running_thread;
};
}  // namespace mini_rpc::server
