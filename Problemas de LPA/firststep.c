#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

int n_operations = 0;
long int budget = 0;
double probabilities[401];
long int costs[401];
long int initialBill = 0;
int impossible = 0;

long int calculaMax(long int i, long int j, double dp_matrix[n_operations+1][budget+1]);
double myPow(double a, long int b);
double[] max(double a, double b) {return (a > b)? a : b; }

int main(int argc, char const *argv[])
{
    double prob;
    long int i, j, k;
    double temp = 0;
    scanf("%d",&n_operations);


    for (i = 1; i < n_operations +1; i++) {
        scanf("%lf %ld",&probabilities[i],&costs[i]);
        initialBill += costs[i];
        if (probabilities[i] == 0) {
            impossible = 1;
        }
    }

    scanf("%ld",&budget);

    budget = budget - initialBill;

    double dp_matrix[n_operations][budget + 1];
    dp_matrix[0][0] = probabilities[1];
    if (n_operations != 0 && impossible == 0) {

        for(i = 1; i <= budget; i++)
        {
            temp = i/costs[1];
            dp_matrix[0][i] = (1 - myPow(1- probabilities[1],temp+1));
        }

        for( j=1; j < n_operations; j++){
            dp_matrix[j][0] = probabilities[j+1] * dp_matrix[j-1][0];
        }


        for ( i = 1; i < n_operations; i++) {

            for ( j = 1; j <=budget; j++)
            {
                /* Calcular a pobabilidade de sucesso de uma maquina pelas restantes */
                dp_matrix[i][j] = dp_matrix[i-1][j] * probabilities[i+1];
                prob = 1 - probabilities[i + 1];

                for ( k = 1; k <= (j/costs[i+1]); k++ ) {
                    prob *= (1 - probabilities[i + 1]);
                    dp_matrix [i][j] = max(dp_matrix [i][j],dp_matrix[i-1][j-costs[i+1]*k] * (1 - prob));
                    
                }
                printf("OLHA O I e o K: %ld %ld\n", i, k);
            }
        }

    }
    printf("-------------------MATRIZ DINAMICA---------------\n" );
    for (i = 0; i < n_operations; i++) {
        for ( j = 0; j <= budget; j++) {
            printf("%.12lf ", dp_matrix[i][j]);
        }
        printf("\n" );
    }

    printf("%.12lf\n",dp_matrix[n_operations-1][budget]);
    return 0;
}

double myPow(double a, long int b){
    double total = 1;
    int l;
    for ( l = 0; l < b; l++) {
        total *= a;
    }

    return total;
}
