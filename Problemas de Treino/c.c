#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int cord_lobos[101][2];
int n_lobos;
int heigth;
int width;
long int n_paths = 0;
long int dynamic_matrix[101][101];

long int countPaths(int x, int y){

    int i,j;
    long int C1 = 0;
    long int C2 = 0;
    int right = 1;
    int up = 1;

    if (dynamic_matrix[x][y] != -1) {

        return dynamic_matrix[x][y];
    }

    if ( x == 0 && y != heigth )
    {

        for ( i = 0; i < n_lobos; i++) {
            for( j = y; j < heigth; j++)
            {
                if (cord_lobos[i][1] == j  && cord_lobos[i][0] == x ) {

                    return 0;
                }
            }

        }
        return 1;
    }
    if ( x != 0 && y == heigth )
    {
        for ( i = 0; i < n_lobos; i++) {
            for ( j = x; j > 0; j-- )
            {
                if (cord_lobos[i][0] == j && cord_lobos[i][1] == y) {
                    return 0;
                }
            }
        }
        return 1;
    }

    if (n_lobos == 0) {
        C2 = countPaths(x, y+1);
        C1 = countPaths(x-1, y);

    } else {
        for ( i = 0; i < n_lobos; i++) {

            if (cord_lobos[i][0] == (x - 1) && cord_lobos[i][1] == y) {

                up = 0;
            }
            if (cord_lobos[i][1] == (y + 1)  && cord_lobos[i][0] == x ) {

                right = 0;
            }
        }

        if (up)
            C1 = countPaths(x-1, y);
        if (right)
            C2 = countPaths(x, y + 1);
    }
    dynamic_matrix[x][y] = C1 + C2;
    return dynamic_matrix[x][y];
}

int main() {

    int i;
    int x , y;
    while(1) {
        scanf("%d %d",&width,&heigth);
        if ( width == 0 && heigth == 0) {
            break;
        }
        scanf("%d",&n_lobos);
        for ( i = 0; i < n_lobos; i++ ) {
            scanf("%d %d",&x,&y);
            cord_lobos[i][0] = width - x;
            cord_lobos[i][1] = y;
        }

        memset(dynamic_matrix, -1, sizeof(dynamic_matrix));

        n_paths = countPaths(width, 0);

        if ( n_paths > 1 ) {
            printf("There are %ld paths from Little Red Riding Hood's house to her grandmother's house.\n",n_paths);
        } else if ( n_paths == 1 ) {
            printf("There is one path from Little Red Riding Hood's house to her grandmother's house.\n");
        } else {
            printf("There is no path.\n");
        }


    }


    return 0;
}
