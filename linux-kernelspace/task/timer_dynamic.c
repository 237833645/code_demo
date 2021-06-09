#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/module.h>
#include <linux/timer.h>

#if 0
1. 初始化
  a. 宏 init_timer  (新内核已经删除)
  b. 宏 DEFINE_TIMER
  c. 宏 timer_setup
2.向内核中添加定时器
  a.  add_timer - 初始化完成后，向内核中添加定时器
      extern void add_timer(struct timer_list *timer);
  b.  mod_timer - 如果需要周期性执行任务，在定时器回调函数中添加 mod_timer
      extern int mod_timer(struct timer_list *timer, unsigned long expires);
3. 手动/自动释放
  a. 定时器运行后，不会再运行，类似自动注销；
  b. del_timer定时器未运行，可手动释放

#endif

static struct timer_list dynamic_timer;

static void dynamic_timer_func(struct timer_list *timer)
{
  pr_info("%s, %d\n", __func__, __LINE__);
  mod_timer(&dynamic_timer, jiffies + 1000 * HZ / 1000);
}

static __init int timer_init(void)
{
  timer_setup(&dynamic_timer, dynamic_timer_func, 0);
  add_timer(&dynamic_timer);
  pr_info("timer! init\n");
  return 0;
}

static __exit void timer_exit(void)
{
  if (timer_pending(&dynamic_timer))
  {
    del_timer(&dynamic_timer);
    pr_info("del_timer \n");
  }

  pr_info("timer! exit\n");
}

module_init(timer_init);
module_exit(timer_exit);

MODULE_AUTHOR("wangfeng");
MODULE_DESCRIPTION("Linux hello module");
MODULE_LICENSE("Dual BSD/GPL");
