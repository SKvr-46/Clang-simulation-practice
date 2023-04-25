#include <stdio.h>
#include <math.h>

double differentiate(double (*f)(double), double x, double h) {
    double result = (f(x + h) - f(x)) / h;
    return result;
}

double func(double x) {
    double result = sin(x);  //微分したい関数
    return result;
}

int main() {
    double x = 0.5;  //微分する点
    double h = 0.0001;  //微小量
    double diff = differentiate(func, x, h);  //微分の結果
    printf("f'(x) = %f\n", diff);
    return 0;
}
