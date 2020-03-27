#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char** argv){
   
   int inputNum = atoi(argv[1]);
   if (argc != 2 || inputNum < 1) {
     printf("Error input!\n");
     return 0;
   }
 
   pid_t pid;
   
   pid = fork();
   if (pid<0) {
     fprintf(stderr, "Fork Failed\n");
     return 1;
   }
   else if (pid == 0){
     while(1){
       if (inputNum == 1){
         printf("%d\n", inputNum);
         break;
       }
       else if (inputNum%2 == 0){
         printf("%d ", inputNum);
         inputNum = inputNum/2;
       }
       else {
         printf("%d ", inputNum);
         inputNum = inputNum*3 + 1;
       }
     }
   }
   else{
     wait(NULL);
   }
   return 0;
}
