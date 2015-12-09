#ifndef VERIFICATION_HELPERS_H_
#define VERIFICATION_HELPERS_H_

int nondet_int();

enum {false, true};

struct mutex {
  int locked;
  //struct mutex lock;
};

struct semaphore {
  int count;
};


void mutex_init(struct mutex *mutex) {
  mutex->locked = false;
}

void mutex_lock(struct mutex *mutex) {
  assert(mutex->locked == false);
  mutex->locked = true;
}

void mutex_unlock(struct mutex *mutex) {
  assert(mutex->locked == true);
  mutex->locked = false;
}

void sema_init(void *sem, int count);

void down(void *sem);

void up(void *sem);
#endif 
