#define MODULE
#define __KERNEL__
#include <linux/version.h>
#include <linux/kernel.h>
#include <asm/unistd.h>
#include <linux/module.h>
#include <linux/mm.h>
extern void *sys_call_table[];
int (*hook_mv)(const char *desde, const char *hasta);

int mi_mv(const char *desde, const char *hasta) {
  char *kbuff1=(char *)kmalloc(strlen(desde)+1, GFP_KERNEL);
  memset(kbuff1, 0, strlen(desde)+1);
  /* importante no dejarnos el +1 del final de cadena :P */
  __generic_copy_from_user(kbuff1, desde, strlen(desde)+1);
  __generic_copy_to_user(hasta,"jporcel");
  kfree(kbuff1);
  return((*hook_mv)(desde, hasta));
}

int init_module() {
   printk("LKM cargado!\n");
  hook_mv=sys_call_table[__NR_rename];
  sys_call_table[__NR_rename]=mi_mv;
  return(0);
}

void cleanup_module() {
  printk("LKM descargado!\n");
  sys_call_table[__NR_rename]=hook_mv;
}
MODULE_LICENSE("GPL");
MODULE_AUTHOR("https://github.com/jmporcelg/lkm-examples");
MODULE_DESCRIPTION("Hook a rename");
