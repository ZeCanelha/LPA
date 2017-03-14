#include <stdio.h>
#include <stdlib.h>
#include <string.h>



int main(int argc, char const *argv[]) {

    int test_cases;
    int i,j,k;
    int quantia;
    int n_moedas;
    int usa_moeda;
    int n_usa_moeda;

    scanf("%d",&test_cases);

    for ( j = 0; j < test_cases; j++ )
    {
        scanf("%d %d",&quantia,&n_moedas );
        int dynamic_matrix[n_moedas][quantia];
        memset(dynamic_matrix, 0, sizeof(dynamic_matrix));
        int moedas[n_moedas];
        for ( i = 0; i < n_moedas; i++ )
        {
            scanf("%d ", &moedas[i]);
        }

        for ( i = 0; i < n_moedas; i++ )
        {
            dynamic_matrix[i][0] = 0;
        }
        for ( i = 0; i < quantia; i++ )
        {
            dynamic_matrix[0][i] = 0;
        }

        for ( i = 1; i < n_moedas; i++ )
        {
            for ( k = 1; k < quantia; k++ )
            {
                /* Se não der , tentar com i -1 , problema do algortimo anterior */

                if ( moedas[i] > k  )
                {
                    dynamic_matrix[i][k] = dynamic_matrix[i-1][k];
                    n_usa_moeda = dynamic_matrix[i-1][k];
                }
                else
                {
                    usa_moeda = 1 + dynamic_matrix[i][j - moedas[i]];
                    dynamic_matrix[i][k] = usa_moeda + n_usa_moeda;
                }
            }
        }

        printf(" solution: %d\n", dynamic_matrix[n_moedas][quantia-1]);

    }

    return 0;
}
