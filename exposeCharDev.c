#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/fs.h>
#include <linux/uaccess.h>
#include <linux/device.h>

/**********************************/
/**********************************/

#define DEVICE_NAME "theCharDev"
#define CLASS_NAME "myClass"

#define AUTHOR	"ZeekHuge"
#define DESC 	"Exposes a character device /dev/theCharDev"


/**********************************/
/* These functions will be called when operations are performed on the device file */
/**********************************/

static int fileBeingReleased (struct inode *, struct file *);
static int fileBeingOpend (struct inode *, struct file *);
static ssize_t fileBeingRead (struct file *, char __user *, size_t, loff_t *);
static ssize_t fileBeingWritten (struct file *, const char __user *, size_t, loff_t *);

/**********************************/
/**********************************/


/**********************************/
/* Global data */
/**********************************/

static int majorNumber;
static int isOpened = 0;
static struct class* myClass = NULL;
static struct device* myDevice = NULL;


/**********************************/
/* The structure the define operations on file (usually called fops) */
/**********************************/

static struct file_operations fops =
{
	.read = fileBeingRead,
	.write = fileBeingWritten,
	.open = fileBeingOpend,
	.release = fileBeingReleased
};

/**********************************/
/**********************************/


/**********************************/
/* Defination of fops functions */
/**********************************/

static int fileBeingReleased (struct inode *node, struct file *fl){

	module_put(THIS_MODULE);
	isOpened = 0;
	printk(KERN_ALERT "File released\n");
	return 0;
}

/**********************************/
/**********************************/

static int fileBeingOpend (struct inode *node, struct file *fl){

	if (!isOpened){
		try_module_get(THIS_MODULE);
		isOpened = 1;
		printk(KERN_ALERT "File openend\n");
	}else{
		printk(KERN_ALERT "Tried to open already openend file\n");
	}
	return 0;
}

/**********************************/
/**********************************/

static ssize_t fileBeingRead (struct file *fl, char __user *bffr, size_t len, loff_t *off){
	printk(KERN_ALERT "File read operation");
	return 0;
}

/**********************************/
/**********************************/

static ssize_t fileBeingWritten (struct file *fl,const char __usr *bffr, size_t len, loff_t * off){
	printk(KERN_ALERT "File write operation");
	return len;
}

/**********************************/
/**********************************/




/**********************************/
/**********************************/

static int __init exposeCharDev_module(void){
	
	printk(KERN_INFO "exposeCharDev loaded\n");

	majorNumber = register_chrdev(0, DEVICE_NAME, &fops);

	if (majorNumber < 0){
		printk(KERN_ALERT "Registration failed - %d",majorNumber);
		return majorNumber;
	}

	myClass = class_create(THIS_MODULE, CLASS_NAME);
	if (IS_ERR(myClass)){
      unregister_chrdev(majorNumber, DEVICE_NAME);
      printk(KERN_ALERT "Failed to create the device\n");
      return PTR_ERR(myClass);
   	}

   	myDevice = device_create(myClass, NULL, MKDEV(majorNumber, 0), NULL, DEVICE_NAME);
	if (IS_ERR(myDevice)){
      class_destroy(myClass); 
      unregister_chrdev(majorNumber, DEVICE_NAME);
      printk(KERN_ALERT "Failed to create the device\n");
      return PTR_ERR(myDevice);
   	}


   	printk(KERN_ALERT "Registration done - %d",majorNumber);

	return 0;
}


/**********************************/
/**********************************/

static void __exit cleanup_exposeCharDev(void){

	printk(KERN_INFO "exposeCharDev rmmod-ed\n");
	unregister_chrdev(majorNumber, DEVICE_NAME);
	// if (err < 0){
	// 	printk(KERN_ALERT "Couldnt unregister");
	// }

}

/**********************************/
/**********************************/


module_init(exposeCharDev_module);
module_exit(cleanup_exposeCharDev);
MODULE_LICENSE("GPL"); /* Not sure what GPL license is about */
MODULE_AUTHOR(AUTHOR);
MODULE_DESCRIPTION(DESC);
MODULE_SUPPORTED_DEVICE("No device");
