#pragma once
#include <iostream>
#include <string>

namespace mini_rpc {
namespace shared {
enum LogLevel {
  DEBUG = 1 << 0,
  INFO = 1 << 1,
};

static int log_level = INFO;

namespace logging {
static void debug(const std::string &str) {
  if (log_level ^ DEBUG) {
    return;
  }
  std::cout << "DEBUG: " << str << std::endl;
}
static void info(const std::string &str) {
  if (log_level ^ INFO) {
    return;
  }
  std::cout << "INFO: " << str << std::endl;
}

}  // namespace logging
}  // namespace shared

#define LOG_DEBUG(str) shared::logging::debug(str)
#define LOG_INFO(str) shared::logging::info(str)
}  // namespace mini_rpc
