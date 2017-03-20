#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int n_operations = 0;
long int budget = 0;
double probabilities[401];
long int costs[401];
int cheapest_machine = 10000000;
long int initialBill = 0;

long int myPow(long int a, long int b);
double max(double a, double b) { return (a > b)? a : b; }
int main(int argc, char const *argv[])
{
    long int i, j, z;
    scanf("%d",&n_operations);

    for (i = 1; i < n_operations +1; i++) {
        scanf("%lf %ld",&probabilities[i],&costs[i]);
        initialBill += costs[i];
    }

    scanf("%ld",&budget);

    budget = budget - initialBill;

    double dp_matrix[n_operations+1][budget+1];

    /*initializing first column and row*/
    for (i = 0; i < n_operations + 1; i++) {
        dp_matrix[i][0] = probabilities[i];
    }

    for (i = 0; i < budget+1; i++) {
        dp_matrix[0][i] = 1;
    }
    if (n_operations != 0) {
        for ( i = 1; i < n_operations + 1; i++) {
            for ( j = 1; j < budget + 1; j++) {
                for (z = 1; z < j/costs[i]; z++) {
                        dp_matrix[i][j] = max(dp_matrix[i][j], dp_matrix[i-1][j - z*costs[i]] * myPow(1 - probabilities[i], z));
                }
            }
        }
    }

    for (i = 0; i < n_operations +1; i++) {
        for ( j = 0; j < budget + 1; j++) {
            printf("%lf ", dp_matrix[i][j]);
        }
        printf("\n" );
    }

    printf("%.12lf\n",dp_matrix[i-1][j-1]);
    return 0;
}

long int myPow(long int a, long int b){
    int total = 1, i;
    for ( i = 0; i < b; i++) {
        total *= a;
    }

    return total;
}
