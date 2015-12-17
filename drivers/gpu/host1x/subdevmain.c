#include "verify_helpers_empty.h"
#include "bus.h"
#include "bus.c"
#include "host1x.h"
int main(int argc, char *argv[]) {
  struct host1x_device dev;
  struct host1x_subdev sub;
  struct host1x_device *device = &dev;
  struct host1x_subdev *subdev = &sub;
  mutex_init(&device->subdevs_lock);
  mutex_init(&device->clients_lock);
  host1x_subdev_unregister(device, subdev);

}
