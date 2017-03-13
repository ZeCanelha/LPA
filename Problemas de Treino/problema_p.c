#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

int n_exames = 0;
int n_cases = 0;
int min_colors = 0;
int colors[26];
int adjacency[26][26];
int gcp(int v);
int cor = 0;

int main(int argc, char const *argv[])
{
    int i, x, y;
        scanf("%d %d",&n_exames, &n_cases);

        memset(adjacency, 0,sizeof(adjacency));
        memset(colors, -1,sizeof(colors));

        for (i = 0; i < n_cases; i++) {
            scanf("%d %d",&x, &y);
            adjacency[x][y] = 1;
            adjacency[y][x] = 1;
        }

    gcp(0);

    printf("%d\n", cor);

    return 0;
}

int gcp(int v) {
    int  k, feasible;

    if (v == n_exames + 1) {
        return 1;
    }

    /*CICLO DAS CORES*/
    for (; cor < n_exames; ++cor) {
        feasible = 1;
        /*CICLO DOS NOS ADJACENTES*/
        for (k = 0; k < n_exames; k++) {
            if (adjacency[k][v] == 1) {
                if (colors[k] == cor) {
                    feasible = 0;
                    break;
                }
            }
        }

        if (feasible == 1) {
            colors[v] = cor;
            if (gcp(v+1) == 1) {
                return 1;
            }
            colors[v] = -1;
        }
    }
    return 0;
}
