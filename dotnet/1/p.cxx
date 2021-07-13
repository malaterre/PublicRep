#include <string>

namespace ns {
class c {
 public:
  c():S("42") {}
  const std::string& get() const { return S; }

 private:
  std::string S;
};
}  // namespace ns

extern "C" {
typedef struct c c;

__attribute__((visibility("default"))) c *
ns_create() {
  return reinterpret_cast<c*>(new ns::c);
}

__attribute__((visibility("default"))) void ns_delete(
    c *c) {
  delete reinterpret_cast<ns::c*>(c);
}

__attribute__((visibility("default"))) const char *
ns_get(c *c) {
  return "";
}

}  // end extern "C"
