#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/syscall.h>
#define K2D_MEMCPY_SYS_CALL 451
int main(int argc, char*argv[]){
	float M1[2][2]={{2.2,2.3},{3.2,3.3}};
	float M2[2][2]={{1,2},{3,4}};
	printf("Matrix 1 initially is ");
	for (int i=0; i<2; i++){
		for (int j=0; j<2; j++){
			printf("%lf ",M1[i][j]);
		}
		printf("\n");
	}
	printf("Matrix 2 initially is ");
	for (int i=0; i<2; i++){
		for (int j=0; j<2; j++){
			printf("%lf ",M2[i][j]);
		}
		printf("\n");
	}
	int rt=syscall(K2D_MEMCPY_SYS_CALL, M1, M2);
	if (rt<0){
		printf("FAILED");
	}
	printf("Matrix 1 finally is ");
	for (int i=0; i<2; i++){
		for (int j=0; j<2; j++){
			printf("%lf ",M1[i][j]);
		}
		printf("\n");
	}
	printf("Matrix 2 finally is ");
	for (int i=0; i<2; i++){
		for (int j=0; j<2; j++){
			printf("%lf ",M2[i][j]);
		}
		printf("\n");
	}
	return 0;
}
	
	
	
	
	
