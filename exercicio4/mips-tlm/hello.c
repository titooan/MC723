/* Hello World program */

#include<stdio.h>

volatile int numberProcs = 0;

main()
{
	int numProc = numberProcs++;
    printf("Hello World %d/%d\n", numProc, numberProcs);
	
	volatile int* address = (int*) (100*1024*1024);
	*address = 0;

	printf("%d\n", *address); 
	printf("%d\n", *address); 
	printf("%d\n", *address); 
}
