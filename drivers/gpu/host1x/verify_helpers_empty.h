#ifndef VERIFY_HELPERS_EMPTY_H_
#define VERIFY_HELPERS_EMPTY_H_
#include "verification_helpers.h"
typedef unsigned int dma_addr_t;

typedef unsigned int u32;

typedef unsigned char u8;

typedef unsigned short u16;

typedef unsigned long u64;

struct delayed_work;

typedef unsigned int bool;

typedef unsigned int ktime_t;

typedef unsigned int __iomem; 

typedef struct mutex spinlock_t;

typedef unsigned int atomic_t;  

typedef unsigned int irqreturn_t;

typedef unsigned int size_t;

typedef int s32;

#define GFP_KERNEL nondet_int()

#define ENOMEM nondet_int()

#define WARN_OFF nondet_int()

#define WARN_ON(condition) nondet_int()

#define EINVAL nondet_int()

#define NULL 0

#define ULONG_MAX nondet_int()

#define PAGE_SHIFT nondet_int()

#define PAGE_MASK nondet_int()

struct kref {
	atomic_t refcount;
};


struct device_node {
	const char *name;
	const char *type;
	/* phandle phandle; */
	const char *full_name;
	/* struct fwnode_handle fwnode; */

	/* struct	property *properties; */
	/* struct	property *deadprops;	/\* removed properties *\/ */
	struct	device_node *parent;
	struct	device_node *child;
	struct	device_node *sibling;
	struct	kobject kobj;
	unsigned long _flags;
	void	*data;
};


void smp_rmb();

u32 host1x_syncpt_read_max(void *sp);

u32 atomic_read(u32);

u32 seq_write(void *file, void *str, u32 len);

void pr_info(char *str, ...);

u32 writel(void *w, u32 ptr);

u32 readl(u32 ptr);

void *platform_get_resource(void *dev, int mem, int num);

void dev_err(void *dev, char *str, ...);

#define ENXIO 0

struct of_device_id {
  char *compatible;
  void *data;
};


struct device {
  struct device		*parent;
  struct device_driver *driver;	/* which driver has allocated this */
  u32			id;	/* device instance */
  
  spinlock_t		devres_lock;
  struct list_head	devres_head;
  void	(*release)(struct device *dev);
  struct bus_type	*bus;		/* type of bus device is on */
  void *of_node;
};

struct device_driver {
	const char		*name;
  	struct bus_type		*bus;
	int (*probe) (struct device *dev);
	int (*remove) (struct device *dev);
	void (*shutdown) (struct device *dev);
	/* int (*suspend) (struct device *dev, pm_message_t state); */
	int (*resume) (struct device *dev);
};

struct platform_device {
  const char      *name;
  int             id;
  bool            id_auto;
  struct device   dev;
  u32             num_resources;
  void *resource;
  void *id_entry;
  char *driver_override; /* Driver name to force a match */
  
  /* MFD cell pointer */
  void *mfd_cell;
};

#define IS_ERR nondet_int()
#define PTR_ERR nondet_int()

struct list_head {
  struct list_head *prev, *next;
};

#define offsetof(TYPE, MEMBER)	((size_t)&((TYPE *)0)->MEMBER)

#define container_of(ptr, type, member) ({			\
	const typeof( ((type *)0)->member ) *__mptr = (ptr);	\
	(type *)( (char *)__mptr - offsetof(type,member) );})

#define list_entry(ptr, type, member) \
	container_of(ptr, type, member)

#define list_first_entry(ptr, type, member) \
	list_entry((ptr)->next, type, member)

#define list_last_entry(ptr, type, member) \
	list_entry((ptr)->prev, type, member)

#define list_next_entry(pos, member) \
	list_entry((pos)->member.next, typeof(*(pos)), member)

#define list_prev_entry(pos, member) \
	list_entry((pos)->member.prev, typeof(*(pos)), member)

#define list_for_each_entry(pos, head, member)				\
	for (pos = list_first_entry(head, typeof(*pos), member);	\
	     &pos->member != (head);					\
	     pos = list_next_entry(pos, member))

