#include <iostream>
#include <stdlib.h>
#include <stdio.h>

#define C 20
#define V 10

int main(int argc, char const *argv[])
{
    int i,j,k;
    int n_cases;
    int n_vertices, n_cameras;
    float vertex[V][2];
    float camera[C][5];
    scanf ("%d",&n_cases);

    for ( i = 0; i < n_cases; i++ )
    {
        scanf("%d %d",&n_vertices, &n_cameras);

        for ( j = 0; j < n_vertices; j++)
        {
            scanf("%f %f",&vertex[i][0],&vertex[i][1]);
        }
        for ( k = 0; k < n_cameras; k++ )
        {
            scanf("%f %f %f %f %f",&camera[i][0],&camera[i][1],&camera[i][2],&camera[i][3],&camera[i][4]);
        }
    }

    return 0;
}
