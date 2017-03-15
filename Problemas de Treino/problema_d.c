#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int count = 0;
int can_run = 1;
int dynamic_matrix[26][100];
int moedas[26];
int quantia = 0;
int n_moedas = 0;

void subset ();


int main(int argc, char const *argv[]) {

    int test_cases;
    int i,j,k;


    scanf("%d",&test_cases);

    for ( k = 0; k < test_cases; k++ )
    {
        scanf("%d %d", &quantia, &n_moedas);

        memset(dynamic_matrix, 0 , sizeof(dynamic_matrix));
        moedas[0] = 0;
        for ( j = 1; j < n_moedas + 1; j++ )
        {
            scanf("%d",&moedas[j]);
        }

        subset();

        for ( i = 0; i < n_moedas + 1; i++ )
        {
            printf("[ ");
            for ( j = 0; j < quantia + 1; j++ )
            {
                printf(" %d ", dynamic_matrix[i][j]);
            }
            printf("]\n");
        }
    }

    return 0;
}


void subset ()
{

    int i,j,z;
    for ( i = 0; i < n_moedas + 1; i++ )
    {
        dynamic_matrix[i][0] = 1;
    }

    for ( j = 1; j < quantia + 1; j++ )
    {
        dynamic_matrix[0][j] = 0;
    }

    for ( i = 1; i <= n_moedas; i++ )
    {
        for ( j = 1; j <= quantia; j++ )
        {
            /* Se berrar penso que seja só alterar a moedas[0] e aqui começar em i - 1 */
            if ( moedas[i] > j )
            {
                dynamic_matrix[i][j] = dynamic_matrix[i - 1][j];
            }
            else
            {
                /* Nãp usar a moeda */
                if ( dynamic_matrix[i - 1][j] == 1 )
                {
                    dynamic_matrix[i][j] = dynamic_matrix[i - 1][j];
                }
                /* Usar a moeda */
                if ( dynamic_matrix[i - 1][j-moedas[i]] == 1 )
                {
                    dynamic_matrix[i][j] = dynamic_matrix[i - 1][j - moedas[i]];
                }
            }
        }
    }
    /* Se em cima for falso, a moeda i foi usada */
    can_run = 0;
    int aux = j -1;
    for (z = i - 1; z > 0; z--)
    {
        if ( dynamic_matrix[z -1][aux] == 1  )
        {
            continue;
        }
        if ( dynamic_matrix[z -1][aux] == 0 )
        {
            printf("Usei %d\n", moedas[z]);
            aux = aux - moedas[z];
            /* moeda usada neste ciclo , cortada no prox */
        }
    }
}
