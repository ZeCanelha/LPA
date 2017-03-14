#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

int n_exames = 0;
int n_cases = 0;
int colors[26];
int adjacency[26][26];
int gcp(int v);
int used_colors = 1;

int main(int argc, char const *argv[])
{
    int i, x, y, j;
    scanf("%d %d",&n_exames, &n_cases);

    memset(adjacency, 0,sizeof(adjacency));
    memset(colors, -1,sizeof(colors));

    for (i = 0; i < n_cases; i++) {
        scanf("%d %d",&x, &y);
        adjacency[x][y] = 1;
        adjacency[y][x] = 1;
    }

    if (n_exames == 0 || n_cases == 0) {
        used_colors = 0;
    } else {
        for (j = 0; j < n_exames; j++) {
            memset(colors, -1,sizeof(colors));
            colors[j] = 1;
            gcp(j);
            colors[j] = -1;
        }

    }

    printf("%d\n", used_colors);

    return 0;
}

int gcp(int v) {
    int  cor, k, feasible;

    if (v == n_exames + 1) {
        return 1;
    }

    /*CICLO DAS CORES*/
    for (cor = 1; cor < n_exames +1; cor++) {
        if (cor > used_colors) {
            used_colors = cor;
        }
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
