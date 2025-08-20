#pragma once
#include <fcntl.h>

#include <cerrno>
#include <iostream>

namespace mini_rpc::shared {
class Utils {
 public:
  static void set_fb_nonblocking(int &fd);
};
}  // namespace mini_rpc::shared
