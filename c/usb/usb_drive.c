/* usb_drive.c */
#include "usb_drive.h"

#include <errno.h>
#include <stdio.h>
#include <stdlib.h>

struct usb_drive {
  struct device device;
  /* whatever */
};

static int usb_drive_destroy(void *self_);
static int usb_drive_read(void *self_, void *buf, size_t size);
static int usb_drive_write(void *self_, void const *buf, size_t size);

static struct device_vtable const g_vtable = {
    {/* object interface */
     usb_drive_destroy},
    {/* device interface */
     usb_drive_read, usb_drive_write}};

int usb_drive_create(struct device **pself) {
  struct usb_drive *self = (struct usb_drive *)malloc(sizeof(*self));
  if (self) {
    *pself = &self->device;
    self->device.vtable = &g_vtable;
    return 0;
  }
  return ENOMEM;
}

int usb_drive_destroy(void *const self_) {
  struct usb_drive *self = (struct usb_drive *)self_;
  printf("destroyed a usb_drive(%p)\n", self_);
  free(self);
  return 0;
}

int usb_drive_read(void *const self_, void *buf, size_t size) {
  printf("read from a usb_drive(%p, %p, %lu)\n", self_, buf,
         (unsigned long)size);
  return 0;
}

int usb_drive_write(void *const self_, void const *buf, size_t size) {
  printf("wrote to a usb_drive(%p, %p, %lu)\n", self_, buf,
         (unsigned long)size);
  return 0;
}
