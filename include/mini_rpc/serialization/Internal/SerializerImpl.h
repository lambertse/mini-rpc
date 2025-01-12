#pragma once
#include <string>
#include <vector>

constexpr int MAX_STRING_LENGTH = 256;
// Serialize
namespace mini_rpc::internal {
template <class OStream>
void serialize(OStream &os, const std::string &v) {
  std::cout << "DEBG " << v.length() <<std::endl;
  if (v.length() > MAX_STRING_LENGTH) throw("String too long");
  os.write(v.c_str(), MAX_STRING_LENGTH);
  std::cout << "Serialize " << v <<std::endl;
}
template <class OStream, typename T>
void serialize(OStream &os, const T &v) {
  uint8_t size = sizeof(T);
  os.write((char *)&(v), size);
}

// Deserialize
template <class IStream>
bool deserialize(IStream &is, std::string &v) noexcept {
  char *buffer = new char[MAX_STRING_LENGTH];
  is.read(buffer, MAX_STRING_LENGTH);
  if (!is.good()) {
    return false;  // Failed to read the content
  }
  std::string str(buffer);
  v = str;
  std::cout << "Deserialize " << v <<std::endl;
  delete[] buffer;
  return true;
}

template <class IStream, typename T>
bool deserialize(IStream &is, T &v) {
  return true;
}

}  // namespace mini_rpc::internal