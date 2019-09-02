#include<linux/init.h>
#include<linux/module.h>
#include<linux/fs.h>
#include<linux/cdev.h>
#include<linux/uaccess.h>

#define MAJ 200
#define MIN 0
#define CHAR_DRV_NAME "Char_drv_interface"

dev_t deviceid=MKDEV(MAJ,MIN);
static struct cdev* chdrv_interface_cdev;
char pribuf[20];


int chdrv_open(struct inode *chdrv_inode, struct file * chdrv_file)
{
	pr_info("File has been opened\n");
	return 0;
}

ssize_t chdrv_write(struct file * chdrv_file, const char* buf, size_t size, loff_t* offset)
{
	
	pr_info("chdrv_write called");
	
	copy_from_user(pribuf,buf,size);

	pr_info("value written on private buffer is %s",pribuf);


	return size;
}




ssize_t chdrv_read(struct file * chdrv_file, char* buf, size_t size, loff_t * offset)
{
	pr_info("chdrv_read called");

	copy_to_user(buf,pribuf,sizeof(pribuf));

	return 0;
}

int chdrv_close(struct inode *chdrv_inode, struct file * chdrv_file)
{
	pr_info("File closed\n");
	return 0;
}

struct file_operations fops ={
	.owner=THIS_MODULE,
	.open=chdrv_open,
	.write=chdrv_write,
	.read=chdrv_read,
	.release=chdrv_close
};

int init_module(void)
{

	pr_info("Hello Kernel space\n");

	register_chrdev_region(deviceid,1,CHAR_DRV_NAME);
	
	// Allocate the cdev instance ---struct cdev *cdev_alloc(void);
	chdrv_interface_cdev=cdev_alloc();

	//initialize the cdev with fops object-----void cdev_init(struct cdev *, const struct file_operations *);
	cdev_init(chdrv_interface_cdev, &fops);

	//Register cdev with vfs (devtmpfs)
	cdev_add(chdrv_interface_cdev, deviceid, 1);

	return 0;
}


void cleanup_module(void)
{
	//Remove cdev and release
	cdev_del(chdrv_interface_cdev);

	// frre the device id
	unregister_chrdev_region(deviceid, 1);
	pr_info("By Kernel\n");
	
}

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Harshal");
