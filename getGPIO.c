/*
* Driver to request iomem-ed gpio location 
*/

#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/ioport.h>
#include <linux/of.h>
#include <linux/gpio.h>

#define AUTHOR	"ZeekHuge"
#define DESC 	"Requests the iomem-ed gpio location"

static int gpioWasClaimed = 1;
static int err =0 ;



static int __init gpio_module(void)
{
	printk(KERN_ALERT "requesting");
	err = gpio_request_one(53,GPIOF_INIT_HIGH,"zeek_gpio");

	if ( err > 0)
	{
		gpioWasClaimed=0;
		printk(KERN_ALERT "gpio busy");
		return 0;
	}

	printk(KERN_ALERT "gpio claimed");
	return 0;

}

static void __exit cleanup_gpio(void)
{
	printk(KERN_ALERT "cleaning");
	
	if (gpioWasClaimed){
		gpio_free(53);
	}
	
	printk(KERN_ALERT "Leaving");
}

module_init(gpio_module);
module_exit(cleanup_gpio);
MODULE_LICENSE("GPL");
MODULE_AUTHOR(AUTHOR);
MODULE_DESCRIPTION(DESC);
MODULE_SUPPORTED_DEVICE("No device");