#include "arrayData.c"
#define TRUE 1
#define FALSE 0
pthread_mutex_t lock;
pthread_mutex_t applyQueueLock;
pthread_mutex_t lockRegisterQueue;
pthread_mutex_t lockPasswordQueue;
pthread_mutex_t dataStructureLock;
pthread_mutex_t arrayDLock;
pthread_mutex_t lockpasswordSend;
pthread_mutex_t lockPasswordTaking;

sem_t emptyApplyQueue;
sem_t fullApplyQueue;

sem_t emptySignQueue;
sem_t fullSignQueue;

sem_t emptyPasswordQueue;
sem_t fullPasswordQueue;


sem_t regis;
sem_t apply;
sem_t applicationReceived;
sem_t studentWait;
sem_t pass;


sem_t contactD;


void initializeSyncItems(){

	sem_init(&emptyApplyQueue,0,10);
	sem_init(&fullApplyQueue,0,0);

	sem_init(&emptySignQueue,0,1);
	sem_init(&fullSignQueue,0,0);

	sem_init(&contactD,0,0);


	sem_init(&regis,0,0);
	sem_init(&studentWait,0,0);
	sem_init(&pass,0,0);
	sem_init(&applicationReceived,0,0);
	pthread_mutex_init(&lock,0);
	//pthread_mutex_init(&studentlock,0);
	pthread_mutex_init(&lockRegisterQueue,0);
	pthread_mutex_init(&lockPasswordQueue,0);
	pthread_mutex_init(&dataStructureLock,0);
	pthread_mutex_init(&lockPasswordTaking,0);
	pthread_mutex_init(&arrayDLock,0);
	pthread_mutex_init(&lockpasswordSend,0);
}


void *student(void *argument){
	
	int *answer = (int*)argument;


	
	sem_wait(&emptyApplyQueue);
	pthread_mutex_lock(&applyQueueLock);
	enqueueApplication(*answer);
	pthread_mutex_unlock(&applyQueueLock);
	sem_post(&fullApplyQueue);
	



	
	sem_wait(&emptySignQueue);
	pthread_mutex_lock(&lockRegisterQueue);
	registrationQueue=*answer;
	pthread_mutex_unlock(&lockRegisterQueue);
	sem_post(&fullSignQueue);
	
	

	printf("Student %d has sumbitted for signing.\n\n",*answer );
	
	
	




	while(TRUE){
		pthread_mutex_lock(&lockPasswordTaking);
		
		pthread_mutex_lock(&lockPasswordQueue);
		passwordQueue=*answer;
		pthread_mutex_unlock(&lockPasswordQueue);

		sem_post(&pass);
		sem_wait(&studentWait);


		pthread_mutex_lock(&lockPasswordQueue);
		int m = passwordSend;
		pthread_mutex_unlock(&lockPasswordQueue);

		if(m==-1){
			printf("Student %d is banned from the system!!\n\n",*answer);
			pthread_mutex_unlock(&lockPasswordTaking);
			break;
		}
		else if( m == 0){
			printf("Please Wait %d!!!\n\n",*answer);
			pthread_mutex_unlock(&lockPasswordTaking);
		}
		else {
			printf("Student %d has got the password %d which he asked for\n\n",*answer,m);
			pthread_mutex_unlock(&lockPasswordTaking);
			break;
		}
	} 
	pthread_exit(NULL);
}

void *application(void *argument){
	while(TRUE){
		sem_wait(&fullApplyQueue);
		pthread_mutex_lock(&applyQueueLock);
		int studentID = dequeueApplication();
		pthread_mutex_unlock(&applyQueueLock);
		sem_post(&emptyApplyQueue);




		printf("%s is processing student with ID:%d\n\n",(char*)argument,studentID);
		

		pthread_mutex_lock(&dataStructureLock);
		insertElement(studentID);
		pthread_mutex_unlock(&dataStructureLock);

		printDataStructure();

		sleep(1);
	}

}

void *signing(void *argument){
	while(TRUE){

		sem_wait(&fullSignQueue);
		pthread_mutex_lock(&lockRegisterQueue);
		int y = registrationQueue;
		pthread_mutex_unlock(&lockRegisterQueue);
		sem_post(&emptySignQueue);
		printf("Registering %d\n\n",y );
		

		
		while(TRUE){
			pthread_mutex_lock(&dataStructureLock);
			int choice = duplicate(y);
			int banned = searchBannedList(y);
			if(banned==1){
				deleteMultiple(y);

				pthread_mutex_lock(&arrayDLock);
				insertArrayD(y,-1);
				pthread_mutex_unlock(&arrayDLock);

				printf("##%s just removed the duplicate of %d\n\n",(char*)argument,y);
				printDataStructure();
			    pthread_mutex_unlock(&dataStructureLock);
				break;
			}
			else if(choice==1){
				deleteMultiple(y);

				pthread_mutex_lock(&arrayDLock);
				insertBannedList(y);
				insertArrayD(y,-1);
				pthread_mutex_unlock(&arrayDLock);

				printf("##%s just removed the duplicate of %d\n\n",(char*)argument,y);
			    pthread_mutex_unlock(&dataStructureLock);
			    printDataStructure();
				break;
			}
			else if(choice==-1){
				deleteElement(y);

				pthread_mutex_lock(&arrayDLock);
				insertArrayD(y,1);
				pthread_mutex_unlock(&arrayDLock);

				printf("##%s just verified that %d is legitimate\n\n",(char*)argument,y);
			    pthread_mutex_unlock(&dataStructureLock);
				break;
			}
			
			pthread_mutex_unlock(&dataStructureLock);
			
		}
		

		sleep(1);
		
	}
}

