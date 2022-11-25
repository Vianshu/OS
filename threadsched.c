#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
#include<sched.h>
#include<time.h>
#include<sys/wait.h>
#include<unistd.h>
#include<sys/resource.h>

void countA(){
	for (unsigned long i=0; i<4294967296; i++){
		continue;
	}
}
void countB(){
	for (unsigned long i=0; i<4294967296; i++){
		continue;
	}
}
void countC(){
	for (unsigned long i=0; i<4294967296; i++){
		continue;
	}
}
void *tt1(void *args){
	long long int v=(long long int)args;
	struct timespec frr;
	struct sched_param* rr=(struct sched_param*)malloc(sizeof(struct sched_param));
	if (rr != NULL){
		rr->sched_priority=v;
	}
	pthread_setschedparam(pthread_self(), SCHED_RR, rr);
	struct timespec srr;
	clock_gettime(CLOCK_MONOTONIC, &srr);
	countB();
	clock_gettime(CLOCK_MONOTONIC, &frr);
	double runtime=0;
	runtime+=(frr.tv_sec-srr.tv_sec);
	runtime+=(frr.tv_sec-srr.tv_nsec)/1000000000.0;
	FILE *file;
	file=fopen("RR.txt","a");
	fprintf(file, "%lld %lf\n",v,runtime);
	fclose(file);
	double *y=(double *)malloc(sizeof(double));
	*y=runtime;
}
void *tt2(void *args){
	long long int v=(long long int)args;
	struct timespec frr;
	struct sched_param* rr=(struct sched_param*)malloc(sizeof(struct sched_param));
	if (rr != NULL){
		rr->sched_priority=v;
	}
	pthread_setschedparam(pthread_self(), SCHED_FIFO, rr);
	struct timespec srr;
	clock_gettime(CLOCK_MONOTONIC, &srr);
	countB();
	clock_gettime(CLOCK_MONOTONIC, &frr);
	double runtime=0;
	runtime+=(frr.tv_sec-srr.tv_sec);
	runtime+=(frr.tv_sec-srr.tv_nsec)/1000000000.0;
	FILE *file;
	file=fopen("FIFO.txt","a");
	fprintf(file, "%lld %lf\n",v,runtime);
	fclose(file);
	double *y=(double *)malloc(sizeof(double));
	*y=runtime;
}
void *tt3(void *args){
	long long int v=(long long int)args;
	struct timespec frr;
	struct sched_param* rr=(struct sched_param*)malloc(sizeof(struct sched_param));
	if (rr != NULL){
		rr->sched_priority=0;
	}
	pthread_setschedparam(pthread_self(), SCHED_OTHER, rr);
	struct timespec srr;
	clock_gettime(CLOCK_MONOTONIC, &srr);
	countB();
	clock_gettime(CLOCK_MONOTONIC, &frr);
	double runtime=0;
	runtime+=(frr.tv_sec-srr.tv_sec);
	runtime+=(frr.tv_sec-srr.tv_nsec)/1000000000.0;
	FILE *file;
	file=fopen("OTHER.txt","a");
	fprintf(file, "%lld %lf\n",v,runtime);
	fclose(file);
	double *y=(double *)malloc(sizeof(double));
	*y=runtime;
}

int main(int argc, char *argv[]){
	pthread_t t1;
	pthread_t t2;
	pthread_t t3;
	long long int v1=50;
	long long int v2=50;
	long long int v3=0;
				
	pthread_create(&t1, NULL, tt1, (void *)v1);
	pthread_create(&t2, NULL, tt2, (void *)v2);
	pthread_create(&t3, NULL, tt3, (void *)v3);

	pthread_join(t1, NULL);
	pthread_join(t2, NULL);
	pthread_join(t3, NULL);

	return 0;
}

