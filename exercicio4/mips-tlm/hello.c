/* Hello World program */

#include<stdio.h>

main()
{
    printf("Hello World\n");
	
	volatile int* address = (int*) (100*1024*1024);
	*address = 10;

	printf("%d\n", *address); 
	//printf("%d\n", *address); 
	//printf("%d\n", *address); 
}
