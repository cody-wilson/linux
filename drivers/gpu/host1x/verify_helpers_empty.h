#include "verification_helpers.h"

typedef unsigned int dma_addr_t;

typedef unsigned int u32;

struct delayed_work;

typedef unsigned int bool;

typedef unsigned int ktime_t;

typedef unsigned int __iomem; 

typedef struct mutex spinlock_t;

typedef unsigned int atomic_t;  

typedef unsigned int irqreturn_t;

typedef unsigned int size_t;

typedef int s32;

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
