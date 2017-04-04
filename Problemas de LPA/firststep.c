#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#define PRECISION 2.220446e-16

/*GLOBAL VARIABLES*/
long int n_operations = 0;
long int budget = 0;
long int initialBill = 0;
int impossible = 0;
double failureProb;

/*PROTOTYPES*/
int compareDoubles(double a, double b);
long double max(long double a, long double b);
long double myPow(long double a, long int b);
void myRecursion(long double dp[n_operations][budget+1],double value[],long int weight[], int i,int line, int array[]);

/*MAIN FUNCTION*/
int main(){
    double probabilities[401];
    long int costs[401];
    int f, j;
    long int i,z;

    scanf("%ld",&n_operations);

    for (f = 1; f < n_operations+1; f++){
        scanf("%lf %ld",&probabilities[f],&costs[f]);
        initialBill += costs[f];
        if (probabilities[f] == 0) {
            impossible = 1;
        }
    }

    scanf("%ld",&budget);

    budget = budget - initialBill;

    int redundantMachines[n_operations+1];
    long double dp_matrix[n_operations][budget+1];

    if (n_operations != 0 && impossible == 0) {

        dp_matrix[0][0] = probabilities[1];
        /*initializing first row*/
        for(i = 1;i <= budget; ++i){
            dp_matrix[0][i] = (1 - myPow(1-probabilities[1],i/costs[1] + 1));
        }
        /*initializing first column*/
        for(j = 1; j < n_operations; ++j){
            dp_matrix[j][0] = probabilities[j+1] * dp_matrix[j-1][0];
        }

        /*Filling the dynamic Table*/
        for (i = 1; i < n_operations; ++i){
            for (j = 1; j <= budget; ++j){
                dp_matrix[i][j] = dp_matrix[i-1][j] * probabilities[i+1];
                failureProb = 1 - probabilities[i+1];

                for(z = 1; z <= j/costs[i+1]; z++){
                    failureProb *= (1-probabilities[i+1]);
                    dp_matrix[i][j] = max(dp_matrix[i][j], dp_matrix[i-1][j - (z * costs[i+1])] * (1 - failureProb));
                }
            }
        }

        printf("%.12Lf\n",dp_matrix[n_operations-1][budget]);

        /*calculating redundant machines*/
        myRecursion(dp_matrix, probabilities, costs, n_operations-1, budget, redundantMachines);
    }

    return 0;
}


/*AUXILIAR METHODS*/
void myRecursion(long double dp[n_operations][budget+1],double value[],long int weight[],int i,int line, int array[]){
    int a,k;
    int price;
    double probz;

    if(i == 0){
        array[1] = (line/weight[1])+1;
        for(a=1; a<n_operations+1; a++){
            printf("%d%s", array[a], a!=n_operations-1?" ":"");
        }

        printf("\n");
        return;
    }

    probz = (1-value[i+1]);

    for(k=1;k<line/weight[i+1];k++){

        probz *= (1-value[i+1]);

        if(compareDoubles(dp[i][line] , dp[i-1][line - ((k) * weight[i+1])] * (1 - probz))){

            price = (weight[i+1] * k);

            array[i] = k+1;

            myRecursion(dp,value,weight,i-1,line-price, array);
        }
    }
}


long double max(long double a, long double b) {
    return (a > b)? a : b;
}

int compareDoubles(double a, double b){
    return fabs(a - b) < PRECISION;
}

long double myPow(long double a, long int b){
    long double total = 1;
    int l;
    for ( l = 0; l < b; l++) {
        total *= a;
    }

    return total;
}
