
#include <stdio.h>

int primo(int n)
{
  int i;
  if(n==2) return 1;
  if(n%2==0) return 0;
  for(i = 3; i < n; i +=2)
    if (n % i == 0)
      return 0;
  
  return 1;
}

int main(int argc, char** argv)
{
  long n = strtol(argv[1], NULL, 0);
  long number = 0;

  for(long i=2; i<=n; i++){
    if(primo(i)){
      number++;
    }
  }

  printf("%d primos menores que %d\n", number, n);
}	
	