#include <sys/ioctl.h>
#include <linux/types.h>
#include <fcntl.h>
#include <xenctrl.h>
#include <xen/sys/privcmd.h>
#include <errno.h>
#include <xen/xen.h>
#include <sys/mman.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#define SHIFT 5
#define MASK 0x1f
int main(void){
	int fd, covFd;
	int ret;
	char* fn;  
	long long int cover[4690] = {0};
	privcmd_hypercall_t set_cover={
			__HYPERVISOR_set_cov_array,
			{(long long int)&cover,0,0,0,0}
	}; 
	fd = open("/proc/xen/privcmd",O_RDWR);
	if (fd<0){
			perror("cannot open privcmd");
			return 0;
	}
	ret = ioctl(fd,IOCTL_PRIVCMD_HYPERCALL, &set_cover); 
	if (ret <  0)
	{
		printf("-------------failed!\n\n");
		return 0;
	}
	
	fn = "/dev/cov";
//	for (int i = 0; i < 4690; ++i)
//	{
//		if (cover[i >> SHIFT] & (1 << (i & MASK)))
//		printf("%lld \t", cover[i]);
//	}
	
	covFd= open(fn, O_RDWR);
	if (covFd == -1) {
		creat(fn, 0777);
		covFd = open(fn, O_RDWR);
	}
//	printf("\n\n %d \n\n", covFd);
//	printf("\n\n %ld \n\n", sizeof(cover));
	write(covFd, cover, sizeof(cover));
	close(covFd);
	close(fd);
	return 0;

}




