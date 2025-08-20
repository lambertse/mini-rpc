#pragma once

#include <functional>
namespace mini_rpc::server {
using ConnectionIOCallback = std::function<void(int fd)>;

class Poll {
 public:
  Poll() = default;
  virtual ~Poll() = default;
  virtual bool init(int fd);
  virtual bool start();
  virtual bool stop();
  virtual void add_connection(int fd);
  virtual void remove_connection(int fd);
  virtual void set_max_event(int max_event);

  void set_connection_io_callback(ConnectionIOCallback cb);

 protected:
  ConnectionIOCallback _conn_io_cb;
  int _poll_fd = -1;
  bool _is_stopped = false;
  int _max_event = 200;
};
}  // namespace mini_rpc::server
