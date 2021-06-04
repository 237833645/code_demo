#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/module.h>

#include <linux/hrtimer.h>
#include <linux/ktime.h>

static struct hrtimer timer;

#if 0 // readme
1. 定时器定义与绑定超时回调函数
static struct hrtimer timer;
 
/* 设置回调函数 */
timer.function = hrtimer_hander;
 
2. 定时器初始化
/* 
 *  参数timer是hrtimer指针，
 *  参数clock_id有如下常用几种选项：
 *  CLOCK_REALTIME	//实时时间，如果系统时间变了，定时器也会变
 *  CLOCK_MONOTONIC	//递增时间，不受系统影响
 *  参数mode有如下几种选项：
 * 	HRTIMER_MODE_ABS = 0x0,		/* 绝对模式 */
	HRTIMER_MODE_REL = 0x1,		/* 相对模式 */
	HRTIMER_MODE_PINNED = 0x02,	/* 和CPU绑定 */
	HRTIMER_MODE_ABS_PINNED = 0x02, /* 第一种和第三种的结合 */
	HRTIMER_MODE_REL_PINNED = 0x03, /* 第二种和第三种的结合 */
 */
void hrtimer_init(struct hrtimer *timer, clockid_t clock_id, enum hrtimer_mode mode)；
 
3. 定时器启动
/*
 * 参数timer是hrtimer指针
 * 参数tim是时间，可以使用ktime_set()函数设置时间，
 * 参数mode和初始化的mode参数一致
 */
hrtimer_start(struct hrtimer *timer, ktime_t tim, const enum hrtimer_mode mode)；
 
4. 设置时间
/*
 * 单位为秒和纳秒组合
 */
ktime_t ktime_set(const long secs, const unsigned long nsecs)；
 
/* 设置超时时间，当定时器超时后可以用该函数设置下一次超时时间 */
hrtimer_forward_now(struct hrtimer *timer, ktime_t interval)
 
5. 注意事项：
定时器超时后会调用回调函数，回调函数结构类似这样：
enum hrtimer_restart		(*function)(struct hrtimer *);
 
enum hrtimer_restart {
	HRTIMER_NORESTART,	/* 不重启定时器 */
	HRTIMER_RESTART,	/* 重启定时器 */
};
在回调函数返回前要手动设置下一次超时时间。
另外，回调函数执行时间不宜过长，因为是在中断上下文中，如果有什么任务的话，最好使用工作队列等机制。
 
6. 关闭定时器
int hrtimer_cancel(struct hrtimer *timer)；
#endif

/* 定时器回调函数 */
static enum hrtimer_restart function(struct hrtimer *hr)
{
  static int i = 0;

  printk(KERN_ALERT "hrtimer function call %d\n", i++);

  /* 设置3s下次过期时间  ktime_set() 单位为秒和纳秒组合 */
  hrtimer_forward_now(hr, ms_to_ktime(1000) /*ktime_set(3,0)*/);

  /* 该参数将重新启动定时器 */
  return HRTIMER_RESTART; // : HRTIMER_NORESTART;
}

static __init int hrtimer_demo_init(void)
{
  printk(KERN_ALERT "hrtimer_demo_init\n");

  /* hrtimer初始化 */
  hrtimer_init(&timer, CLOCK_MONOTONIC, HRTIMER_MODE_REL);

  /* 设置回调函数 */
  timer.function = function;

  /* hrtimer启动 */
  hrtimer_start(&timer, ktime_set(1, 0) /*ms_to_ktime(2000)*/, HRTIMER_MODE_REL);

  return 0;
}

static __exit void hrtimer_demo_exit(void)
{
  /* hrtimer注销 */
  hrtimer_cancel(&timer);

  printk(KERN_ALERT "hrtimer_demo_exit\n");
}

MODULE_AUTHOR("hrtimer_demo ");
MODULE_DESCRIPTION("Linux hrtimer_demo module");
MODULE_LICENSE("Dual BSD/GPL");

module_init(hrtimer_demo_init);
module_exit(hrtimer_demo_exit);
