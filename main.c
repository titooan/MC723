#include <stdio.h>
#include "calc_primo.h"


int main(int argc, char** argv)
{
  long n = strtol(argv[1], NULL, 0);
  //int n = 104395301;

  if (primo(n))
    printf("%d é primo.\n", n);
  else
    printf("%d não é primo.\n", n);
}	
	