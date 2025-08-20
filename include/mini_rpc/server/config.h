#pragma once

#include <string>

namespace mini_rpc::server {
struct ServerConfig {
  int port;
  int max_connections;
  bool enable_logging;
  std::string log_level;

  static ServerConfig from_file(const std::string& config_path) {}
  static ServerConfig default_config() {
    static ServerConfig config;
    config.port = 8100;
    config.max_connections = 200;
    config.enable_logging = true;
    config.log_level = "INFO";
    return config;
  }
};
}  // namespace mini_rpc::server
