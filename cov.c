#include <sys/ioctl.h>
#include <linux/types.h>
#include <fcntl.h>
#include <xenctrl.h>
#include <xen/sys/privcmd.h>
#include <errno.h>
#include <xen/xen.h>



int main(void){
	int fd, covFd;
	int ret;
	char* fn;  
	int cover[100000] = {0};

	privcmd_hypercall_t set_cover={
			__HYPERVISOR_set_cov_array,
			{(long long int)&cover,0,0,0,0}
	}; 
//	privcmd_hypercall_t unset_cover={
//			__HYPERVISOR_unset_cov_array,
//			{0,0,0,0,0}
//	};
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
	for (int i = 0; i < 10000; ++i)
	{
		if (cover[i] == '1')
			printf("yes \t");
	}
	covFd= open(fn, O_RDWR);
	if (covFd == -1) {
		creat(fn, 0777);
		covFd = open(fn, O_RDWR);
	}
	write(covFd, cover, sizeof(cover));
	close(covFd);
//	ret=ioctl(fd,IOCTL_PRIVCMD_HYPERCALL, &unset_cover); 
//	if (ret < 0 )
//		perror("no!");			
	close(fd);
    return 0;

}




