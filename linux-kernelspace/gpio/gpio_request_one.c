#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/module.h>
#include <linux/gpio.h>
#include <linux/delay.h>

struct gpio led[] = {
    {17, GPIOF_OUT_INIT_LOW, "led0"},
};

static __init int gpiodemo0_init(void)
{
    int ret;
    int i;

    pr_info("gpiodemo0! init\n");

    ret = gpio_request_one(led[0].gpio, led[0].flags, led[0].label);
    if (ret < 0) {
	pr_err("gpio_request error!\n");    
        return -1;
    }

    for (i=0; i<10; i++) {
        gpio_set_value(led[0].gpio, 1);
        //pr_info("gpio_set_value 1");
        //ssleep(1);
        gpio_set_value(led[0].gpio, 0); 
        //pr_info("gpio_set_value 0");
        //ssleep(1);
    }
    return 0;
}

static __exit void gpiodemo0_exit(void)
{
    gpio_set_value(led[0].gpio, 0);
    gpio_free(led[0].gpio);
    pr_info("gpiodemo0! exit\n");
}

module_init(gpiodemo0_init);
module_exit(gpiodemo0_exit);

MODULE_AUTHOR("wangfeng");
MODULE_DESCRIPTION("Linux gpiodemo0 module");
MODULE_LICENSE("Dual BSD/GPL");
