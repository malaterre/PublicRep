/* http://www.linuxchix.org/content/courses/kernel_hacking/lesson8 */
#include <linux/init.h>
#include <linux/module.h>
MODULE_LICENSE("GPL");

static int hello_init(void)
{
 //pr_err("My module worked!\n");
 printk(KERN_ALERT "My module worked!\n");
        return 0;
}

static void hello_exit(void)
{
// pr_err("Unloading my module.\n");
 printk(KERN_ALERT "My module unloaded!\n");
        return;
}

module_init(hello_init);
module_exit(hello_exit);
