#include <sys/event.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

#include "mini_rpc/server/poll.h"
#include "mini_rpc/shared/logging.h"
#include "mini_rpc/shared/utils.h"

namespace mini_rpc::server {
bool Poll::init(int fd) {
  _poll_fd = kqueue();
  if (_poll_fd == 0) {
    LOG_INFO("kqueue failed: " + std::string(strerror(errno)));
    return false;
  }

  struct kevent ev;
  EV_SET(&ev, fd, EVFILT_READ, EV_ADD | EV_ENABLE, 0, 0, NULL);
  if (kevent(_poll_fd, &ev, 1, NULL, 0, NULL) == -1) {
    LOG_INFO("kevent: listen_sock failed: " + std::string(strerror(errno)));
    return false;
  }
  return true;
}

bool Poll::start() {
  struct kevent events[_max_event];
  while (!_is_stopped) {
    auto nfds = kevent(_poll_fd, NULL, 0, events, _max_event, NULL);
    if (nfds == 0) {
      LOG_INFO("kevent failed: " + std::to_string(errno));
      break;
    }

    for (int n = 0; n < nfds; ++n) {
      int fd = static_cast<int>(events[n].ident);

      if (_conn_io_cb) {
        _conn_io_cb(fd);
      }
    }
  }
  return true;
}

bool Poll::stop() {
  if (_poll_fd >= 0) {
    close(_poll_fd);
    _poll_fd = -1;
  }
  _is_stopped = true;
  return true;
}

void Poll::add_connection(int fd) {
  struct kevent ev;
  EV_SET(&ev, fd, EVFILT_READ, EV_ADD | EV_ENABLE, 0, 0, NULL);
  if (kevent(_poll_fd, &ev, 1, NULL, 0, NULL) == -1) {
    LOG_INFO("kevent: conn_sock failed: " + std::to_string(errno));
    exit(EXIT_FAILURE);
  }
}

void Poll::set_connection_io_callback(ConnectionIOCallback cb) {
  _conn_io_cb = std::move(cb);
}

void Poll::remove_connection(int fd) {
  // Remove a connection from the poll
}

void Poll::set_max_event(int max_event) { _max_event = std::move(max_event); }
}  // namespace mini_rpc::server
