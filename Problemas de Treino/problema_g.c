#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int n = 0;
int m = 0;

int towerA[101];
int towerB[101];

int dynamic_matrix[101][101];

int max_value(int a, int b) { return (a > b)? a : b; }
int construct_tower ();

int main(int argc, char const *argv[])
{
    int i, j;
    int count = 0;
    int result = 0;
    while(1)
    {
        scanf("%d %d",&n, &m );

        if ( n == 0 && m == 0 )
            break;

        memset(dynamic_matrix, -1 , sizeof(dynamic_matrix));

        for ( i = 0; i < n; i++ )
        {
            scanf("%d", &towerA[i]);
        }

        for ( j = 0; j < m; j++ )
        {
            scanf("%d", &towerB[j]);
        }
        count++;
        result = construct_tower();
        printf("Twin Towers #%d\nNumber of Tiles : %d\n\n",count,result);

    }

    return 0;
}

int construct_tower()
{
    int i, j;
    for ( i = 0; i <= n; i++ )
    {
        dynamic_matrix[i][0] = 0;
    }
    for ( j = 0; j <= m; j++ )
    {
        dynamic_matrix[0][j] = 0;
    }

    for ( i = 1; i <= n; i++ )
    {
        for ( j = 1; j <= m; j++ )
        {
            if ( towerA[i - 1] == towerB[j - 1] )
            {
                dynamic_matrix[i][j] = dynamic_matrix[i - 1][j - 1] + 1;
            }
            else
            {
                dynamic_matrix[i][j] = max_value(dynamic_matrix[i-1][j],dynamic_matrix[i][j -1]);
            }
        }
    }

    return dynamic_matrix[n][m];

}
