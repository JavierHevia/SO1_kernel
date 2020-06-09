#include <linux/proc_fs.h>
#include <linux/seq_file.h>
#include <asm/uaccess.h>
#include <linux/hugetlb.h>
#include <linux/sched/signal.h>
#include <linux/sched.h>
#include <linux/module.h>
#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/fs.h>

struct list_head *p;
struct task_struct  *proceso,ts,*tsk;


#define BUFSIZE     150

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("Lista de procesos...");
MODULE_AUTHOR("Andrés Ricardo Ismael Guzmán - Eduardo Javier Hevia Calderòn ");


static int escribir_archivo(struct seq_file * archivo, void *v) {
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
  
    for_each_process(proceso){    
        seq_printf(archivo, "---------------------------------\n");        
		seq_printf(archivo, " PID    : \t%d \n", proceso->pid); 
        seq_printf(archivo, " Nombre : \t%s \n", proceso->comm); 
        seq_printf(archivo, " Estado : \t%ld \n", proceso->state);
        list_for_each(p, &(proceso->children)){ 
            seq_printf(archivo, "    -------------------------------\n");  
            ts = *list_entry(p, struct task_struct, sibling);
            seq_printf(archivo, "     PID : \t%d \n", ts.pid);
            seq_printf(archivo, "     Nombre : \t%s \n", ts.comm);
            seq_printf(archivo, "     Estado : \t%ld \n", ts.state);
              
        }
        seq_printf(archivo, "\n---------------------------------\n\n"); 		 
	}

    
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
    proc_create("cpu_201010425_201313898", 0, NULL, &operaciones);
    printk(KERN_INFO "Andrés Ricardo Ismael Guzmán \nEduardo Javier Hevia Calderòn\n");
    return 0;
}
 
static void salir(void)
{
    remove_proc_entry("cpu_201010425_201313898", NULL);
    printk(KERN_INFO "Sistemas Operativos 1\n");
}
 
module_init(iniciar);
module_exit(salir); 
