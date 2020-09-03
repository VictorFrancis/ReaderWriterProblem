#include<stdio.h>
#include<string.h>
#include<pthread.h>
#include<stdlib.h>
#include<unistd.h>

pthread_mutex_t rd,wrt;//reader and writer mutex
int readcount;//storing the number of reader

void initialize(){
	pthread_mutex_init(&rd,NULL);
	pthread_mutex_init(&wrt,NULL);
	readcount=0;
}

void* reader(void* arg){
	int waittime;
	waittime = rand() % 5;
	printf("\nReader is trying to enter\n");
	pthread_mutex_lock(&rd);
	readcount++;
	if(readcount==1){
		pthread_mutex_lock(&wrt);
	}
	pthread_mutex_unlock(&rd);
	printf("\n%d Reader is inside \n",readcount);
	sleep(waittime);
	pthread_mutex_lock(&rd);
	readcount--;
	if(readcount==0){
		pthread_mutex_unlock(&wrt);
	}
	pthread_mutex_unlock(&rd);
	printf("\nReader is leaving\n");
}
void* writer(void* arg){
	int waittime;
	waittime = rand() % 3;
	printf("\nWriter is trying to enter\n");
	pthread_mutex_lock(&wrt);
	printf("\nwriter has entered the critical section\n");
	sleep(waittime);
	pthread_mutex_unlock(&wrt);
	printf("\nwriter is leaving\n");
}

int main()
{
	int r = 5;//number of reader
	int w = 3;//number of writer
	pthread_t rtid[r];
	pthread_t wtid[w];
	initialize();
	//spawning reader thread
	for (int i = 0; i < r; ++i)
	{
		int err;
		err = pthread_create(&(rtid[i]),NULL,&reader,NULL);
	}
	//spawning writer thread
	for (int i = 0; i < w; ++i)
	{
		int err;
		err = pthread_create(&(wtid[i]),NULL,&writer,NULL);
	}

	//exiting thread
	for (int i = 0; i < r; ++i)
	{
		pthread_join(rtid[i],NULL);
	}

	for (int i = 0; i < w; ++i)
	{
		pthread_join(wtid[i],NULL);
	}

	return 0;
}