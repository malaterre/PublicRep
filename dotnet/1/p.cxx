namespace ns {
class c {
 public:
  c():I(42) {}

 private:
  int I;
};
}  // namespace ns

extern "C" {
typedef struct c c;

__attribute__((visibility("default"))) c * ns_create() {
  return reinterpret_cast<c*>(new ns::c);
}

__attribute__((visibility("default"))) void ns_delete(c *c) {
  delete reinterpret_cast<ns::c*>(c);
}

__attribute__((visibility("default"))) const char * ns_get(c *c) {
  return "42";
}

}  // end extern "C"