#define list_for_each_entry_reverse(pos, head, member)			\
	for (pos = list_last_entry(head, typeof(*pos), member);		\
	     &pos->member != (head); 					\
	     pos = list_prev_entry(pos, member))

#define list_for_each_entry_safe(pos, n, head, member)			\
	for (pos = list_first_entry(head, typeof(*pos), member),	\
		n = list_next_entry(pos, member);			\
	     &pos->member != (head); 					\
	     pos = n, n = list_next_entry(n, member))

#define list_for_each_entry_from(pos, head, member) 			\
	for (; &pos->member != (head);					\
	     pos = list_next_entry(pos, member))

static inline void INIT_LIST_HEAD(struct list_head *list)
{
	list->next = list;
	list->prev = list;
}

static inline void __list_add(struct list_head *new,
			      struct list_head *prev,
			      struct list_head *next)
{
	next->prev = new;
	new->next = next;
	new->prev = prev;
	prev->next = new;
}

static inline void list_add_tail(struct list_head *new, struct list_head *head)
{
	__list_add(new, head->prev, head);
}


static inline void __list_del(struct list_head * prev, struct list_head * next)
{
	next->prev = prev;
}

static inline void __list_del_entry(struct list_head *entry)
{
	__list_del(entry->prev, entry->next);
}

#define POISON_POINTER_DELTA 0
#define LIST_POISON1  ((void *) 0x100 + POISON_POINTER_DELTA)
#define LIST_POISON2  ((void *) 0x200 + POISON_POINTER_DELTA)


static inline void list_del(struct list_head *entry)
{
	__list_del(entry->prev, entry->next);
	entry->next = LIST_POISON1;
	entry->prev = LIST_POISON2;
}

static inline void of_node_put(struct device_node *node) { }

static inline void list_move_tail(struct list_head *list,
				  struct list_head *head)
{
	__list_del_entry(list);
	list_add_tail(list, head);
}

static inline int list_empty(const struct list_head *head)
{
	return head->next == head;
}

static inline void list_del_init(struct list_head *entry)
{
	__list_del_entry(entry);
	INIT_LIST_HEAD(entry);
}

struct dev_pm_ops {
	int (*prepare)(struct device *dev);
	void (*complete)(struct device *dev);
	int (*suspend)(struct device *dev);
	int (*resume)(struct device *dev);
	int (*freeze)(struct device *dev);
	int (*thaw)(struct device *dev);
	int (*poweroff)(struct device *dev);
	int (*restore)(struct device *dev);
	int (*suspend_late)(struct device *dev);
	int (*resume_early)(struct device *dev);
	int (*freeze_late)(struct device *dev);
	int (*thaw_early)(struct device *dev);
	int (*poweroff_late)(struct device *dev);
	int (*restore_early)(struct device *dev);
	int (*suspend_noirq)(struct device *dev);
	int (*resume_noirq)(struct device *dev);
	int (*freeze_noirq)(struct device *dev);
	int (*thaw_noirq)(struct device *dev);
	int (*poweroff_noirq)(struct device *dev);
	int (*restore_noirq)(struct device *dev);
	int (*runtime_suspend)(struct device *dev);
	int (*runtime_resume)(struct device *dev);
	int (*runtime_idle)(struct device *dev);
};

struct bus_type {
	const char		*name;
	const char		*dev_name;
	struct device		*dev_root;
	int (*match)(struct device *dev, struct device_driver *drv);
	int (*probe)(struct device *dev);
	int (*remove)(struct device *dev);
	void (*shutdown)(struct device *dev);

	int (*online)(struct device *dev);
	int (*offline)(struct device *dev);

	int (*resume)(struct device *dev);

	const struct dev_pm_ops *pm;

};

#define DEFINE_MUTEX(mutexname) \
  struct mutex mutexname = {.locked = false}

#define LIST_HEAD_INIT(name) { &(name), &(name) }

#define LIST_HEAD(name) \
	struct list_head name = LIST_HEAD_INIT(name)

#define min_t(type, x, y) ({			\
	type __min1 = (x);			\
	type __min2 = (y);			\
	__min1 < __min2 ? __min1: __min2; })

