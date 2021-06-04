#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/module.h>
#include <linux/debugfs.h>

static __init int debug_fs_init(void)
{
  pr_info("debug_fs! init\n");
  return 0;
}

static __exit void debug_fs_exit(void)
{
  pr_info("debug_fs! exit\n");
}

module_init(debug_fs_init);
module_exit(debug_fs_exit);

MODULE_AUTHOR("wangfeng");
MODULE_DESCRIPTION("Linux hello module");
MODULE_LICENSE("Dual BSD/GPL");
