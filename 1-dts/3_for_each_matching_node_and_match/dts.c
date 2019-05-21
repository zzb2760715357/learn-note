#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/of_platform.h>
#include <linux/module.h>

/* define name for device and driver */
#define DEV_NAME "DTS_demo"

static const struct of_device_id DTS_demo_of_match[] = {
    { .compatible = "DTS_demo",  },
    { .compatible = "DTS_demoX",  },
    { .compatible = "DTS_demoY",  },
    { },
};

/* probe platform driver */
static int DTS_demo_probe(struct platform_device *pdev)
{
    struct device_node *node;
    const struct of_device_id *match;

  
    printk("DTS probe entence...\n");
    
    for_each_matching_node_and_match(node,DTS_demo_of_match,&match){
        if(node)
            printk("Matching node %s \n",node->name);
        if(match)
            printk("device_id compatible:%s \n",match->compatible);
    }

    return 0;
}



/* remove platform driver */
static int DTS_demo_remove(struct platform_device *pdev)
{
    return 0;
}

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
