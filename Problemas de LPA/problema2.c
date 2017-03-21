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
long int myPow(long int a, long int b);
double max(double a, double b) { return (a > b)? a : b; }

int main(int argc, char const *argv[])
{
    long int i, j, r;
    scanf("%d",&n_operations);

    for (i = 1; i < n_operations +1; i++) {
        scanf("%lf %ld",&probabilities[i],&costs[i]);
        initialBill += costs[i];
    }

    scanf("%ld",&budget);

    budget = budget - initialBill;

    double dp_matrix[n_operations+1][budget+1];
    if (n_operations != 0 || impossible != 0) {

    }

    /*for (i = 0; i < n_operations +1; i++) {
        for ( j = 0; j < budget + 1; j++) {
            printf("%lf ", dp_matrix[i][j]);
        }
        printf("\n" );
    }*/

    printf("%.12lf\n",dp_matrix[i-1][j-1]);
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

/*long int myPow(long int a, long int b){
    int total = 1, l;
    for ( l = 0; l < b; l++) {
        total *= a;
    }

    return total;
}*/
