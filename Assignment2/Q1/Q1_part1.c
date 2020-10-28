/* Name: Yatharth Taneja  
   Roll_Number: 2019346 */
#include<stdio.h>
#include<sys/wait.h>
#include<stdlib.h>
#include<unistd.h>
int global=10;
int main(){
__pid_t pid;
pid=fork();

if(pid<0){
    fprintf(stderr," Fork failed");
    return 1;
}
else if(pid==0){
//  child process

   while(global>-90){
   global-=1;
   printf("Child process %d\n",global);
   }
   exit(0);
}
else
{
   while(global<100){
   global+=1;
   printf("parent process %d\n",global);
   }
}

// waitpid(pid,NULL,0);

return(0);
}