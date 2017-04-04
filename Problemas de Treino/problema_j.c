#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int n, t;
long double probabilities[500][500];
long double dp_matrix[501][501];

int main(int argc, char const *argv[]) {
    int i,j;

    scanf("%d %d", &n, &t);

    for ( i = 0; i < n; i++ ) {
        for (j = 0; j < t + 1; j++) {
            scanf("%Lf", &probabilities[i][j]);
        }
    }

    if (n < 500 && n > 1 && t < 500 && t > 1) {


    }





    return 0;
}
