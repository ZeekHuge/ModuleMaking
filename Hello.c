/*
* Hello world module
*/
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/of.h>
#include <linux/of_device.h>


#define AUTHOR	"ZeekHuge"
#define DESC 	"Prints hello in dmesg"



static int arg_int = 1;
static short arg_short = 2;
static char* arg_string = "foo";

module_param(arg_int,int,0000);
MODULE_PARM_DESC(arg_int, "An intger");
module_param(arg_short, short,0000);
MODULE_PARM_DESC(arg_short, "A short intger");
module_param(arg_string,charp,0000);
MODULE_PARM_DESC(arg_string, "A string argument");


static int hello_data __initdata = 1;


static int __init hello_module(void)
{

	printk(KERN_ALERT "Hello world Module %d .\n",hello_data); /* to print to the logs */
	printk(KERN_ALERT "Argument 1, an  integer %d .\n",arg_int);
	printk(KERN_ALERT "Argument 2, a short %hd .\n",arg_short);
	printk(KERN_ALERT "Argument 3, a string %s .\n",arg_string);

	return 0; /* To mark loading succes */
}

static void  __exit cleanup_hello(void)
{
	printk(KERN_ALERT "The string was - %s.\n",arg_string);
	printk(KERN_ALERT "Goodbye world.\n");
}

module_init(hello_module);
module_exit(cleanup_hello);
MODULE_LICENSE("GPL");
MODULE_AUTHOR(AUTHOR);
MODULE_DESCRIPTION(DESC);
MODULE_SUPPORTED_DEVICE("No device");