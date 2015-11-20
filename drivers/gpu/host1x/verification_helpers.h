int nondet_int();

enum {false, true};

struct mutex {
  int locked;
  //struct mutex lock;
};

void mutex_init(struct mutex *mutex) {
  mutex->locked = false;
}

void mutex_lock(struct mutex *mutex) {
  assert(!mutex->locked);
  mutex->locked = true;
}

void mutex_unlock(struct mutex *mutex) {
  assert(mutex->locked);
  mutex->locked = false;
}
