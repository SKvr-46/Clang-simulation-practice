#include <stdio.h>

double f(double x, double y) {
    // 常微分方程式の右辺を定義する
    return x + y;
}

int main() {
    double x0 = 0.0;  // 初期値 x0
    double y0 = 1.0;  // 初期値 y0
    double h = 0.1;   // 刻み幅 h
    int n = 10;       // ステップ数 n
    double x = x0;
    double y = y0;
    int i;

    for (i = 0; i < n; i++) {
        // オイラー法による更新式
        y = y + h * f(x, y);
        x = x + h;
        printf("x = %f, y = %f\n", x, y);
    }

    return 0;
}
