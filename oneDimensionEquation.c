#include <stdio.h>
#include <gsl/gsl_math.h>
#include <gsl/gsl_linalg.h>
#define N 3 //行列サイズ

int main()
{
    double A[N*N] = {6, -2, 2, -2, 3, -1, 2, -1, 3}; // 入力行列
    double B[N] = {2, -1, 1}; // 右辺ベクトル
    double X[N]; // 解ベクトル

    gsl_matrix_view m = gsl_matrix_view_array(A, N, N);
    gsl_vector_view b = gsl_vector_view_array(B, N);
    gsl_vector_view x = gsl_vector_view_array(X, N);

    int s; // サブルーチンの戻り値

    gsl_permutation *p = gsl_permutation_alloc(N);
    gsl_matrix *LU = gsl_matrix_alloc(N, N);

    gsl_linalg_LU_decomp(&m.matrix, p, &s);
    gsl_linalg_LU_solve(&m.matrix, p, &b.vector, &x.vector);

    gsl_permutation_free(p);
    gsl_matrix_free(LU);

    // 解を表示する
    printf("解ベクトル：\n");
    for (int i = 0; i < N; i++) {
        printf("%f\n", X[i]);
    }

    return 0;
}
