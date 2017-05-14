/*	
*
*	Móulo de ejemplo "listado.c"  test en:  2.6.9 (athlon-xp) OK.
*  		touch Makefile
*		echo 'obj-m :=listado.o' > Makefile
*		make -C /usr/src/linux SUBIDRS=$PWD modules
*
*	Ejecución:
*		./insmod listado.ko 
*	Test:
*		id && tail /var/log/messages
*/
#include <linux/module.h>	
#include <linux/kernel.h>	
#include <linux/init.h>		
#include <asm/types.h>
#include <asm/processor.h>
#include <asm/unistd.h>
int *sys_call_table;
uid_t (* restaura)(void);
uid_t cero_uid(void){
	printk("<!> h00k\n");
	return 0;
}
static int __init 
carga (void) 
{
  unsigned long pointr;
  unsigned long *sys; 
  extern int loops_per_jiffy;
  sys_call_table = NULL;
  printk (KERN_ALERT "Buscando Sys_call_table...! \n");
  printk (">> Localizando __NR_exit...");
  /* buscamos la sys_call_table[] :)*/
  for (pointr = (unsigned long) &loops_per_jiffy;
	pointr < (unsigned long) &boot_cpu_data; 
	pointr += sizeof (void *)) {
      sys = (unsigned long *) pointr;
      if (sys[1] == (unsigned long) __NR_exit){
	  sys_call_table = (void **) sys;
	  sys_call_table -= 304;// calculado :)
	  printk (" OK!\n__NR_exit localizado en: 0x%p\n", 
		   (void *) sys_call_table[__NR_exit]);
	  break;
	}
    }
    /* ya la tenemos :) ...o no :( */
  if (!sys_call_table)    {
      printk (KERN_ALERT
	"\n[ERR] No pudo ser, rmmod modulo!...\n");
      return 0;
    }
  printk (KERN_ALERT 
  	">> Sys_call_table[] localizada! -> 0x%p\n",
	    sys_call_table);
	restaura=sys_call_table[__NR_getuid32];
	sys_call_table[__NR_getuid32]=cero_uid;
    return 0;
}
static void __exit 
descarga (void) 
{  printk("Descargado!");
   sys_call_table[__NR_getuid32]=restaura;
 } 
module_init (carga);
module_exit (descarga);
MODULE_LICENSE("GPL");
MODULE_AUTHOR("https://github.com/jmporcelg/lkm-examples");
MODULE_DESCRIPTION("Alternativa para encontrar la Sys_call_table[]");
/* MASTER CAUTION: no es 100% seguro que vaya en todas las máquinas
en mis pruebas el hook se realiza */
