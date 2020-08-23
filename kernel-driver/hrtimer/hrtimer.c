#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/init.h>

#include <linux/hrtimer.h>
#include <linux/ktime.h>

static struct hrtimer timer;

static enum hrtimer_restart function(struct hrtimer *hr)
{
    static int i = 0;
    printk(KERN_ALERT "hrtimer function call %d\n", i++);

    if(i == 20)
    {
        hrtimer_cancel(&timer);
        return HRTIMER_NORESTART;
    }

	hrtimer_forward_now(hr, ms_to_ktime(1000));

	return HRTIMER_RESTART;// : HRTIMER_NORESTART;
}

static __init int hrtimer_demo_init(void)
{
    printk(KERN_ALERT "hrtimer_demo_init\n");

    hrtimer_init(&timer,CLOCK_MONOTONIC, HRTIMER_MODE_REL);
    timer.function = function;
    hrtimer_start(&timer,ms_to_ktime(2000),HRTIMER_MODE_REL);

    return 0;
}

static __exit void hrtimer_demo_exit(void)
{
    hrtimer_cancel(&timer);
    printk(KERN_ALERT "hrtimer_demo_exit\n");
}


MODULE_AUTHOR("hrtimer_demo ");
MODULE_DESCRIPTION("Linux hrtimer_demo module");
MODULE_LICENSE("Dual BSD/GPL");

module_init(hrtimer_demo_init);
module_exit(hrtimer_demo_exit);


