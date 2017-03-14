#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

int n_members = 0;
int n_connections = 0;
int colors[1000];
int cor = 1;
int adjacency[1000][1000];
int gcp(int v);
int a  = 0;
int max = 0;

int main(int argc, char const *argv[])
{
    int i, x, y;
    scanf("%d %d",&n_members, &n_connections);

    memset(adjacency, 0,sizeof(adjacency));


    for (i = 0; i < n_connections; i++) {
        scanf("%d %d",&x, &y);
        adjacency[x][y] = 1;
        adjacency[y][x] = 1;
    }
    for ( i = 0; i < n_members; i++)
    {
        memset(colors, -1,sizeof(colors));
        gcp(i);
    }
    printf("%d\n",max);
    return 0;
}

int gcp(int v) {
    int  k, feasible;

    if (v == n_members) {
        if ( a > max )
            max = a;
        a = 0;
        return 1;
    }

    feasible = 1;
    /*CICLO DOS NOS ADJACENTES*/
    for (k = 0; k < n_members; k++) {
        if (adjacency[k][v] == 1) {
            if (colors[k] == cor) {
                feasible = 0;
                break;
            }
        }
    }
    if (feasible == 1) {
        colors[v] = cor;
        a++;
        if (gcp(v+1) == 1) {
            return 1;
        }
        colors[v] = -1;
    }
    if ( feasible == 0 )
    {
        if (gcp(v + 1) == 1 )
            return 1;
    }

    return 0;
}
