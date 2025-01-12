#pragma once
#include "Internal/SerializerImpl.h"

namespace mini_rpc {
template <class IStream>
class Deserializer {
 public:
  Deserializer(IStream &is) : is_(is) {}

  template <typename T>
  Deserializer &operator>>(T &value) {
    if (!internal::deserialize(is_, value)) {
      throw std::runtime_error{"Could not deserialize"};
    }
    return *this;
  }

 private:
  IStream& is_;
};

template <class OStream>
class Serializer {
 public:
  Serializer(OStream &os) : os_(os) {}
  template <typename T>
  Serializer &operator<<(T &value) {
    internal::serialize(os_, value);
    return *this;
  }

 private:
  OStream& os_;
};
}  // namespace mini_rpc