#include "verify_helpers_empty.h"
#include "dev.h"

int main() {
  const struct of_device_id *id;
  struct host1x h;
	struct host1x *host = &h;
	struct resource *regs;
	int syncpt_irq;
	int err;
    INIT_LIST_HEAD(&locks);
	id = nondet_int(); /* of_match_device(host1x_of_match, &pdev->dev); */
	if (!id)
      return -nondet_int();

	regs = nondet_int();/* platform_get_resource(pdev, IORESOURCE_MEM, 0); */
	if (!regs) {
		/* dev_err(&pdev->dev, "failed to get registers\n"); */
		return -ENXIO;
	}

	syncpt_irq = nondet_int(); /* platform_get_irq(pdev, 0); */
	if (syncpt_irq < 0) {
		/* dev_err(&pdev->dev, "failed to get IRQ\n"); */
		return -ENXIO;
	}

	host = nondet_int(); /* devm_kzalloc(&pdev->dev, sizeof(*host), GFP_KERNEL); */
	if (!host)
      return -nondet_int();

	mutex_init(&host->devices_lock);
	INIT_LIST_HEAD(&host->devices);
	INIT_LIST_HEAD(&host->list);
	host->info = id->data;

    host1x_channel_list_init(host);

    /* host1x_syncpt_init(host); */

    host1x_intr_init(host, syncpt_irq);
    check_locks(); 

    err = host1x_register(host);
		return 0;
}
