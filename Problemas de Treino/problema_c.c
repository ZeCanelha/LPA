#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int cord_lobos[100][2];
int n_lobos;
int heigth;
int width, i;
int n_paths = 0;
int dynamic_matrix[5][5];

int countPaths(int x, int y){

    int C1 = 0;
    int C2 = 0, k;

    if (dynamic_matrix[x][y] != -1) {
        printf("CONA BOA\n" );
        return dynamic_matrix[x][y];
    }

    if (x == 0 || y == heigth+1) {
        return 1;
    }

    if (n_lobos == 0) {
        C1 = countPaths(x+1, y);
        C2 = countPaths(x, y-1);
    } else {
        for ( i = 0; i < n_lobos; i++) {

            if (cord_lobos[i][0] != x+1) {
                C1 = countPaths(x+1, y);
                break;
            }

            if (cord_lobos[i][1] != y-1) {
                C2 = countPaths(x, y-1);
                break;
            }

        }
    }
    printf("CONA\n");

    dynamic_matrix[x][y] = C1 + C2;

    for (k = 0; k < width+1; k++) {
        printf("%d %d\n", dynamic_matrix[k][0],  dynamic_matrix[k][1]);
    }
    printf("\n");

    return dynamic_matrix[x][y];
}

int main(int argc, char const *argv[]) {

    int i;

    while(1) {
        scanf("%d %d",&width,&heigth);
        if ( width == 0 && heigth == 0) {
            break;
        }


        scanf("%d",&n_lobos);
        int cord_lobos[n_lobos][2];

        for ( i = 0; i < n_lobos; i++ ) {
            scanf("%d %d",&cord_lobos[i][0],&cord_lobos[i][1]);
        }

        memset(dynamic_matrix, -1, sizeof(dynamic_matrix));

        n_paths = countPaths(width, 0);



        if ( n_paths > 1 ) {
            printf("There are %d paths from Little Red Riding Hood's house to her grandmother's house.\n",n_paths);
        } else if ( n_paths == 1 ) {
            printf("There is one path from Little Red Riding Hood's house to her grandmother's house.\n");
        } else {
            printf("There is no path.\n");
        }


    }




    return 0;
}
