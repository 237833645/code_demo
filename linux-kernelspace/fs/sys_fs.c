#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/module.h>
#include <linux/sysfs.h>

static __init int sysfs_init(void)
{
  pr_info("sysfs! init\n");
  return 0;
}

static __exit void sysfs_exit(void)
{
  pr_info("sysfs! exit\n");
}

module_init(sysfs_init);
module_exit(sysfs_exit);

MODULE_AUTHOR("wangfeng");
MODULE_DESCRIPTION("Linux hello module");
MODULE_LICENSE("Dual BSD/GPL");
