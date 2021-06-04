#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/module.h>
#include <linux/kthread.h>
#include <linux/delay.h>

static struct task_struct *kthread = NULL;

static int thread_fun(void *data)
{
    int i = 0;

    /*
    如果该内核线程已经被设置stop标志了，则会返回1，否则返回0。
    */
    while (!kthread_should_stop())
    {
        msleep_interruptible(1000);
        pr_info("thread_fun %d\n", i);
        i++;
    }

    return 0;
}

static __init int kthread_init(void)
{
    pr_info("%s %d\n", __func__, __LINE__);

    /*
        kthread_run - create and wake a thread.
    */
    kthread = kthread_run(thread_fun, NULL, "kthread_demo");
    if (kthread == NULL)
    {
        pr_err("kthread_run failed\n");
        return -1;
    }

    return 0;
}

static __exit void kthread_exit(void)
{
    pr_info("%s %d\n", __func__, __LINE__);

    if (kthread != NULL)
    {
        /*
        这个调用是会阻塞等待，直到内核线程k退出为止。
        原因为因为此函数内部会调用wait_for_completion()的方法(通过等待队列来实现)，
        阻塞等待内核线程自身的退出。
        */
        kthread_stop(kthread);

        pr_info("%s %d kthread_stop \n", __func__, __LINE__);

        kthread = NULL;
    }
}

module_init(kthread_init);
module_exit(kthread_exit);

MODULE_AUTHOR("wangfeng");
MODULE_DESCRIPTION("Linux hello module");
MODULE_LICENSE("Dual BSD/GPL");
