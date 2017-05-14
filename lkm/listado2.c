#define MODULE
#define __KERNEL__
#include <linux/version.h>
#include <linux/kernel.h>
#include <linux/module.h>
MODULE_PARM(parm_entero, "i");
int parm_entero;


int init_module() {
  printk("LKM cargado!\n");
  printk("parm_entero vale:%i\n", parm_entero);
  return 0;
}

void cleanup_module() {
  printk("LKM descargado!\n");
}

MODULE_LICENSE("GPL");
MODULE_AUTHOR("https://github.com/jmporcelg/lkm-examples");
