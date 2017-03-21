#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int n_operations = 0;
long int budget = 0;
double probabilities[401];
long int costs[401];


double myPow(double a, long int b);
long int sum( long int j);
double product(long int j);

int main(int argc, char const *argv[])
{
    long int i, j, b;
    double tmp;
    scanf("%d",&n_operations);

    for (i = 1; i <= n_operations; i++) {
        scanf("%lf %ld",&probabilities[i],&costs[i]);
    }

    scanf("%ld",&budget);


    double dp_matrix[budget+1][n_operations+1];
    long int redundantCopies[n_operations+1];

    if (n_operations != 0) {
        for (j = 1; j <= n_operations; j++) {
            for (b = 0; b <= (sum(j)-1); b++) {
                dp_matrix[b][j] = 0;
            }
            dp_matrix[sum(j)][j] = product(j);
            redundantCopies[j] = 1;
        }
        if (budget < sum(n_operations)) {
            return 0;
        }
        for (j = 2; j <= n_operations; j++) {
            dp_matrix[budget][j] = product(j);

            for (b = (sum(j-1) + 1); b <= (budget - costs[j]); b++) {
                tmp = dp_matrix[b][j-1]*(1 - myPow((1 - probabilities[j]), (budget-b)/costs[j]));
                if (tmp > dp_matrix[budget][j]) {
                    dp_matrix[budget][j] = tmp;
                    redundantCopies[j] = (budget-b)/costs[j];
                }
            }

        }
    }

    /*printf("-------------------MATRIZ DINAMICA---------------\n" );
    for (i = 1; i <= n_operations; i++) {
        for ( j = 1; j <= budget; j++) {
            printf("%.32lf ", dp_matrix[i][j]);
        }
        printf("\n" );
    }*/

    printf("-------------------NUMERO DE MAQUINAS PARA CADA SETOR ----------\n" );
    for (i = 1; i <= n_operations; i++) {
        printf("%ld ", redundantCopies[i]);
    }

    printf("\n" );
    printf("%.12lf\n",dp_matrix[budget][n_operations]);
    return 0;
}

double myPow(double a, long int b){
    double total = 1;
    int l;
    for ( l = 1; l <= b; l++) {
        total *= a;
    }

    return total;
}

long int sum(long int j){
    long int total = 0, i;
    for (i = 1; i <= j; i++) {
        total += costs[i];
    }

    return total;
}

double product(long int j){
    double total = 1;
    int i;
    for (i = 1; i <= j; i++) {
        total *= probabilities[i];
    }
    return total;
}
