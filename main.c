#include <stdio.h>
#include "calc_primo.h"
#include <omp.h>


int main(int argc, char** argv)
{
  long n = strtol(argv[1], NULL, 0);
  long number = 0;

  #pragma omp parallel for schedule(dynamic) reduction(+:number)
  for(long i=2; i<=n; i++){
    if(primo(i)){
      number++;
    }
  }

  printf("%d primos menores que %d\n", number, n);
}	
	