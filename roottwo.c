#include <stdio.h>

double dif(double x, double y){
    if(x>y)
        return x-y;
    else
        return y-x;
    }


    main(){
    double a,b;

    a=2.0;
    b=(a*a+2)/(2*a);
    while(dif(a,b)>0.00001){
        a=b;
        b=(a*a+2)/(2*a);
    }
    printf("%f\n",b);
    }
