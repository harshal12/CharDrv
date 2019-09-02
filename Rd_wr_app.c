#include<stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int main()
{
	int ret;
	char buf[20];
	int fd=open("/dev/Mydev",O_RDWR);
	if(fd<0)
	{
		perror("Failed to open the file");
	}

	printf("Enter the value you want to send to kernel\n");
	scanf("%[^\n]s",buf);
	if(write(fd,buf,sizeof(buf)))
	{
		perror("Problem in writing:");
	}
	


	if(read(fd,buf,sizeof(buf))<0)
	{
	perror("Prroblem in reading");
	}
	printf("read successfully, and the read value is %s",buf);

	close(fd);
	return 0;
}
