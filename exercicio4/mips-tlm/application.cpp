#include<stdio.h>
#define MAX 100000

volatile int numberProcs = 0;

volatile int *lock = (volatile int*) (100*1024*1024);

volatile int lock1 = 0;

volatile int numberFound = 0;
volatile int lockNumberFound = 0;

volatile int finished = 0;
volatile int lockFinished = 0;

void AcquireGlobalLock(){
	while(*lock);
}

void ReleaseGlobalLock(){
	*lock = 0;
}

void AcquireLocalLock(volatile int* lock){
    AcquireGlobalLock();
    while(*lock){
        ReleaseGlobalLock();
    for(int i=0; i < 15; i++) {}
    AcquireGlobalLock();
   }
    *lock = 1;
    ReleaseGlobalLock();
}

void ReleaseLocalLock(volatile int* lock){
    AcquireGlobalLock();
    *lock = 0;
    ReleaseGlobalLock();
}

int isPrime(int number){
	int isPrime = 1;
	for(int i=2; i*i<number; i++){
		if(number%i==0){
			return 0;
		}
	}
	return 1;
}

int foundOne(){
	AcquireLocalLock(&lockNumberFound);
	numberFound++;
	ReleaseLocalLock(&lockNumberFound);
}

int getNumberFound(){

	int result;
	AcquireLocalLock(&lockNumberFound);
		result = numberFound;
	ReleaseLocalLock(&lockNumberFound);	

	return result;
}



main()
{

    int numProc;
    int localSum = 0;
   	printf("OOH \n");
   	AcquireLocalLock(&lock1);
   	numProc = numberProcs;
   	numberProcs++;
   	ReleaseLocalLock(&lock1);

   	int i;
	int max;

	if(numProc ==0){
		i=2;
		max = MAX/2;
	}else{
		i=MAX/2;
		max = MAX;
	}

	for(;i<max;i++){
		if(isPrime(i)){
			foundOne();
		}
	}

	AcquireLocalLock(&lockFinished);
   	finished++;
   	if(finished == 2){
   		printf("Found %d prime numbers < %d", getNumberFound(), MAX);
   	}
   	ReleaseLocalLock(&finished);




}


