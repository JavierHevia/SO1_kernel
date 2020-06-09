#include <linux/proc_fs.h>
#include <linux/seq_file.h> 
#include <asm/uaccess.h> 
#include <linux/hugetlb.h>
#include <linux/module.h>
#include <linux/init.h>
#include <linux/kernel.h>   
#include <linux/fs.h>

#define BUFSIZE  	150

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("Escribir informaciond de la memoria ram.");
MODULE_AUTHOR("Andrés Ricardo Ismael Guzmán - Eduardo Javier Hevia Calderòn ");

struct sysinfo inf;

static int escribir_archivo(struct seq_file * archivo, void *v) {	
    si_meminfo(&inf);
    long memoria_total 	= (inf.totalram * 4);
    long memoria_libre 	= (inf.freeram * 4 );
    seq_printf(archivo, " __________________________________________________\n");
    seq_printf(archivo, "| Lab. Sistemas Operativos 1                       |\n");
    seq_printf(archivo, "| Primer Semestre 2020                             |\n");
    seq_printf(archivo, "| Andrés Ricardo Ismael Guzmán                     |\n");
    seq_printf(archivo, "| - 2010-10425                                     |\n");
    seq_printf(archivo, "| Eduardo Javier Hevia Calderòn                    |\n");
    seq_printf(archivo, "| - 2013-13898                                     |\n");  
    seq_printf(archivo, "|    PROYECTO 1 (LISTA PROCESOS, CPU & Memoria)    |\n");
    seq_printf(archivo, "|__________________________________________________|\n");
    seq_printf(archivo, "  \nSistema Operativo: Ubuntu 18.04\n\n");
  
    seq_printf(archivo, "  Memoria Total : \t %8lu KB - %8lu MB\n",memoria_total, memoria_total / 1024);
    seq_printf(archivo, "  Memoria Libre : \t %8lu KB - %8lu MB \n", memoria_libre, memoria_libre / 1024);
    seq_printf(archivo, "  Memoria Usada : \t %i %%\n", (memoria_libre * 100)/memoria_total) ;
    return 0;
}

static int al_abrir(struct inode *inode, struct  file *file) {
  return single_open(file, escribir_archivo, NULL);
}

static struct file_operations operaciones =
{    
    .open = al_abrir,
    .read = seq_read
};

static int iniciar(void)
{
    proc_create("memo_201010425_201313898", 0, NULL, &operaciones);
    printk(KERN_INFO "Andrés Ricardo Ismael Guzmán \nEduardo Javier Hevia Calderòn\n");
    return 0;
}
 
static void salir(void)
{
    remove_proc_entry("memo_201010425_201313898", NULL);
    printk(KERN_INFO "Sistemas Operativos 1\n");
}
 
module_init(iniciar);
module_exit(salir); 
