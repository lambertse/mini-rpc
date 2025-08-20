#pragma once

#include <map>
#include <memory>

#include "mini_rpc/define.h"
namespace mini_rpc::server {

class RequestHandler {
 public:
  RequestHandler() = default;
  virtual ~RequestHandler() = default;

 private:
};

}  // namespace mini_rpc::server
