#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define NX 100  // x軸方向のグリッド数
#define NY 100  // y軸方向のグリッド数
#define NT 1000 // 時間ステップ数

int main() {
    FILE *data, *gp;
    char *data_file;

    double ***u;                // 3次元配列 u をポインタで宣言
    double c = 3.0;             // 波の速度
    double dx = 0.1;             // x軸方向のグリッド幅
    double dy = 0.1;             // y軸方向のグリッド幅
    double dt = 0.1;             // 時間ステップ幅
    double r = c * dt / dx;      // 安定性条件を満たすための係数（収束条件）
    int i, j, k;

    // 3次元配列 u を動的に割り当てる
    u = (double***) malloc(sizeof(double**) * NX);
    for (i = 0; i < NX; i++) {
        //u[i]はuの先頭アドレスからi番目のアドレスを指すポインタ=>u[i]は2次元配列の行
        u[i] = (double**) malloc(sizeof(double*) * NY);
        for (j = 0; j < NY; j++) {
            //u[i][j]はi行目のj列目の要素
            u[i][j] = (double*) malloc(sizeof(double) * NT);
        }
    }

    // 3次元配列 u を 0 で初期化
    for (i = 0; i < NX; i++) {
        for (j = 0; j < NY; j++) {
            for (k = 0; k < NT; k++) {
                u[i][j][k] = 0;
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
    // FILE* fp = fopen("wave.dat", "w");
    data_file="wave.dat";  //変数に文字リテラルを代入するときはポインタ変数に代入する。
    data = fopen(data_file,"w"); //wは書き込み専用で開く

    for (i = 0; i < NX; i++) {
        for (j = 0; j < NY; j++) {
            fprintf(data, "%f %f %f\n", i * dx, j * dy, u[i][j][NT-1]);
        }
        fprintf(data, "\n");
    }
    fclose(data);

    gp = popen("gnuplot -persist","w");
    fprintf(gp, "set xrange [0:10]\n");
    fprintf(gp, "set yrange [0:10]\n");
    fprintf(gp, "set zrange [-10:10]\n");
    fprintf(gp, "splot \"%s\" with lines linetype 1 title \"sin\"\n",data_file);
    pclose(gp);



    // 3次元配列 u を解放する
    for (i = 0; i < NX; i++) {
        for (j = 0; j < NY; j++) {
            free(u[i][j]);
        }
        free(u[i]);
    }
    free(u);


    return 0;
}