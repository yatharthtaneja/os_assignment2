/* Name: Yatharth Taneja
   Roll_Number: 2019346 */

#include<stdio.h>
#include<pthread.h>
#include<stdlib.h>
int global=10;
void* func(void* arg) 
{ 
    pthread_detach(pthread_self()); 
  
     while (global>-90)
     {

      global-=1;
      printf("Child process %d\n",global);
     }
    pthread_exit(NULL); 
} 
int main(){
pthread_t ptid;
pthread_create(&ptid,NULL,&func,NULL);
// pthread_join(ptid,NULL);

   while(global<100){
      global+=1;   
   printf("parent process %d\n",global);

   }
pthread_join(ptid,NULL);

   return(0);
}