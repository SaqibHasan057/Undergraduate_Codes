#include<stdio.h>
#include<pthread.h>
#include<stdlib.h>

struct threadArg{
    int random;
    long id;
};

struct threadArg data[5];

void * PrintHello(void *th){
    struct threadArg *tinfo=(struct threadArg *) th;

    long tid=tinfo->id;
    int random=tinfo->random;



    printf("It's thread #%ld and random= %d\n",tid,random);
    /*for(int i=0;i<1000;i++){
        if(i%100==0){
            printf("Loop %d thread #%ld\n",i,tid);
        }
        if(i==999)
            printf("Loop end thread #%ld\n",tid);
    }
    */

    sleep(random);
    printf("Sleep ends %d sec thread #%ld\n",random,tid);

    pthread_exit(NULL);
}

int main(){
    srand(time(NULL));

    pthread_t threads[5];
    int rc;
    long t;
    for(t=0;t<5;t++){
        data[t].id=t;
        data[t].random=rand()%5;

        printf("Main: creating thread %ld with random %d...\n",t,data[t].random);
        rc=pthread_create(&threads[t],NULL,PrintHello,(void *)&data[t]);
        if(rc){
            printf("Error! return code from pthread_create() is %d\n",rc);
            exit(-1);
        }
    }

    //pthread_exit(NULL);
    //while(1);

    return 0;
}
