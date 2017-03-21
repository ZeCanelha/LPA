#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int n_operations = 0;
int impossible = 0;
long int budget = 0;
double probabilities[401];
long int costs[401];
int cheapest_machine = 10000000;
long int initialBill = 0;

long int calculaMax(long int i, long int j, double dp_matrix[n_operations+1][budget+1]);
double myPow(double a, long int b);
long int sum( int j);
double product(int j);
double max(double a, double b) { return (a > b)? a : b; }

int main(int argc, char const *argv[])
{
    long int i, j, b;
    double tmp;
    scanf("%d",&n_operations);

    for (i = 1; i < n_operations +1; i++) {
        scanf("%lf %ld",&probabilities[i],&costs[i]);
        /*initialBill += costs[i];*/
    }

    scanf("%ld",&budget);

    /*budget = budget - initialBill;*/

    double dp_matrix[budget+1][n_operations+1];
    long int redundantCopies[n_operations+1];

    if (n_operations != 0 || impossible != 0) {
        for (j = 1; j <= n_operations; j++) {
            for (b = 0; b < sum(j)-1; b++) {
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
            for (b = sum(j-1) + 1; b <= budget - costs[j]; b++) {
                tmp = dp_matrix[b][j-1]*myPow((1 - (1 - probabilities[j])), (budget-b)/costs[j]);
                if (tmp > dp_matrix[budget][j]) {
                    dp_matrix[budget][j] = tmp;
                    redundantCopies[j] = (budget-b)/costs[j];
                }
            }
        }
    }
    printf("-------------------MATRIZ DINAMICA---------------\n" );
    for (i = 1; i <= n_operations; i++) {
        for ( j = 1; j <= budget; j++) {
            printf("%.12lf ", dp_matrix[i][j]);
        }
        printf("\n" );
    }

    printf("-------------------NUMERO DE MAQUINAS PARA CADA SETOR ----------\n" );
    for (i = 1; i < n_operations; i++) {
        printf("%ld ", redundantCopies[i]);
    }
    printf("%.12lf\n",dp_matrix[budget][n_operations]);
    return 0;
}

/*long int calculaMax(long int i, long int j, double dp_matrix[n_operations+1][budget+1]) {
    int z, maximo = 0;
    for (z = 1; z < i/costs[j]; z++) {
            if (maximo < dp_matrix[i][j-1] * (1-myPow(1 - probabilities[j], z))){
                maximo = dp_matrix[i][j-1] * (1-myPow(1 - probabilities[j], z));
            }

    }
    return maximo;
}*/

double myPow(double a, long int b){
    int total = 1, l;
    for ( l = 0; l < b; l++) {
        total *= a;
    }

    return total;
}

long int sum( int j){
    int total = 0, i;
    for (i = 1; i <= j; i++) {
        total += costs[i];
    }

    return total;
}

double product(int j){
    double total = 1;
    int i;
    for (i = 1; i <= j; i++) {
        total *= probabilities[i];
    }
    return total;
}