struct host1x *dev_get_drvdata(struct device *arg);

void dma_free_writecombine();

void *dma_alloc_writecombine();

void *dev_name(struct device *dev);

void trace_host1x_wait_cdma(char *name, int event);

void schedule();

ktime_t ktime_get();

unsigned long msecs_to_jiffies(ktime_t time);

int schedule_delayed_work(void *work, u64 delay);

int cancel_delayed_work(void *work);

void dev_dbg();

void pr_warn(char *str, ...);

#define EBUSY nondet_int();

void trace_host1x_cdma_begin(char *str, ...);

void trace_host1x_cdma_push(char *str, ...);

void trace_host1x_cdma_end(char *str, ...);

struct __wait_queue_head {
	spinlock_t		lock;
	struct list_head	task_list;
};
typedef struct __wait_queue_head wait_queue_head_t;

void kfree(void *obv);

static inline void __list_add(struct list_head *new,
			      struct list_head *prev,
			      struct list_head *next)
{
	next->prev = new;
	new->next = next;
	new->prev = prev;
	prev->next = new;
}

static inline void list_add(struct list_head *new, struct list_head *head)
{
	__list_add(new, head, head->next);
}

int atomic_inc_return();

typedef struct __wait_queue wait_queue_t;

typedef int (*wait_queue_func_t)(wait_queue_t *wait, unsigned mode, int flags, void *key);


struct __wait_queue {
	unsigned int		flags;
	void			*private;
	wait_queue_func_t	func;
	struct list_head	task_list;
};

#define WQ_FLAG_EXCLUSIVE nondet_int()

void __wake_up(wait_queue_head_t *q, unsigned int mode, int nr, void *key) {
  wait_queue_t *curr, *next;

  mutex_lock(&q->lock);
  list_for_each_entry_safe(curr, next, &q->task_list, task_list) {
    unsigned flags = curr->flags;

    if (curr->func(curr, mode, 0, key) &&
        (flags & WQ_FLAG_EXCLUSIVE) && !--nr)
      break;
  }
  mutex_unlock(&q->lock);
}

#define wake_up(x) __wake_up(x, 1 | 2, 1, NULL)

#define wake_up_interruptible(x)	__wake_up(x, 1, 1, NULL)

void kref_put(void *a, void *b);

void spin_lock(spinlock_t *lock) {
  mutex_lock(lock);
}

void spin_unlock(spinlock_t *lock) {
  mutex_unlock(lock);
}

spinlock_t spin_lock_init(spinlock_t *lock) {
  mutex_init(lock);
}

int atomic_cmpxchg(int *p, int cmp, int val) {
  *p = (*p == cmp) ?  val : *p;
  return *p;
}

void *create_workqueue(char *str);
void destroy_workqueue(void *queue);
void snprintf(char *str,...);

unsigned long clk_get_rate(void *clk);

#define DIV_ROUND_UP(n,d) (((n) + (d) - 1) / (d))
#define BITS_PER_LONG sizeof(long) * 8
#define ENOSYS nondet_int()

int find_first_zero_bit(void *p, unsigned int size) {
  char *buf = (char *)p;
  char temp;
  for (int i = 0; i < size; i++) {
    if (i % 8 == 0) 
      temp = buf[i/8];

    if (!(temp & 0b1)) {
      return i;
    }

    temp >>= 1;
  }

  return i+1;
}

void *kzalloc(int size, int opt);

#define BIT(nr)			(1UL << (nr))

struct delayed_work;

int find_first_bit(void *p, unsigned int size) {
  char *buf = (char *)p;
  char temp;
  for (int i = 0; i < size; i++) {
    if (i % 8 == 0) 
      temp = buf[i/8];

    if (temp & 0b1) {
      return i;
    }

    temp >>= 1;
  }

  return i+1;
}

int find_next_bit(void *p, unsigned int size, int start) {
  char *buf = (char *)p;
  char temp;
  for (int i = start; i < size; i++) {
    if (i % 8 == 0) 
      temp = buf[i/8];

    if (temp & 0b1) {
      return i;
    }

    temp >>= 1;
  }

  return i+1;
}

