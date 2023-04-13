#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define NX 50

int main(){
    FILE *gp;
    int i,j;
    double x,y,z;

    gp = popen("gnuplot -persist", "w");
    fprintf(gp, "set xrange [-5:5]\n");
    fprintf(gp, "set yrange [-5:5]\n");
    fprintf(gp, "set zrange [-50:50]\n");
    fprintf(gp, "splot '-' with lines linetype 1 title \"x^2 - y^2\"\n");

    for(i=0;i<=NX;i++){
        for(j=0;j<=NX;j++){
            x=-5+10.0/NX*i;
            y=-5+10.0/NX*j;
            z=x*x-y*y;
            fprintf(gp,"%f %f %f\n",x,y,z);
        }
        //gnuplotにデータの1セット（この場合は2次元座標平面上での点）が終わったことを伝えるためのもの
        fprintf(gp,"\n");  
    }

    fprintf(gp, "e\n");

    pclose(gp);
    return 0;
}
