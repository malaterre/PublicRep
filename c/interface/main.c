#include "usb_drive.h"

/* common object interface */
#define object_destroy(t) ((t)->vtable->object.fp_destroy((t)))

/* common device interface */
#define device_read(t, b, s) ((t)->vtable->device.fp_read((t), (b), (s)))

#define device_write(t, b, s) ((t)->vtable->device.fp_write((t), (b), (s)))

void read_write(struct device *const self) {
  char buf[100];

  device_read(self, buf, 50);

  device_write(self, buf, 5);
}

int main(void) {
  struct device *a_device;

  if (!usb_drive_create(&a_device)) {
    read_write(a_device);

    object_destroy(a_device);
  }

  return 0;
}
