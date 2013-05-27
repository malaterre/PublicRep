/* http://www.linuxchix.org/content/courses/kernel_hacking/lesson8 */
#include <linux/module.h>
#include <linux/init.h>

static int __init mymodule_init(void)
{
 pr_err("My module worked!\n");
        return 0;
}

static void __exit mymodule_exit(void)
{
 pr_err("Unloading my module.\n");
        return;
}

module_init(mymodule_init);
module_exit(mymodule_exit);

MODULE_LICENSE("GPL");
