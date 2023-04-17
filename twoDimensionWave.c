#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define NX 100  // x軸方向のグリッド数
#define NY 100  // y軸方向のグリッド数
#define NT 1000 // 時間ステップ数

int main() {
    double u[NX][NY][NT] = {0};  // 波の振幅 3次元配列 u の全要素を 0 で初期化
    double c = 1.0;              // 波の速度
    double dx = 0.1;             // x軸方向のグリッド幅
    double dy = 0.1;             // y軸方向のグリッド幅
    double dt = 0.1;             // 時間ステップ幅
    double r = c * dt / dx;      // 安定性条件を満たすための係数（収束条件）
    int i, j, k;

    // 初期条件の設定
    //具体的には、2次元空間内で中心を中心とした半径10の円の中の点の振幅を1.0に設定し、
    //それ以外の点の振幅を0に初期化しています。つまり、円内に波を発生させている。
    for (i = 0; i < NX; i++) {
        for (j = 0; j < NY; j++) {
            //点 (i,j) が中心を (NX/2, NY/2) とする半径10の円の内側にあるかどうかを判定
            if ((i - NX / 2) * (i - NX / 2) + (j - NY / 2) * (j - NY / 2) < 10 * 10) {
                u[i][j][0] = 1.0;
            }
        }
    }

    // 時間発展の計算公式
    for (k = 0; k < NT - 1; k++) {
        for (i = 1; i < NX - 1; i++) {
            for (j = 1; j < NY - 1; j++) {
                u[i][j][k+1] = 2.0 * u[i][j][k] - u[i][j][k-1] + r * r * (u[i+1][j][k] - 2.0 * u[i][j][k] + u[i-1][j][k] + u[i][j+1][k] - 2.0 * u[i][j][k] + u[i][j-1][k]);
            }
        }
    }

    // 結果の出力
    FILE* fp = fopen("wave.dat", "w");
    for (i = 0; i < NX; i++) {
        for (j = 0; j < NY; j++) {
            fprintf(fp, "%f %f %f\n", i * dx, j * dy, u[i][j][NT-1]);
        }
        fprintf(fp, "\n");
    }
    fclose(fp);
    return 0;
}
