#include <linux/kernel.h>
#include <linux/sched.h>
#include <linux/module.h>
#include <linux/init.h>
#include <linux/moduleparam.h>
#include <linux/sched/signal.h>

static unsigned int pid;
module_param(pid, uint, 0644);

static int module2_init(void)
{
    struct task_struct *p;//p为游标
    struct task_struct *parent;
    struct task_struct *target;
    struct list_head *list;
    for_each_process(p)
    {
        if(p->pid == pid)  
        break;//找到目标进程
    }
    target = p;//保留目标进程
    p=p->parent;//此时p指向目标进程的父进程
    printk(KERN_ALERT"This is parent:\n");
    printk(KERN_ALERT"程序名\t\tPID号\t进程状态  优先级\n");
    printk(KERN_ALERT"%-10s\t%5d\t%ld\t   %d\n", p->comm, p->pid, p->state, p->prio);
    parent=p;//保留parent指针，便于循环sibling的退出
    p=list_entry(parent->children.next, struct task_struct, sibling/*children*/);//p指向目标进程的第一个sibling
    /*
    *注意：parent的children.next指向第一个孩子进程的sibling成员，而非children成员
    */
    printk(KERN_ALERT"This is sibling:");
    printk(KERN_ALERT"程序名\t\tPID号\t进程状态  优先级\n");
    list_for_each(list,&parent->children)
    /*
    *注意：孩子进程链表中的最后一个孩子进程sibling->next指向父进程的children成员，并非第一个孩子的sibling成员
    */ 
    { 
        p=list_entry(list,struct task_struct,sibling);
	if(p != target)
        printk(KERN_ALERT"%-10s\t%5d\t%ld\t   %d\n", p->comm, p->pid, p->state, p->prio);
    }
    p=list_entry(target->children.next, struct task_struct, sibling);//找到第一个儿子
    printk(KERN_ALERT"This is children:\n");
    printk(KERN_ALERT"程序名\t\tPID号\t进程状态  优先级\n");
    list_for_each(list,&target->children) 
    { 
        p=list_entry(list,struct task_struct,sibling);
        printk(KERN_ALERT"%-10s\t%5d\t%ld\t   %d\n", p->comm, p->pid, p->state, p->prio);
    }   
    return 0;
}

static void module2_exit(void)
{
    printk(KERN_ALERT"Module2 has been exited!\n");
}

module_init(module2_init);
module_exit(module2_exit);
MODULE_LICENSE("GPL");

