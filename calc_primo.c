int primo(int n)
{
  int i;

  for(i = 2; i < n; i +=1)
    if (n % i == 0)
      return 0;
  
  return 1;
}