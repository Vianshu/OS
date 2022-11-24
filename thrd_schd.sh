#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <time.h>
#include <sched.h>
#include <sys/resource.h>

// struct args {
// };

void countA() {
    for (unsigned long i=1; i<=4294967296; i++) {
        continue;
    }
}

void countB() {
    for (unsigned long i=1; i<=4294967296; i++) {
        continue;
    }
}

void countC() {
    for (unsigned long i=1; i<=4294967296; i++) {
        continue;
    }
}

void* Thr_A(void* args) {
    struct timespec start;
    struct timespec end;
    struct sched_param* paramA = (struct sched_param*)malloc(sizeof(struct sched_param));
    
    int niceVal = 10;

    if (paramA != NULL) {
        paramA -> sched_priority = 0;
    }


    pthread_setschedparam(pthread_self(), SCHED_OTHER, paramA);
    nice(niceVal);

    printf("Thread A has started counting!\n");
    
    FILE* file;
    file = fopen("threadRuntimeCFS.txt", "a");

    int startTime = clock_gettime(CLOCK_REALTIME, &start);
    countA();
    int endTime = clock_gettime(CLOCK_REALTIME, &end);

    double runTime = (end.tv_sec + 1.0e-9*end.tv_nsec - (start.tv_sec + 1.0e-9*start.tv_nsec));

    fprintf(file, "%d %lfs\n", niceVal, runTime);
    free(paramA);
    return NULL;
}

void* Thr_B(void* args) {
    struct timespec start;
    struct timespec end;
    struct sched_param* paramB = (struct sched_param*)malloc(sizeof(struct sched_param));
    if (paramB != NULL) {
        paramB -> sched_priority = 1;
    }

    pthread_setschedparam(pthread_self(), SCHED_RR, paramB);

    printf("Thread B has started counting!\n");
    
    FILE* file;
    file = fopen("threadRuntimeRR.txt", "a");
    
    int startTime = clock_gettime(CLOCK_REALTIME, &start);
    countB();
    int endTime = clock_gettime(CLOCK_REALTIME, &end);

    double runTime = (end.tv_sec + 1.0e-9*end.tv_nsec - (start.tv_sec + 1.0e-9*start.tv_nsec));

    fprintf(file, "%d %lfs\n", paramB->sched_priority, runTime);
    free(paramB);
    return NULL;
}

void* Thr_C(void* args) {
    struct timespec start;
    struct timespec end;
    struct sched_param* paramC = (struct sched_param*)malloc(sizeof(struct sched_param));
    if (paramC != NULL) {
        paramC -> sched_priority = 1;
    }

    pthread_setschedparam(pthread_self(), SCHED_FIFO, paramC);

    printf("Thread C has started counting!\n");
    
    FILE* file;
    file = fopen("threadRuntimeFIFO.txt", "a");
    int startTime = clock_gettime(CLOCK_REALTIME, &start);
    countC();
    int endTime = clock_gettime(CLOCK_REALTIME, &end);

    double runTime = (end.tv_sec + 1.0e-9*end.tv_nsec - (start.tv_sec + 1.0e-9*start.tv_nsec));

    fprintf(file, "%d %lfs\n", paramC->sched_priority, runTime);
    fclose(file);
    free(paramC);
    return NULL;
}

int main() {

    pthread_t ThrA;
    pthread_t ThrB;
    pthread_t ThrC;

    // Thread A
    pthread_create(&ThrA, NULL, Thr_A, NULL);
    //Thread B
    pthread_create(&ThrB, NULL, Thr_B, NULL);
    //Thread C
    pthread_create(&ThrC, NULL, Thr_C, NULL);

    //Joining all threads
    pthread_join(ThrA, NULL);
    pthread_join(ThrB, NULL);
    pthread_join(ThrC, NULL);
    printf("All threads have terminated.\n");
    return 0;
}
