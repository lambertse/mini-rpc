#include "mini_rpc/shared/utils.h"

namespace mini_rpc::shared {
void Utils::set_fb_nonblocking(int &fd) {
  errno = 0;
  int flags = fcntl(fd, F_GETFL, 0);
  if (errno) {
    std::cerr << "fcntl get error\n";
    return;
  }

  fcntl(fd, F_SETFL, flags | O_NONBLOCK);
  if (errno) {
    std::cerr << "fcntl set error\n";
    return;
  }
}
}  // namespace mini_rpc::shared
