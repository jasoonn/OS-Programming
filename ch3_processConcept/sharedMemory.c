#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <sys/shm.h>
#include <sys/mman.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>

int get_int_len (int value){
  int l=1;
  while(value>9){ l++; value/=10; }
  return l;
}

int main(int argc, char** argv){
   
   int inputNum = atoi(argv[1]);
   if (argc != 2 || inputNum < 1) {
     printf("Error input!\n");
     return 0;
   }
   
  
   const int SIZE = 4096;
   const char* name = "OS";
  
   int shm_fd;
   void* ptr;

   shm_fd = shm_open(name, O_CREAT | O_RDWR, 0666);
   ftruncate(shm_fd, SIZE);
   ptr = mmap(0, SIZE, PROT_WRITE, MAP_SHARED, shm_fd, 0);
   

   pid_t pid;
   
   pid = fork();
   if (pid<0) {
     fprintf(stderr, "Fork Failed\n");
     return 1;
   }
   else if (pid == 0){
     while(1){
       if (inputNum == 1){
         sprintf(ptr, "%d", inputNum);
         break;
       }
       else if (inputNum%2 == 0){
         sprintf(ptr, "%d ", inputNum);
         ptr+= get_int_len(inputNum) + 1;
         inputNum = inputNum/2;
       }
       else {
         sprintf(ptr, "%d ", inputNum);
         ptr+= get_int_len(inputNum) + 1;
         inputNum = inputNum*3 + 1;
       }
     }
   }
   else{
     wait(NULL);
     printf("%s\n", (char *)ptr);
     shm_unlink(name);
   }
   return 0;
}