void *password(void *argument){
	while(TRUE){
		sem_wait(&pass);


		pthread_mutex_lock(&lockPasswordQueue);
		int x = passwordQueue;
		pthread_mutex_unlock(&lockPasswordQueue);

		printf("$$D is processing %d\n\n",x);
		printArrayD();

		pthread_mutex_lock(&arrayDLock);
		int y = checkArrayD(x);
		pthread_mutex_unlock(&arrayDLock);

		if(y==0){
			pthread_mutex_lock(&lockpasswordSend);
			passwordSend=0;
			pthread_mutex_unlock(&lockpasswordSend);
			printf("Made %d student wait\n\n",x);
		}
		else if(y==1){
			pthread_mutex_lock(&lockpasswordSend);
			passwordSend=(rand()%50)*36+12;
			pthread_mutex_unlock(&lockpasswordSend);
			pthread_mutex_lock(&arrayDLock);
			deleteArrayD(x);
			pthread_mutex_unlock(&arrayDLock);
			printf("$$D has approved a student %d\n\n",x);
		}
		else{
			pthread_mutex_lock(&lockpasswordSend);
			passwordSend=-1;
			pthread_mutex_unlock(&lockpasswordSend);
			pthread_mutex_lock(&arrayDLock);
			deleteArrayD(x);
			pthread_mutex_unlock(&arrayDLock);
			printf("$$D has disapproved a student %d\n\n",x);
		}
		

		sem_post(&studentWait);
		//printArrayD();
		sleep(1);
		
	}
}

int main(){
	initializeQueue();
	initializeDataStructure();
	initializeSyncItems();
	int rc;



	pthread_t firstThread[30];
	pthread_t threadA;
	pthread_t threadC;
	pthread_t threadE;
	pthread_t threadB;
	pthread_t threadD;

	rc=pthread_create(&threadA,NULL,application,(void*)"A");
    if(rc){
    	printf("Error! return code from pthread_create() is %d\n",rc);
    	exit(-1);
    }

    rc=pthread_create(&threadC,NULL,application,(void*)"C");
    if(rc){
    	printf("Error! return code from pthread_create() is %d\n",rc);
    	exit(-1);
    }

    rc=pthread_create(&threadE,NULL,application,(void*)"E");
    if(rc){
    	printf("Error! return code from pthread_create() is %d\n",rc);
    	exit(-1);
    }

    rc=pthread_create(&threadB,NULL,signing,(void*)"B");
    if(rc){
    	printf("Error! return code from pthread_create() is %d\n",rc);
    	exit(-1);
    }

   rc=pthread_create(&threadD,NULL,password,(void*)"D");
    if(rc){
    	printf("Error! return code from pthread_create() is %d\n",rc);
    	exit(-1);
    }


	void *status;
	int i;
	pthread_mutex_init(&lock,0);
	

    for(i=0;i<30;i++){
    	int *j = (int*)malloc(sizeof(int));
    	*j=(rand()%30)+1;
    	//printf("%d\n\n",*j );
    	rc=pthread_create(&firstThread[i],NULL,student,(void *)j);
    	if(rc){
    		printf("Error! return code from pthread_create() is %d\n",rc);
    		exit(-1);
    	}
    }

    for(i=0;i<30;i++){
    	rc=pthread_join(firstThread[i],&status);
    	if(rc){
    		printf("Error! return code from pthread_create() is %d\n",rc);
    		exit(-1);
    	}
    }    

    printf("We have reached the main thread!!!\n");
    //printQueue(queueApply,lengthOfApplyQueue);
    pthread_exit(NULL);

    /*enqueueApplication(4);
    enqueueApplication(5);
    printQueue(queueApply,lengthOfApplyQueue);*/

    /*rc=pthread_join(threadA,&status);
    if(rc){
    	printf("Error! return code from pthread_create() is %d\n",rc);
    	exit(-1);
    }

    rc=pthread_join(threadC,&status);
    if(rc){
    	printf("Error! return code from pthread_create() is %d\n",rc);
    	exit(-1);
    }

    rc=pthread_join(threadE,&status);
    if(rc){
    	printf("Error! return code from pthread_create() is %d\n",rc);
    	exit(-1);
    }

    rc=pthread_join(threadB,&status);
    if(rc){
    	printf("Error! return code from pthread_create() is %d\n",rc);
    	exit(-1);
    }

    rc=pthread_join(threadD,&status);
    if(rc){
    	printf("Error! return code from pthread_create() is %d\n",rc);
    	exit(-1);
    }*/

    pthread_exit(NULL);

    





	return 0;
}