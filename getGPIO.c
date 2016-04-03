
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/ioport.h>
#include <linux/of.h>
#include <linux/gpio.h>


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
module_init(gpio_module);

static void __exit cleanup_gpio(void)
{
	printk(KERN_ALERT "cleaning");
	
	if (gpioWasClaimed){
		gpio_free(53);
	}
	
	printk(KERN_ALERT "Leaving");
}
module_exit(cleanup_gpio);



MODULE_LICENSE("GPL v2");
MODULE_AUTHOR("ZeekHuge");
MODULE_DESCRIPTION("");