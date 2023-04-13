#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define NX 10

int main(){
    FILE *gp;
    int a,b;
    double x, y, z;

    gp = popen("gnuplot -persist", "w");
    fprintf(gp, "set xrange [-1:1]\n");
    fprintf(gp, "set yrange [-1:1]\n");
    fprintf(gp, "set zrange [-2:2]\n");
    fprintf(gp, "splot '-' with lines linetype 1 title \"sin\"\n");

    for(a=0; a<= NX; a++){
        for(b=0; b<= NX; b++){
            x = -1 + 2.0*a/NX;
            y = -1 + 2.0*b/NX;
            z = x*x - y*y;
            fprintf(gp,"%f %f %f\n", x, y, z);
        }
        fprintf(gp, "\n");
    }


    fprintf(gp, "e\n");

    pclose(gp);


    return 0;
}