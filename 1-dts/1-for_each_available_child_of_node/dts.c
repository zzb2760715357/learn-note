#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/of_platform.h>
#include <linux/module.h>

/* define name for device and driver */
#define DEV_NAME "DTS_demo"

/* probe platform driver */
static int DTS_demo_probe(struct platform_device *pdev)
{
    struct device_node *np = pdev->dev.of_node;
    struct device_node *child;
    int count;
  
    printk("DTS probe entence...\n");

    /* Count child number for current device node */
    count = of_get_child_count(np);
    printk("%s has %d children\n", np->name, count);

    printk("%s child:\n", np->name);
    for_each_child_of_node(np, child)
        printk("  \"%s\"\n", child->name);

    printk("%s available child:\n", np->name);
    for_each_available_child_of_node(np, child)
        printk("  \"%s\"\n", child->name);

    return 0;
}



/* remove platform driver */
static int DTS_demo_remove(struct platform_device *pdev)
{
    return 0;
}

static const struct of_device_id DTS_demo_of_match[] = {
    { .compatible = "DTS_demo, BiscuitOS",  },
    { },
};
MODULE_DEVICE_TABLE(of, DTS_demo_of_match);

/* platform driver information */
static struct platform_driver DTS_demo_driver = {
    .probe  = DTS_demo_probe,
    .remove = DTS_demo_remove,
    .driver = {
        .owner = THIS_MODULE,
        .name = DEV_NAME, /* Same as device name */
        .of_match_table = DTS_demo_of_match,
    },
};
module_platform_driver(DTS_demo_driver);
