#ifndef DEVICE_H
#define DEVICE_H

/* common object private vtable */
struct object_prv_vtable {
  int (*fp_destroy)(void *const);
};

/* common object interface */
#define object_destroy(t) ((t)->vtable->object.fp_destroy((t)))

/* common device private vtable */
#include <stddef.h>

struct device_prv_vtable {
  int (*fp_read)(void *const, void *, size_t);
  int (*fp_write)(void *const, void const *, size_t);
};

/* common device vtable */
struct device_vtable {
  struct object_prv_vtable const object;
  struct device_prv_vtable const device;
};

/* common device object */
struct device {
  struct device_vtable const *vtable;
};

/* common device interface */
#define device_read(t, b, s) ((t)->vtable->device.fp_read((t), (b), (s)))

#define device_write(t, b, s) ((t)->vtable->device.fp_write((t), (b), (s)))
#endif
