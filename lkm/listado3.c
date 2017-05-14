/*	
*  		gcc -Wall -O3 -c - I /usr/src/linux/include modulo.c
*	Ejecución:
*		./insmod modulo.o <parametros>
*	Test:
*		#dmesg, #tail -n10 /var/log/messages, etc.
*/
#define MODULE
#define __KERNEL__ 
#include <asm/unistd.h>   
#include <linux/version.h>
#include <linux/kernel.h>
#include <linux/module.h>
extern void *sys_call_table[];
long (* hook_chmod)(const char *fichero);

long mi_chmod(const char *fichero){
	printk("[HxC LKM] CHMOD inhibido!!\n");
	return 0;


}
int init_module() {
	printk("LKM Listo y funcionando.\n");
	hook_chmod=sys_call_table[__NR_chmod];
	sys_call_table[__NR_chmod]=mi_chmod;
	printk("@SYS_chmod: 0x%p\n",hook_chmod);
	return 0;

}

int cleanup_module(){
	printk("Descargando...\n");
	sys_call_table[__NR_chmod]=(void *)hook_chmod;

}
MODULE_LICENSE("GPL");
MODULE_AUTHOR("https://github.com/jmporcelg/lkm-examples");
MODULE_DESCRIPTION("Ejemplo de hook que anula chmod");
