#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int n_operations = 0;
double max_prob = 0;
double budget = 0;
double dp_matrix[401][401];
double machines[401][2];


int main(int argc, char const *argv[])
{
    int i;
    scanf("%d",&n_operations);

    memset(machines, -1,sizeof(machines));
    memset(dp_matrix, 0,sizeof(dp_matrix));

    for (i = 0; i < n_operations; i++) {
        scanf("%lf %lf",&machines[i][0],&machines[i][1]);
    }

    scanf("%lf",&budget);

    printf("%lf\n",max_prob);
    return 0;
}
