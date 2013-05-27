/* http://www.linuxchix.org/content/courses/kernel_hacking/lesson8 */
#include <linux/module.h>
#include <linux/init.h>

static int __init hello_init(void)
{
 pr_err("My module worked!\n");
        return 0;
}

static void __exit hello_exit(void)
{
 pr_err("Unloading my module.\n");
        return;
}

module_init(hello_init);
module_exit(hello_exit);

MODULE_LICENSE("GPL");
