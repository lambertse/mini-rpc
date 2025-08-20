#pragma once
#include "gen_rand_num.pb.h"
#include "mini_rpc/contract_base.h"

namespace mini_rpc {
class GenerateRand
    : public ContractBase<generate_rand::Request, generate_rand::Response> {
 public:
  GenerateRand() : ContractBase("generate_rand") {}
};
}  // namespace mini_rpc
