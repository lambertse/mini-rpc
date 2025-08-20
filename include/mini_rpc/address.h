#pragma once

#include <string>

namespace mini_rpc {
class Address {
 public:
  Address(const std::string& name, int port) : name(name), port(port) {}
  const std::string& getName() const { return name; }
  int getPort() const { return port; }

 private:
  std::string name;
  int port;
};
}  // namespace mini_rpc
