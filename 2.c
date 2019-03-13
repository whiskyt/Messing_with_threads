#include <stdio.h>
#include <string.h>
#include <pthread.h>

pthread_t tid[4]; // array of pthread_t objects ... easier than initialising 4 pthread_t objects individually
float var = 64.0; // shared variable
int counter=0;
pthread_mutex_t lock; // mutex object

void incre()//function to increment 
{
	var = var+1;
}

void decre()//function to deincrement
{
	var = var-1.0;
}

void doubleFloat()//function to double
{
	var = var*2.0;
}

void halve()//function to half
{
	var = var*(0.5);
}	


void* function(void* arg) // function to be used bt threads, to perform operations on shared variable, var.
{
	pthread_mutex_lock(&lock); // thread locks mutex, so no other thread can have access

	if((counter%4)==0) // ensures that whatever the value inside counter , each thread will execute a different function
	{
		printf("-- Thread %d executing incre() --\n",counter+1);
		printf("var before incre() is %f\n",var);
		incre();
		printf("var after incre() is %f\n\n",var);
		
	}
	if((counter%4)==1)
	{
		printf("-- Thread %d executing double() --\n",counter+1);
		printf("var before double() is %f\n",var);
		doubleFloat();
		printf("var after double() is %f\n\n",var);
	}
	if((counter%4)==2)
	{
		printf("-- Thread %d executing decre() --\n",counter+1);
		printf("var before decre() is %f\n",var);
		decre();
		printf("var after decre() is %f\n\n",var);	
	}
	if((counter%4)==3)
	{
		printf("-- Thread %d executing halve() --\n",counter+1);
		printf("var before halve() is %f\n",var);
		halve();
		printf("var after halve() is %f\n\n",var);
	}
	
	counter++; // incrementing counter
	pthread_mutex_unlock(&lock); //unlocks mutex for other threads to access
	return NULL;
}

int main()
{
	int i =0;
	int err;

	if(pthread_mutex_init(&lock,NULL) != 0) // if mutex initialisation fails
	{
		printf("\n-- mutex init failed --\n");
		return 1;
	}
	while(i<4) // mutex initialisation successful
	{
		err = pthread_create(&(tid[i]),NULL,&function,NULL); // if thread creation successful, thread with thread id tid[i] will execute function. 
		if(err !=0) //if thread creation fails
			printf("\n-- Cant create thread -- :[%s]\n",strerror(err));
		i++;
	}
	pthread_join(tid[0],NULL); //waiting for respective threads to complete before termination of process
	pthread_join(tid[1],NULL);
	pthread_join(tid[2],NULL);
	pthread_join(tid[3],NULL);
	pthread_mutex_destroy(&lock); // destroys mutex object, cannot be used again after this.

	return 0;
}
