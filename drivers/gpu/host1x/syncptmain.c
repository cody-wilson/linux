#include "verify_helpers_empty.h"
#include "dev.h"

int main(int argc, char *argv[]) {
  struct platform_device *pdev;
  const struct of_device_id *id;
  struct host1x h;
  struct host1x *host = &h;
  struct resource *regs;
  int syncpt_irq;
  int err;
    
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
    mutex_init(&host->intr_mutex);
	INIT_LIST_HEAD(&host->devices);
	INIT_LIST_HEAD(&host->list);
	host->dev = &pdev->dev;
	host->info = id->data;

	/* set common host1x device data */
	/* platform_set_drvdata(pdev, host); */

	host->regs = nondet_int(); /* devm_ioremap_resource(&pdev->dev, regs); */
	if (nondet_int()/* IS_ERR(host->regs) */)
      return nondet_int();/* PTR_ERR(host->regs); */

	if (nondet_int()/* host->info->init */) {
      err = nondet_int();/* host->info->init(host); */
		if (err)
			return err;
	}

	host->clk = (void *) nondet_int(); /* devm_clk_get(&pdev->dev, 0); */
	if (IS_ERR) {
		dev_err(&pdev->dev, "failed to get clock\n");
		err = PTR_ERR;
		return err;
	}

	err = host1x_channel_list_init(host);
	if (err) {
		dev_err(&pdev->dev, "failed to initialize channel list\n");
		return err;
	}

	err = nondet_int(); /* clk_prepare_enable(host->clk); */
	if (err < 0) {
		dev_err(&pdev->dev, "failed to enable clock\n");
		return err;
	}

	err = host1x_syncpt_init(host);
	if (err) {
		dev_err(&pdev->dev, "failed to initialize syncpts\n");
		goto fail_unprepare_disable;
	}

 fail_deinit_intr:
	host1x_intr_deinit(host);
 fail_deinit_syncpt:
	host1x_syncpt_deinit(host);
 fail_unprepare_disable:
	/* clk_disable_unprepare(host->clk); */
	return err;
}
