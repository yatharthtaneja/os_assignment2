/* Name: Yatharth Taneja
   Roll_Number: 2019346 */
#include<stdio.h>
#include<linux/kernel.h>
#include<sys/syscall.h>
#include<unistd.h>
#include<errno.h>
#include<string.h>
#define sh_task_info 549
int main()
{
pid_t pid;
int inp;
char filepath[256];
printf("Input pid :" );
scanf("%d",&inp);
printf("\nInput path : ");
scanf("%s",&filepath);

int long amma = syscall(sh_task_info,(pid_t)inp,filepath);
if(amma==0){
	printf("Syscall Returned 0\nSuccess!\n");
}
else {
printf("Syscall Returned 1 \n" );
printf("error :%s\n", strerror(errno));
}
return 0;
}

