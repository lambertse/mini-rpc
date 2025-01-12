#pragma once
#define mc_mini_rpc_sb_object(name) struct name {
#define mc_mini_rpc_sb_object_ex(name, base) struct name : public base {
#define mc_mini_rpc_sb_endobject(name) \
 public:                               \
  }                                    \
  ;

#define mc_mini_rpc_sb_members(...) \
 public:                            \
  __VA_ARGS__

#define mc_mini_rpc_sb_define_constructors(name) \
 public:                                         \
  /*  template <class... Args>                   \
    name(Args... args) {                         \
      set_all(std::forward<Args>(args)...);      \
    }  */                                        \
  name() noexcept {}                             \
  name(const name &other) = default;             \
  name(name &&other) = default;                  \
  name &operator=(name &&other) = default;       \
  name &operator=(const name &other) = default;
