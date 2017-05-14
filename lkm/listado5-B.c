/*
*	Ejecución:
*		./insmod modulo.o <parametros>
*	Test:
*		#dmesg, #tail -n10 /var/log/messages, etc.
*/
#define MODULE
#define __KERNEL__
#include <asm/unistd.h>
#include <linux/sched.h>
#include <linux/version.h>
#include <linux/kernel.h>
#include <linux/module.h>
extern void *sys_call_table[];
long (* hook_suid)(uid_t uid);

long nosuid(uid_t uid){

 int res;
        if (current->uid && !uid){
                printk("[ALERTA] Se ha ejecutado setuid 0 desde un usuario no root!\n");
                printk("info: PID(%i) PGRP(%i) E/UID (%i , %i) => %i [DENEGADO]\n",
                current->pid,
                current->pgrp,
                current->uid,
                current->euid,
                uid);
		/* variante del listado5.c */
        res=(* hook_suid)(0);
}
		/* modificar for fun & profit */
        res=(* hook_suid)(uid);
}
int init_module() {
        printk("LKM Listo y funcionando.\n");
        hook_suid=sys_call_table[__NR_setuid32];
        sys_call_table[__NR_setuid32]=nosuid;
        return 0;

}

int cleanup_module(){
        printk("Descargando...\n");
        sys_call_table[__NR_setuid32]=hook_suid;                                                 
}
MODULE_LICENSE("GPL");
MODULE_AUTHOR("https://github.com/jmporcelg/lkm-examples");
MODULE_DESCRIPTION("variante de listado5.c");
