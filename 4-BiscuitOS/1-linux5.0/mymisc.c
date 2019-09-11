#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/init.h>
#include <linux/fs.h>
#include <linux/miscdevice.h>


int misc_demo_open (struct inode *inode, struct file *filp)
{
	printk("zhuangzebin<%s-%d>\n",__func__,__LINE__);

	return 0;
}

int misc_demo_release (struct inode *inode, struct file *filp)
{
	printk("zhuangzebin<%s-%d>\n",__func__,__LINE__);

	return 0;
}


ssize_t misc_demo_read (struct file *filp, char __user *buf, size_t count, loff_t * offset)
{
	return 0;
}

ssize_t misc_demo_write (struct file *filp, const char __user *buf, size_t count, loff_t *offset)
{
	return 0;
}


static const struct file_operations misc_demo_fops = {
	.open = misc_demo_open,
	.release = misc_demo_release, 
	.write = misc_demo_write,
	.read = misc_demo_read,
};


static struct miscdevice misc_demo_device = {
	.minor = MISC_DYNAMIC_MINOR,
	.name = "misc_demo",
	.fops = &misc_demo_fops,
};

static int __init misc_demo_init(void)
{
	int ret = -1;
	
	printk("zhuangzebin<%s-%d>\n",__func__,__LINE__);
	ret = misc_register(&misc_demo_device);
	if (ret < 0){
		printk("zhuangzebin<%s-%d> register misc error\n",__func__,__LINE__);
	}

	return ret;
}

static void __exit misc_demo_exit(void)
{
	printk("zhuangzebin<%s-%d>\n",__func__,__LINE__);

	misc_deregister(&misc_demo_device);
}



module_init(misc_demo_init);
module_exit(misc_demo_exit);

