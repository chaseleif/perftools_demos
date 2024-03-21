#include <stdio.h>
#include <stdlib.h>

int main(int argc,char **argv) {
  unsigned long long n=0, n_1=1;
  for (int times=0;times<100;++times) {
  for (int i=0;i<200000000;++i) {
    unsigned long long newn = n_1+n;
    n=n_1;
    n_1=newn;
  }
  }
  printf("%ull\n",n_1);
  return 0;
}
