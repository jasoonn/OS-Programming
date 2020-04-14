#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int pointsNum; /* this data is shared by the thread(s) */
void *runner(void *param); /* the thread */

int main(int argc, char *argv[])
{
    pthread_t tid;       /* the thread identifier */
    pthread_attr_t attr; /* set of attributes for the thread */
    int size = atoi(argv[1]);

    if (argc != 2) {
        fprintf(stderr,"usage: a.out <integer value>\n");
        return -1;
    }

    if (size < 0) {
        fprintf(stderr,"Argument %d must be non-negative\n",size);
        return -1;
    }

    /* get the default attributes */
    pthread_attr_init(&attr);


    /* create the thread */
    pthread_create(&tid,&attr,runner,argv[1]);

    /* now wait for the thread to exit */
    pthread_join(tid,NULL);
   
   printf("%f\n", (double)pointsNum*4/(double)size);
}

void *runner(void *param) 
{
   int upper = atoi(param);
   
   while(upper>0){
       double rand_x = (double)rand() / ((double)RAND_MAX + 1);
       double rand_y = (double)rand() / ((double)RAND_MAX + 1);
       if (rand_x*rand_x+rand_y*rand_y<1) pointsNum++;
       upper--;
   }

   pthread_exit(0);
}