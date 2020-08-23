#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/module.h>

static __init int helloworld_init(void)
{
    printk(KERN_INFO "Hello World! init\n");
    return 0;
}

static __exit void helloworld_exit(void)
{
    printk(KERN_INFO "Hello World! exit\n");
}


module_init(helloworld_init);
module_exit(helloworld_exit);

MODULE_AUTHOR("helloworld");
MODULE_DESCRIPTION("Linux hello module");
MODULE_LICENSE("Dual BSD/GPL");


