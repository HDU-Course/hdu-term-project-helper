/*必须头文件*/
#include<linux/init.h> 
#include<linux/module.h>
#include<linux/kernel.h>
 

//初始化
static int  hello_init(void)
{
 	//日志级别
        printk(KERN_ALERT"hello,word\n");
 	//返回0
        return 0;
 
}

//退出，注销和释放资源
static void  hello_exit(void)
 
{
 
        printk(KERN_ALERT"goodbye\n");
 
}

//加载模块时调用 
module_init(hello_init);
//卸载模块时调用
module_exit(hello_exit);
/*模块许可申明*/
MODULE_LICENSE("GPL");

