#include <stdio.h>
#include <stdlib.h>

int num_obejcts = 0;
int max_objects = 0;
int max_amount = 0;
int object_price[600];
int object_weight[600];

int main(int argc, char const *argv[])
{
    int i,j;
    scanf("%d", &num_obejcts);
    scanf("%d",&max_objects);
    scanf("%d",&max_amount);
    for ( i = 0; i < num_obejcts; i++ )
    {
        scanf ("%d %d", &object_price[i], &object_weight[i]);
    }

    int dynamic_matrix[num_obejcts][max_amount];
    memset(dynamic_matrix, - 1 , sizeof(dynamic_matrix));

    for ( j = 1; j < max_amount; j++ )
    {
        dynamic_matrix[0][j] = 0;
    }

    for ( i = 0; i < num_obejcts; i++ )
    {
        dynamic_matrix[i][0] = 0;
    }
    return 0;
}
