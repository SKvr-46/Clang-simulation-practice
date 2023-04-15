#include <stdio.h>
#include <math.h>

double f(double x) {
    // 関数f(x)の定義
    return x * x - 2.0;
}

double df(double x) {
    // 関数f(x)の導関数f'(x)の定義
    return 2.0 * x;
}

int main() {
    double x0 = 1.0;    // 初期値
    double eps = 1e-6;  // 収束条件とする誤差の閾値
    int max_iter = 100; // 最大反復回数
    double x = x0;
    double delta = f(x)/df(x);
    int iter = 0;

    while (fabs(delta) > eps && iter < max_iter) {
        x = x - delta;
        delta = f(x)/df(x);
        iter++;
    }

    if (iter < max_iter) {
        printf("解: %f (反復回数: %d)\n", x, iter);
    } else {
        printf("収束せず (反復回数の上限に達しました)\n");
    }

    return 0;
}
