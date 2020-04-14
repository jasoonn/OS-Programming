#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

int* fSeries; /* this data is shared by the thread(s) */
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

    fSeries = (int*)malloc(sizeof(int)*size);
    if(fSeries==NULL){
        printf("malloc fail.\n");
        return -1;
    }

    /* get the default attributes */
    pthread_attr_init(&attr);


    /* create the thread */
    pthread_create(&tid,&attr,runner,argv[1]);

    /* now wait for the thread to exit */
    pthread_join(tid,NULL);
    for (int i=0; i< size-1; i++){
        printf("%d ", fSeries[i]);
    }
    printf("%d\n", fSeries[size-1]);
    free(fSeries);
}

void *runner(void *param) 
{
   int upper = atoi(param);
   
   int first = 0;
   int second = 1;
   for(int i=0;i<upper;i++){
       fSeries[i] = first;
       int tmp = second;
       second = first + second;
       first = tmp;
   }

   pthread_exit(0);
}