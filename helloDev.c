#include <linux/module.h>
#include <linux/param.h>
#include <linux/moduleparam.h>
#include <linux/cdev.h>
#include <linux/fs.h>
#include <linux/wait.h>
#include <linux/poll.h>
#include <linux/sched.h>
#include <linux/slab.h>

#define BUFFER_MAX (10)
#define OK (0)
#define ERROR (-1)

struct cdev *gDev = NULL;
struct file_operations *gFileOps = NULL;
dev_t devNum = -1;
unsigned int subDevNum = 1;
int reg_major = 232;
int reg_minor = 0;
char *buffer;
int flag = 0;

static int hello_open(struct inode *p, struct file *f)
{
    printk(KERN_INFO "hello open\n");
    return 0;
}

ssize_t hello_write(struct file *f, const char __user *u, size_t s, loff_t *l)
{
    printk(KERN_INFO "hello write\n");
/*     if (u != NULL){
        printk(KERN_INFO "%s\n", u);
        printk(KERN_INFO "write %ld bytes\n", strlen(u));
    } */
    return 0;
}

ssize_t hello_read(struct file *f, char __user *u, size_t s, loff_t *l)
{
    printk(KERN_INFO "hello read\n");

    return 0;
}

int hello_init(void)
{
    // 生成设备号
    devNum = MKDEV(reg_major, reg_minor);
    // 注册字符驱动，避免其他驱动占用设备号
    if (OK == register_chrdev_region(devNum, subDevNum, "hello world device"))
    {
        printk(KERN_INFO "register_chrdev_region ok\n");
    }
    else
    {
        printk(KERN_INFO "register_chrdev_region error \n");
        return ERROR;
    }

    printk(KERN_INFO "hello driver init\n");
    gDev = kzalloc(sizeof(struct cdev), GFP_KERNEL);
    // 绑定驱动file ops
    gFileOps = kzalloc(sizeof(struct file_operations), GFP_KERNEL);
    gFileOps->open = hello_open;
    gFileOps->write = hello_write;
    gFileOps->read = hello_read;
    gFileOps->owner = THIS_MODULE;

    // 初始化字符驱动
    cdev_init(gDev, gFileOps);
    cdev_add(gDev, devNum, 1);
    return 0;
}

void __exit hello_exit(void)
{
    cdev_del(gDev);
    unregister_chrdev_region(devNum, subDevNum);
    kfree(gDev);
    kfree(gFileOps);
    printk(KERN_INFO "hello driver exit\n");
    return;
}

module_init(hello_init);
module_exit(hello_exit);
MODULE_LICENSE("GPL");