#include "mini_rpc/server/server_impl.h"

using namespace mini_rpc::server;
int main() {
  ServerImpl server;
  if (server.init()) {
    server.start();
  } else {
    return -2;
  }
}
