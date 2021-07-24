#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/module.h>
#include <linux/gpio.h>
#include <linux/delay.h>
#include <linux/kthread.h>


static struct task_struct *kthread = NULL;

struct gpio led[] = {
    {17, GPIOF_OUT_INIT_LOW, "led0"},
    {27, GPIOF_OUT_INIT_LOW, "led1"},
    {22, GPIOF_OUT_INIT_LOW, "led2"},
};

/***********************************************************************/


static int gpio_led_init(void)
{
    int ret = 0;
    int i = 0;

    ret = gpio_request_array(led, ARRAY_SIZE(led));
    if (ret < 0) {
	    pr_err("gpio_request error!\n");    
        return -1;
    }

    for (i=0; i< ARRAY_SIZE(led); i++) {
        gpio_set_value(led[i].gpio, 0);
    }

    return ret;
}

static int gpio_led_run(int flag)
{
    int ret = 0;
    int i = 0;

    for (i=0; i< ARRAY_SIZE(led); i++) {
        gpio_set_value(led[i].gpio, flag);
    }

    return ret;
}

static void gpio_led_exit(void)
{
    int i = 0;

    for (i=0; i< ARRAY_SIZE(led); i++) {
        gpio_set_value(led[i].gpio, 0);
    }
    gpio_free_array(led, ARRAY_SIZE(led));
}


/***********************************************************************/

static int thread_fun(void *data)
{
    int count = 0;

    /*
    如果该内核线程已经被设置stop标志了，则会返回1，否则返回0。
    */
    while (!kthread_should_stop())
    {
        gpio_led_run(1);
        msleep_interruptible(500);

        gpio_led_run(0);
        msleep_interruptible(500);

        count++;
        pr_info("thread_fun run count = %d\n", count);
    }

    return 0;
}

/***********************************************************************/


static __init int gpiodemo0_init(void)
{
    int ret = 0;

    pr_info("gpiodemo0! init\n");

    ret = gpio_led_init();
    if (ret != 0)
    {
        pr_err("gpio_led_init failed\n");
        return -1;
    }

    kthread = kthread_run(thread_fun, NULL, "kthread_gpio_demo1");
    if (kthread == NULL)
    {
        pr_err("kthread_run failed\n");
        return -1;
    }

    return ret;
}

static __exit void gpiodemo0_exit(void)
{
    if (kthread != NULL)
    {
        kthread_stop(kthread);
        pr_info("%s %d kthread_stop \n", __func__, __LINE__);
        kthread = NULL;
    }

    gpio_led_exit();

    pr_info("gpiodemo0! exit\n");
}

module_init(gpiodemo0_init);
module_exit(gpiodemo0_exit);

MODULE_AUTHOR("wangfeng");
MODULE_DESCRIPTION("Linux gpiodemo0 module");
MODULE_LICENSE("Dual BSD/GPL");
