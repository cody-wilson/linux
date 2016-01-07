#ifndef DATARACE_H__
#define DATARACE_H__

#include "verification_helpers.h"
#include "dev.h"

struct list_head *get_device_list(struct mutex *lock, struct list_head *list) {
  if (lock->locked == false)
    assert(0);
  return list;
}

#endif