#define for_each_set_bit(bit, addr, size) \
	for ((bit) = find_first_bit((addr), (size));		\
	     (bit) < (size);					\
	     (bit) = find_next_bit((addr), (size), (bit) + 1))

struct scatterlist {
#ifdef CONFIG_DEBUG_SG
	unsigned long	sg_magic;
#endif
	unsigned long	page_link;
	unsigned int	offset;
	unsigned int	length;
	dma_addr_t	dma_address;
#ifdef CONFIG_NEED_SG_DMA_LENGTH
	unsigned int	dma_length;
#endif
};


struct sg_table {
	struct scatterlist *sgl;	/* the list */
	unsigned int nents;		/* number of mapped entries */
	unsigned int orig_nents;	/* original size of list */
};
#define MAX_PHANDLE_ARGS nondet_int()



struct of_phandle_args {
	struct device_node *np;
	int args_count;
	u32 args[MAX_PHANDLE_ARGS];
};

#define ERR_PTR nondet_int

#define ENODEV nondet_int()

#define EPROBE_DEFER nondet_int()

void platform_device_put(void *p);

#define time_after(a,b)		\
  ((long)((b) - (a)) < 0)
#define time_before(a,b)	time_after(b,a)

void usleep_range(unsigned long min, unsigned long max);

#define ETIMEDOUT nondet_int();

int clk_enable(void *clk) {
  return nondet_int();
}

int clk_disable(void *clk) {
  return nondet_int();
}

#define ARRAY_SIZE(x) nondet_int()

extern const struct of_device_id *of_match_node(
	const struct of_device_id *matches, const struct device_node *node);

#define IORESOURCE_MEM nondet_int()

static inline void *platform_get_drvdata(const struct platform_device *pdev);

int clk_prepare(void *clk);

static inline void platform_set_drvdata(struct platform_device *pdev,
                                        void *data);

void clk_unprepare(void *clk);

char * kasprintf(void *str, ...);

void memcpy(void *dest, const void *src, size_t n) {
  char *destc = (char *)dest;
  const char *srcc = (const char *)src;

  for (int i = 0; i < n; i++) {
    destc[i] = srcc[i];
  }
}

#define BITS_TO_LONGS(bits) DIV_ROUND_UP(bits, 8*8)

#define DECLARE_BITMAP(name, bits) \
  unsigned long name[BITS_TO_LONGS(bits)]

static inline void memset(void *s, int c, size_t n) {
  char *sc = (char *)s;
  
  for (int i = 0; i < n; i++) {
    sc[i] = c;
  }
}

static inline void bitmap_zero(unsigned long *dst, unsigned int nbits)
{
	if (nbits < 8*8)
		*dst = 0UL;
	else {
		unsigned int len = BITS_TO_LONGS(nbits) * sizeof(unsigned long);
		memset(dst, 0, len);
	}
}

void set_bit(unsigned long nr, volatile unsigned long *addr);

#define CONFIG_TEGRA_HOST1X_FIREWALL nondet_int()

#define wmb()   asm volatile("sfence" : : : "memory")

#define HZ 1000


#define __WAIT_QUEUE_HEAD_INITIALIZER(name) {				\
	.lock		= name.lock,		\
	.task_list	= { &(name).task_list, &(name).task_list } }

#define DECLARE_WAIT_QUEUE_HEAD(name) \
  wait_queue_head_t name = __WAIT_QUEUE_HEAD_INITIALIZER(name); \
  mutex_init(&name.lock);
# define DECLARE_WAIT_QUEUE_HEAD_ONSTACK(name) DECLARE_WAIT_QUEUE_HEAD(name)

#define wait_event_interruptible_timeout(wq, condition, timeout)	nondet_int()

#define EAGAIN nondet_int()

#define LONG_MAX nondet_int()

typedef unsigned long atomic_long_t;
typedef void (*work_func_t)(struct work_struct *work);
struct work_struct {
	atomic_long_t data;
	struct list_head entry;
	work_func_t func;
};
#endif
