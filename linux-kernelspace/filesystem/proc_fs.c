#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/module.h>
#include <linux/proc_fs.h>
#include <linux/seq_file.h>
#include <linux/uaccess.h>

/*
创建目录：
extern struct proc_dir_entry *proc_mkdir(const char *, struct proc_dir_entry *);
    -- > proc_mkdir_data(name, 0, parent, NULL);
extern struct proc_dir_entry *proc_mkdir_mode(const char *, umode_t, struct proc_dir_entry *);
创建proc文件
struct proc_dir_entry *proc_create(const char *name, umode_t mode, struct proc_dir_entry *parent, const struct file_operations *proc_fops);
要从 /proc 中删除一个文件，可以使用 remove_proc_entry 函数。要使用这个函数，我们需要提供文件名字符串，以及这个文件在 /proc 文件系统中的位置（parent）。
extern void remove_proc_entry(const char *, struct proc_dir_entry *);
删除目录
extern void proc_remove(struct proc_dir_entry *);

*/

static struct proc_dir_entry *proc_dir_entry = NULL;

#define PROC_DIR_NAME "proc_demo"
#define PROC_NAME "op"

//static umode_t mode = S_IRWXU|S_IRWXG|S_IRWXO;
static umode_t mode = 0777;//S_IRUSR|S_IWUSR;

static int mt_need_uart_console = 0;

static int mt_printk_ctrl_show(struct seq_file *m, void *v)
{
    if (m) {
        seq_printf(m, "mt_need_uart_console = %d\n", mt_need_uart_console);
    }

	return 0;
}

static int proc_open(struct inode *inode, struct file *file)
{
    return single_open(file, mt_printk_ctrl_show, inode->i_private);
}


static ssize_t proc_write(struct file *filp, const char *ubuf, size_t cnt, loff_t *data)
{
	char buf[64];
	long val;
	int ret;

	if (cnt >= sizeof(buf))
		return -EINVAL;

	if (copy_from_user(&buf, ubuf, cnt))
		return -EFAULT;

	buf[cnt] = 0;

	ret = kstrtoul(buf, 10, (unsigned long *)&val);

	if (ret < 0)
		return ret;

	switch (val) {
	case 0:
		mt_need_uart_console = 0;
		//mt_disable_uart();
		break;
	case 1:
		mt_need_uart_console = 1;
		//mt_enable_uart();
		break;
	
	default:
		break;
	}
	return cnt;
}

static const struct file_operations proc_operations = {
    .owner          = THIS_MODULE,
    .open           = proc_open,
	.write          = proc_write, 
    .read           = seq_read,
    .llseek         = seq_lseek,
    .release        = single_release,
};

static __init int proc_fs_init(void)
{

    //proc_dir_entry = proc_mkdir(PROC_DIR_NAME, NULL); //NULL表示是在/proc/目录下面建立目录
    proc_dir_entry = proc_mkdir_mode(PROC_DIR_NAME, mode, NULL);
    if (!proc_dir_entry) {
        pr_err("proc_dir_entry == NULL");
        return -ENOMEM;
    }

    proc_create(PROC_NAME, mode, proc_dir_entry, &proc_operations);

    pr_info("%s %d successful", __func__,__LINE__);

    return 0;
}

static __exit void proc_fs_exit(void)
{
    
    if (!proc_dir_entry) {
        proc_remove(proc_dir_entry);
        proc_dir_entry = NULL;
        pr_info("proc_dir_entry remove ok");
    }
    
    pr_info("%s %d successful", __func__,__LINE__);
}
 

module_init(proc_fs_init);
module_exit(proc_fs_exit);

MODULE_AUTHOR("wangfeng");
MODULE_DESCRIPTION("Linux hello module");
MODULE_LICENSE("Dual BSD/GPL");


