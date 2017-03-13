#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>


double best_distance = 10000000;
int n_nos = 0;

/* At most , existem 12 lugares para visitar */

int visited[13];
double dist_matrix[13][13];
int coord[13][2];
int n;


int shortest_path(int , double, int );
int dist();
int main(int argc, char const *argv[])
{
    int i,j;

    scanf("%d",&n_nos);
    if ( n_nos == 0)
    {
        printf("0.000\n");
    } else {
        for ( i = 0; i < n_nos; i++ ) {
            scanf("%d %d",&coord[i][0],&coord[i][1]);
        }

        /* Colocar os lugares visitados a zero */
        memset(dist_matrix, 0 , sizeof(dist_matrix));
        memset(visited, 0, sizeof(visited));
        dist();
        for ( j = 0; j < n_nos; j++ ) {
            visited[j] = 1;
            shortest_path(j,0, 1);
            visited[j] = 0;
        }

        printf("%.3f\n",best_distance);
    }


    return 0;
}


int shortest_path( int i , double len, int n )
{
    int j;
    if ( len >= best_distance )
        return 1;

    if ( n == n_nos && len < best_distance )
    {
        best_distance = len;
        return 1;
    }

    for ( j = 0; j < n_nos; j++ )
    {
        if (visited[j] == 0 ) {
            visited[j] = 1;
            n++;
            shortest_path(j, len + dist_matrix[i][j], n);
            n--;
            visited[j] = 0;
        }
    }
    return 1;
}

int dist()
{
    int k ,  z;
    for ( k = 0; k < n_nos; k++) {
        for ( z = 0; z < n_nos; z++) {
            dist_matrix[k][z] = (double)sqrt( pow((double)(coord[k][0] - coord[z][0]),2) + pow((double)(coord[k][1] - coord[z][1]),2) );
        }
    }
    return 0;
}
