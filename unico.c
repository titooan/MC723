
#include <stdio.h>

int primo(int n)
{
  int i;

  for(i = 2; i < n; i +=2)
    if (n % i == 0)
      return 0;
  
  return 1;
}

int main(int argc, char** argv)
{
  //long n = strtol(argv[1], NULL, 0);
  int n = 104395301;

  if (primo(n))
    printf("%d é primo.\n", n);
  else
    printf("%d não é primo.\n", n);
}	
	