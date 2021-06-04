#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/module.h>
#include <linux/debugfs.h>

// CONFIG_DEBUG_FS=y让内核支持debugfs, 内核默认会将debugfs挂载在/sys/kernel/debug目录下

/*
#define DEFINE_DEBUGFS_ATTRIBUTE(__fops, __get, __set, __fmt)		\
static int __fops ## _open(struct inode *inode, struct file *file)	\
{									\
	__simple_attr_check_format(__fmt, 0ull);			\
	return simple_attr_open(inode, file, __get, __set, __fmt);	\
}									\
static const struct file_operations __fops = {				\
	.owner	 = THIS_MODULE,						\
	.open	 = __fops ## _open,					\
	.release = simple_attr_release,					\
	.read	 = debugfs_attr_read,					\
	.write	 = debugfs_attr_write,					\
	.llseek  = no_llseek,						\
}

struct dentry *debugfs_create_dir(const char *name, struct dentry *parent);

struct dentry *debugfs_create_file(const char *name, umode_t mode,
				   struct dentry *parent, void *data,
				   const struct file_operations *fops);

void debugfs_remove(struct dentry *dentry);
void debugfs_remove_recursive(struct dentry *dentry);           
*/

static struct dentry *d_folder = NULL;
static struct dentry *d_file = NULL;

static int data_access = 0;

/* read cat */
static int debugfs_get(void *data, u64 *val)
{
  u64 *t_val = val;
  *t_val = data_access;

  pr_info("fun=[%s] line=[%d] *t_val = %lld, data_access = %d\n", __func__, __LINE__, *t_val, data_access);
  return 0;
}

/* write echo */
static int debugfs_set(void *data, u64 val)
{
  data_access = val;
  pr_info("fun=[%s] line=[%d] val = %lld, data_access = %d\n", __func__, __LINE__, val, data_access);

  return 0;
}

DEFINE_DEBUGFS_ATTRIBUTE(debugfs_fops, debugfs_get, debugfs_set, "%lld\n");

static __init int debug_fs_init(void)
{
  pr_info("debug_fs! init\n");

  d_folder = debugfs_create_dir("debugfs_demo", NULL);

  if (d_folder)
  {
    d_file = debugfs_create_file("test", 0666, d_folder, NULL, &debugfs_fops);
  }

  return 0;
}

static __exit void debug_fs_exit(void)
{
  if (d_file)
  {
    debugfs_remove_recursive(d_file);
  }

  if (d_folder)
  {
    debugfs_remove_recursive(d_folder);
  }

  pr_info("debug_fs! exit\n");
}

module_init(debug_fs_init);
module_exit(debug_fs_exit);

MODULE_AUTHOR("wangfeng");
MODULE_DESCRIPTION("Linux hello module");
MODULE_LICENSE("Dual BSD/GPL");
