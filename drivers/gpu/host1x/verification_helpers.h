#ifndef VERIFICATION_HELPERS_H_
#define VERIFICATION_HELPERS_H_


#include "verify_helpers_empty.h"

int nondet_int();
int lock_count = 0;

enum {false, true};

struct list_head locks;

struct mutex {
  int locked;
  struct list_head node;
};

struct semaphore {
  int count;
};


void mutex_init(struct mutex *mutex) {
  mutex->locked = false;
}

void mutex_lock(struct mutex *mutex) {
  /* assert(mutex->locked == false); */
  /* if (lock_count > 0) { */
  /*   assert(0); */
  /* } */
  mutex->locked = true;
  lock_count++;
  list_add(&locks, &mutex->node);
}

void mutex_unlock(struct mutex *mutex) {
  /* assert(mutex->locked == true); */
  mutex->locked = false;
  lock_count--;
  list_del(&mutex->node);
}

void check_locks() {
  if (list_empty(&locks))
    assert(0);
}

void sema_init(void *sem, int count);

void down(void *sem);

void up(void *sem);
#endif 
