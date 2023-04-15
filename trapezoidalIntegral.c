#include <stdio.h>

/* 被積分関数 */
double f(double x)
{ // 計算結果がπになる式
    return 4 / (1 + x * x); /* 関数f(x)の値を計算して返す */
}

double integ(double a, double b, int n)
{
    // 関数f(x)の区間[a,b]における積分を、分割数nの台形公式で解き、その値を返す
    
    double h;
    h = (b - a) / n;

    double x, sum;
    int i;

    sum = 0;

    // 1/2 * y0を足す → y0 = a
    sum = 1/2 * f(a);

    // y1 ~ yn-1までの総和
    for (i = 1; x<b; i++)
    {
        x = a + h * i;
        sum += f(x);
    }
    // 1/2 * yn を足す → yn = b

    sum = sum + 1/2 * f(b);
    return h * sum;
}

int main(void)
{
    double a, b;
    int n;

    //分割数
    n = 2000;

    // 区間[0, 1]
    a = 0;
    b = 1;

    printf("%d %10.7f\n", n, integ(a, b, n));
    return 0;
}
