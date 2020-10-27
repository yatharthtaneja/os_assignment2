#include<linux/kernel.h>
#include<linux/syscalls.h>
#include<linux/types.h>
#include<linux/sched.h>
#include<linux/errno.h>
#include <linux/unistd.h>
#include<linux/file.h>
#include<linux/fs.h>
#include<asm/uaccess.h>
#include<linux/module.h>
#include<linux/fcntl.h>
#include<linux/init.h>
#include<linux/string.h>
SYSCALL_DEFINE2(sh_task_info,pid_t,inp_pid,char*,file_path)
{
	int errno=0;
	char data[5000];

	struct task_struct *task_info;
	task_info=find_task_by_vpid(inp_pid);
	if (task_info==NULL)
	{
		printk("PID not found \n");
		errno=1;
		return errno;
		/* code */
	}
			snprintf(data,5000,"Process: %s\n \
       PID_Number: %ld\n \
       Process State: %ld\n \
       Priority: %ld\n \
       RT_Priority: %ld\n \
       Static Priority: %ld\n \
       Normal Priority: %ld\n \
       TGID_Number: %ld\n \
		CPU: %d\n \
		Blocked:%d\n\
		Real Blocked:%d\n\
		Flags:%d\n\
		Exit State:%d\n\
		Exit Code:%d\n\
		Exit Signal:%d\n\
		Parent Death Signal:%d\n"
		,
       task_info->comm, 
       (int)task_info->pid, 
       (long)task_info->state, 
       (long)task_info->prio, 
       (long)task_info->rt_priority, 
       (long)task_info->static_prio, 
       (long)task_info->normal_prio,
       (long)task_info->tgid,
       (int)task_info->on_cpu,
		task_info->blocked,
		task_info->real_blocked,
		(int)task_info->flags,
		(int)task_info->exit_state,
		(int)task_info->exit_code,
		(int)task_info->exit_signal,
		(int)task_info->pdeath_signal);

	printk(KERN_ALERT"%s",data);
	struct file *fptr;
	char buf[256];

	long copied = strncpy_from_user(buf,file_path, sizeof(buf));
	int fd;
	mm_segment_t old_fs=get_fs();
	set_fs(KERNEL_DS);
	if(copied<0 || copied == sizeof(buf)){
		errno= -EFAULT;
		return errno;
	}
	fptr=filp_open(buf, O_WRONLY|O_CREAT, 0644);
		if(IS_ERR(fptr)){
		printk(KERN_ALERT" Cannot Open File");
		set_fs(old_fs);
		return 1;
	}

		fd=kernel_write(fptr,data,strlen(data)+1,0);
		fput(fptr);
		filp_close(fptr,NULL);
		set_fs(old_fs);
		if(fd<0){
			printk(" Cannot Write to file %d",fd);
			errno=1;
		}

return errno;
}
