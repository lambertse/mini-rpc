#include <unistd.h>

#include "mini_rpc/connection_manager.h"
#include "mini_rpc/define.h"
#include "mini_rpc/proto/request.pb.h"
#include "mini_rpc/shared/logging.h"
#include "mini_rpc/shared/protobuf_handler.h"

ConnectionManager::ConnectionManager() {}

void ConnectionManager::remove_connection(int fd) {}

void ConnectionManager::handle_connection_io(ConnectionSharedPtr conn) {
  if (conn->state == ConnectionState::REQUEST) {
    state_request(conn);
  } else if (conn->state == ConnectionState::RESPONSE) {
    state_response(conn);
  }
}

void ConnectionManager::state_request(ConnectionSharedPtr conn) {
  LOG_DEBUG("state_request: " + std::to_string(conn->fd));
  do {
    ssize_t rv = 0;
    do {
      size_t cap = k_max_msg - conn->rbuf.size();
      std::string tmpbuf(cap, '\0');
      rv = read(conn->fd, &tmpbuf[0], cap);
      if (rv > 0) conn->rbuf.append(tmpbuf, 0, rv);
    } while (rv < 0 && errno == EINTR);

    if (rv < 0) {
      if (errno == EAGAIN) {
        // Got EAGAIN, stop it
        break;
      } else {
        LOG_DEBUG("read() error" + std::to_string(errno));
        break;
      }
    }

    if (rv == 0) {
      if (conn->rbuf.size() > 0) {
        LOG_DEBUG("Unexpected EOF");
      } else {
        LOG_DEBUG("EOF");
      }
      conn->state = ConnectionState::END;
      break;
    }
    // Maybe need to cover the size here
    while (try_one_request(conn)) {
    }
  } while (conn->state == ConnectionState::REQUEST);
}

void ConnectionManager::state_response(ConnectionSharedPtr conn) {
  LOG_DEBUG("state_response: " + std::to_string(conn->fd));
  do {
    ssize_t rv = 0;
    do {
      ssize_t cap = conn->wbuf.size() - conn->wbuf_sent;
      rv = write(conn->fd, &conn->wbuf[conn->wbuf_sent], cap);
    } while (rv < 0 && errno == EINTR);

    if (rv < 0) {
      if (errno == EAGAIN) {
        // Got EAGAIN, stop it
        break;
      } else {
        LOG_DEBUG("write() error: " + std::to_string(errno));
        conn->state = ConnectionState::END;
        break;
      }
    }
    conn->wbuf_sent += size_t(rv);
    if (conn->wbuf_sent == conn->wbuf.size()) {
      conn->state = ConnectionState::END;
      conn->wbuf_sent = 0;
      break;
    }
    // Still got some data in wbuf, could try to continue writing
  } while (true);
}

bool ConnectionManager::try_one_request(ConnectionSharedPtr conn) {
  if (conn->rbuf.size() < 4) {
    // Not enough data in the buffer, will retry in the next iterator
    return false;
  }
  u_int32_t len = 0;
  memcpy(&len, &conn->rbuf[0], 4);
  if (conn->rbuf.size() < 4 + len) {
    return false;
  }

  if (len > k_max_msg) {
    LOG_DEBUG("Too long");
    conn->state = ConnectionState::END;
    return false;
  }
  if (conn->rbuf.size() < 4 + len) {
    // Not enough data in the buffer
    return false;
  }
  auto buffer = conn->rbuf.substr(4);
  request::Request req = ProtobufHandler::deserialize(buffer);
  static int count = 0;
  LOG_INFO(std::to_string(count++) + ". Incomming message: " + req.msg());

  request::Response res;
  res.set_msg("Responnse for message: " + req.msg() + " from server");
  char serializedData[k_max_msg];
  size_t resLen = res.ByteSizeLong();
  if (resLen > k_max_msg - 4) {
    LOG_INFO("Response too large");
    conn->state = ConnectionState::END;
    return false;
  }
  if (!res.SerializeToArray(serializedData, resLen)) {
    LOG_INFO("Failed to serialize response");
    conn->state = ConnectionState::END;
    return false;
  }

  conn->wbuf.resize(resLen + 4);
  memcpy(&conn->wbuf[0], &resLen, 4);
  memcpy(&conn->wbuf[4], serializedData, resLen);

  // Remove the processed data from the read buffer
  size_t remaining = conn->rbuf.size() - (4 + len);
  if (remaining > 0) {
    conn->rbuf = conn->rbuf.substr(4 + len);
  } else {
    conn->rbuf.clear();
  }
  //

  state_response(conn);
  return conn->state == ConnectionState::REQUEST;
}
