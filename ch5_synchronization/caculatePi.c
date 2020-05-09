#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void *runner(void *param);
int counter;
pthread_mutex_t mutex;
pthread_t tid[5];

int main(int argc, char *argv[]){
    int pointNum = 1000;
    if (pthread_mutex_init(&mutex, NULL) != 0)
    {
        printf("\n mutex init failed\n");
        return 1;
    }
    for(int i=0;i<5;i++){
        pthread_attr_t attr;
        pthread_attr_init(&attr);
        pthread_create(&tid[i],&attr,runner,&pointNum);
    }

    for(int i=0;i<5;i++){
        pthread_join(tid[i],NULL);
    }
    pthread_mutex_destroy(&mutex);
    printf("%f\n", (double)counter*4/(double)(pointNum*5));

}


void *runner(void *param) 
{
   int upper = *(int*)(param);
   pthread_mutex_lock(&mutex);
   while(upper>0){
       double rand_x = (double)rand() / ((double)RAND_MAX + 1);
       double rand_y = (double)rand() / ((double)RAND_MAX + 1);
       if (rand_x*rand_x+rand_y*rand_y<1)  counter++;
       upper--;
   }
   pthread_mutex_unlock(&mutex);

   pthread_exit(0);
}