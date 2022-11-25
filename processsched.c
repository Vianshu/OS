#include<stdio.h>
#include<pthread.h>
#include<stdlib.h>
#include<sys/resource.h>
#include<time.h>
#include<sched.h>
#include<sys/wait.h>
#include<string.h>
#include<unistd.h>
#include<sys/types.h>

int main(int argc, char *argv[]){
	struct timespec sfi,ffi;
	struct timespec srr, frr;
	struct timespec sot, fot;

	pid_t p1;
	pid_t p2;
	pid_t p3;

	/*I will be giving priority values in v1 and v2 for FIFO and RR*/
	int v1=5;
	int v2=10;

	struct sched_param fi=(struct sched_param*)malloc(sizeof(struct sched_param));
	struct sched_param rr=(struct sched_param*)malloc(sizeof(struct sched_param));
	struct sched_param ot=(struct sched_param*)malloc(sizeof(struct sched_param));
	
	if (fi != NULL){
		fi->sched_priority=v1;
	}
	
	if (rr != NULL){
		rr->sched_priority=v2;
	}
	
	if (ot != NULL){
		ot->sched_priority=0;
	}
	clock_gettime(CLOCK_MONOTONIC,&srr);
	clock_gettime(CLOCK_MONOTONIC,&sfi);
	clock_gettime(CLOCK_MONOTONIC,&sot);

	if ((p1 == fork())==0){
		sched_setscheduler(p1, SCHED_FIFO, fi);
		execlp("bash","bash","kern1.sh",NULL);
	}
	if ((p2 == fork())==0){
		sched_setscheduler(p2, SCHED_RR, rr);
		execlp("bash","bash","kern2.sh",NULL);
	}
	
	if ((p3 == fork())==0){
		sched_setscheduler(p1, SCHED_OTHER, ot);
		execlp("bash","bash","kern3.sh",NULL);
	}
	
	/* Generating files for storing runtime values */
	FILE *f1;
	FILE *f2;
	FILE *f3;
	f1=fopen("FIFOrunProcess.txt","a");
	f2=fopen("RRrunProcess.txt","a");
	f3=fopen("OTHER(CFS)runProcess.txt","a");
	/* Using wait() for checking which process has ended */

	for (int g=0; g<3; g++){
		pid_t c= wait(NULL);
		if (c == p1){
			clock_gettime(CLOCK_MONOTONIC,&ffi);
			double runtimef=0;
			runtimef+=(ffi_tv.sec-sfi_tv.sec);
			runtimef+=(ffi_tv.nsec-sfi_tv.nsec)/1000000000.0;
			fprintf(f1,"%d %lf",v1,runtimef);
			fclose(f1);
		}
		else if (c == p2){
			clock_gettime(CLOCK_MONOTONIC,&frr);
			double runtimer=0;
			runtimer+=(frr_tv.sec-srr_tv.sec);
			runtimer+=(frr_tv.nsec-srr_tv.nsec)/1000000000.0;
			fprintf(f2,"%d %lf",v2,runtimer);
			fclose(f2);
		}
		else if (c == p3){
			clock_gettime(CLOCK_MONOTONIC,&fot);
			double runtimet=0;
			runtimet+=(fot_tv.sec-sot_tv.sec);
			runtimet+=(fot_tv.nsec-sot_tv.nsec)/1000000000.0;
			fprintf(f3,"%d %lf",0,runtimet);
			fclose(f3);
		}
		
	}
	
	return 0;
}