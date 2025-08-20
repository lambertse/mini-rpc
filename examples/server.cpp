#include <iostream>
#include <string>

#include "../contract/gen_rand_num.h"
int main() {
  mini_rpc::generate_rand::Response response;
  response.set_rand_num(42);  // Example random number
  auto res = mini_rpc::GenerateRand::serializeResponse(response);

  std::cout << "Serialized Response Data: ";
  for (const auto& byte : res) {
    std::cout << static_cast<char>(byte) << " ";
  }
}
