/* usb_drive.c */
#include "usb_drive.h"

#include <errno.h>
#include <stdio.h>
#include <stdlib.h>

struct usb_drive {
  struct device device;
  /* whatever */
};

static int object_destroy(void *p);
static int device_read(void *const p, void *q, size_t s);
static int device_write(void *const p, void const *q, size_t s);

#if 0
static struct device_vtable const g_vtable[
{ /* object interface */
object_destroy
},

{ /* device interface */
device_read,
device_write
}
];
#else
static struct device_vtable const g_vtable = {{/* object interface */
                                               object_destroy},
                                              {/* device interface */
                                               device_read, device_write}};
#endif

int usb_drive_create(struct device **pself) {
  struct usb_drive *const self = malloc(sizeof(*self));
  if (self) {
    *pself = &self->device;
    self->device.vtable = &g_vtable;
    return 0;
  }
  return ENOMEM;
}

int object_destroy(void *const self_) {
  struct usb_drive *const self = self_;
  free(self);
  printf("destroyed a usb_drive(%p)\n", self_);
  return 0;
}

int device_read(void *const self_, void *buf, size_t size) {
  struct usb_drive *const self = self_;
  printf("read from a usb_drive(%p, %p, %lu)\n", self_, buf,
         (unsigned long)size);
  return 0;
}

int device_write(void *const self_, void const *buf, size_t size) {
  struct usb_drive *const self = self_;
  printf("wrote to a usb_drive(%p, %p, %lu)\n", self_, buf,
         (unsigned long)size);
  return 0;
}
