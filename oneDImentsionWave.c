#include <stdio.h>
#include <math.h>

#define PI 3.14159265358979323846

double func(double x, double t) {
    // 初期条件として与えられた関数 f(x)
    return sin(2*PI*x);
}

int main() {
    int nx = 100;          // 空間方向のグリッド数
    double dx = 0.1;       // 空間方向の刻み幅
    double dt = 0.001;     // 時間方向の刻み幅
    double c = 1.0;        // 波速度
    double tmax = 1.0;     // 計算の終了時刻
    double t = 0.0;        // 現在の時間
    double u[nx];          // u(x, t)の配列
    double u_new[nx];      // 時間ステップt+dtでのu(x)の配列

    // 初期条件の設定
    for (int i = 0; i < nx; i++) {
        double x = i*dx;
        u[i] = func(x, 0.0);
    }

    // タイムステップのループ
    while (t < tmax) {
        // 端点以外の空間方向の差分を計算
        for (int i = 1; i < nx-1; i++) {
            u_new[i] = u[i] + c*c*dt/dx/dx*(u[i+1] - 2*u[i] + u[i-1]);
        }
        // 端点の差分を計算
        u_new[0] = u[0] + c*c*dt/dx/dx*(u[1] - 2*u[0] + u[nx-1]);
        u_new[nx-1] = u[nx-1] + c*c*dt/dx/dx*(u[0] - 2*u[nx-1] + u[nx-2]);
        // u(x, t+dt)を更新
        for (int i = 0; i < nx; i++) {
            u[i] = u_new[i];
        }
        // 時間を更新
        t += dt;
    }

    // 結果の出力
    for (int i = 0; i < nx; i++) {
        double x = i*dx;
        printf("%f %f\n", x, u[i]);
    }

    return 0;
}
