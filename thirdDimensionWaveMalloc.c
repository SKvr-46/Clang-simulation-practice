#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define NX 100  // x軸方向のグリッド数
#define NY 100  // y軸方向のグリッド数
#define NZ 100  // y軸方向のグリッド数
#define NT 1000 // 時間ステップ数

int main() {
    FILE *data, *gp;
    char *data_file;

    double ****u;                // 4次元配列 u をポインタで宣言
    double c = 1.0;              // 波の速度
    double dx = 0.1;             // x軸方向のグリッド幅
    double dy = 0.1;             // y軸方向のグリッド幅
    double dz = 0.1;             // z軸方向のグリッド幅
    double dt = 0.1;             // 時間ステップ幅
    double r = c * dt / dx;      // 安定性条件を満たすための係数（収束条件）
    int i, j, k, m;


    u = (double ****) malloc(sizeof(double ***) * NX);
    for (i = 0; i < NX; i++) {
        u[i] = (double ***) malloc(sizeof(double **) * NY);
        for (j = 0; j < NY; j++) {
            u[i][j] = (double **) malloc(sizeof(double *) * NZ);
            for (k = 0; k < NZ; k++) {
                u[i][j][k] = (double *) malloc(sizeof(double) * NT);
            }
        }
    }

    for (i = 0; i < NX; i++) {
        for (j = 0; j < NY; j++) {
            for (k = 0; k < NZ; k++) {
                for(m=0; m<NT; m++){
                    u[i][j][k][m] = 0;
                }
            }
        }
        
    }

    // 時間発展の計算公式
    for (m = 0; m < NT - 1; m++) {
        for (i = 1; i < NX - 1; i++) {
            for (j = 1; j < NY - 1; j++) {
                for (k = 1; k < NZ - 1; k++) {
                        u[i][j][k][m] = u[i][j][k][m] + r * (u[i + 1][j][k][m] + u[i - 1][j][k][m] + u[i][j + 1][k][m] + u[i][j - 1][k][m] + u[i][j][k + 1][m] + u[i][j][k - 1][m] + u[i][j][k][m + 1] + u[i][j][k][m - 1]);
                }
            }
        }
    }

    // 結果の出力
    // FILE* fp = fopen("wave.dat", "w");
    data_file="wave3.dat";  //変数に文字リテラルを代入するときはポインタ変数に代入する。
    data = fopen(data_file,"w"); //wは書き込み専用で開く

    for (i = 0; i < NX; i++) {
        for (j = 0; j < NY; j++) {
            for (k = 0; k < NZ; k++) {
                fprintf(data, "%f %f %f\n", i * dx, j * dy, u[i][j][k][NT-1]);
            }
        }
        fprintf(data, "\n");
    }
    fclose(data);

    gp = popen("gnuplot -persist","w");
    fprintf(gp, "set xrange [0:10]");
    fprintf(gp, "set yrange [0:10]");
    fprintf(gp, "set zrange [-1:1]");
    fprintf(gp, "splot \"%s\" with lines linetype 1 title \"plot\"\n",data_file);
    pclose(gp);


    // 4次元配列 u を解放する
    for (i = 0; i < NX; i++) {
        for (j = 0; j < NY; j++) {
            for (k = 0; k < NZ; k++) {
                free(u[i][j][k]);
            }
            free(u[i][j]);
        }
        free(u[i]);
    }
    free(u);


    return 0;
}