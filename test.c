
#include <stdio.h>
#include <math.h>
#define NX 720

int main(void){
    FILE *gp; //ファイルストリームのアドレス
    int i;
    double dx, x[NX+1], y[NX+1];
    
   /* ---- データ作成 ---- */
    dx=4*M_PI/NX;
    for(i=0; i<=NX; i++){
        x[i]=-2*M_PI+i*dx;
        y[i]=sin(x[i]);
    }

    /* ---- グラフ作成 ---- */
    gp = popen("gnuplot -persist","w");
    fprintf(gp, "set xrange [-6.5:6.5]\n");  
    fprintf(gp, "set yrange [-1.5:1.5]\n");
    fprintf(gp, "plot '-' with lines linetype 1 title \"sin\"\n");

    for(i=0; i<=NX; i++){
       fprintf(gp,"%f\t%f\n", x[i], y[i]);    // データの書き込み

    }  
    fprintf(gp,"e\n");

    pclose(gp);

    return 0;
}
//fopen、fclose、fread、fwrite、fscanf、fprintf の第一引数はファイルストリームのアドレス