#include<stdio.h>
#include<pthread.h>
#include<stdlib.h>
#include<unistd.h>
void * PrintHello(void *threadid){

    long *tid;
    tid=(long *)threadid;
    printf("It's thread #%ld\n",*tid);
    /*for(int i=0;i<1000;i++){
        if(i%100==0){
            printf("Loop %d thread #%ld\n",i,*tid);
        }
        if(i==999)
            printf("Loop end thread #%ld\n",*tid);
    }
    */

    //sleep(2);
    printf("Sleep ends 2 sec thread #%ld\n",*tid);

    pthread_exit(NULL);
}

int main(){
    pthread_t threads[5];
    int rc;
    long t;
    long x[5]={0,1,2,3,4};
    for(t=0;t<5;t++){
        printf("Main: creating thread %ld...\n",t);
        rc=pthread_create(&threads[t],NULL,PrintHello,(void *)&x[t]);
        if(rc){
            printf("Error! return code from pthread_create() is %d\n",rc);
            exit(-1);
        }
    }

    pthread_exit(NULL);
    //while(1);

    return 0;
}
