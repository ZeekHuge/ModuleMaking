/*
 * Hello.c - An introductory loadable kernel module.
 *
 *  Copyright (C) 2016 ZeekHuge
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 */

#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/of.h>
#include <linux/of_device.h>

static int parm_int = 1;
static short parm_short = 2;
static char* parm_string = "foo_string";

module_param(parm_int,int,0000);
MODULE_PARM_DESC(parm_int, "An intger");
module_param(parm_short, short,0000);
MODULE_PARM_DESC(parm_short, "A short intger");
module_param(parm_string,charp,0000);
MODULE_PARM_DESC(parm_string, "A string");

static int __init init_hello(void)
{

	printk(KERN_DEBUG "Hello world!\n"); 
	printk(KERN_DEBUG "Parameter 1, parm_int = %d\n",parm_int);
	printk(KERN_DEBUG "Parameter 2, parm_short = %hd\n",parm_short);
	printk(KERN_DEBUG "Parameter 3, parm_string = %s\n",parm_string);

	return 0; 
}
module_init(init_hello);

static void  __exit exit_hello(void)
{
	printk(KERN_ALERT "Goodbye world.\n");
}
module_exit(exit_hello);

MODULE_LICENSE("GPL v2");
MODULE_AUTHOR("ZeekHuge");