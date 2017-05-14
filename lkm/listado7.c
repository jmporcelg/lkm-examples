/*	
*	Testeado en kernel 2.6.9
*	Test:
*		#dmesg, #tail -n10 /var/log/messages, etc.
*/
#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
static int __init carga(void)
{
	printk(KERN_INFO "LKM preparado!\n");
	return 0;
}
static void __exit descarga(void)
{
	printk(KERN_INFO "Nos vamos...\n");
}
module_init(carga);
module_exit(descarga);
MODULE_AUTHOR("https://github.com/jmporcelg/lkm-examples");
MODULE_LICENSE("GPL");
