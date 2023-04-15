#include <stdio.h>
#include <math.h>

double numinteg(double a, double b, int n){
  int i;
  double integ;
  double dx;

  integ=0.0;
  dx=(b-a)/n;
  for(i=0;i<n;i++)
    integ=integ+sin(a+dx*i)*dx;
  return integ;
}

int main(){
  int n;

  for(n=1;n<=10;n++)
    printf("分割数=%d 数値積分の結果=%.16f\n",n,numinteg(0.0,3.141592,n));
}