#include <stdlib.h>
#include <stdio.h>
#include <string.h>



int main(int argc, char const *argv[])
{
    int n_places;
    int n_transactions;
    char input_reader[20];
    int k;

    char * aux;
    int n1, n2, n3;

    /* TODO:
     *
     * Quando o ultimo numero for 2 corresponde ás ligações do nó a transição *
     * Quando o ultimo numero for 1 corresponde ás ligações da transição para o nó *
     * Verificar se é necessario uma matriz para guardar os diferentes estados para ver os ciclos
     *
    */

    scanf("%d %d",&n_places,&n_transactions);
    getchar();

    int curr_state[n_places];

    int ingoing_nodes[n_transactions+1][n_places+1];
    int outgoing_nodes[n_transactions+1][n_places+1];

    memset(&ingoing_nodes,0,sizeof(ingoing_nodes));
    memset(&outgoing_nodes,0,sizeof(outgoing_nodes));

    while(1)
    {
        /* fgets lê o \n */
        fgets(input_reader,20,stdin);

        if ( strcmp(input_reader,"STATE\n") == 0 )
            break;

        else
        {
            aux = strtok(input_reader," ");
            n1 = atoi(aux);
            aux = strtok(NULL," ");
            n2 = atoi(aux);
            aux = strtok(NULL," ");
            n3 = atoi(aux);

            if ( n3 == 1 )
            {
                outgoing_nodes[n1][n2] += 1;
            }
            else
            {
                ingoing_nodes[n1][n2] += 1;
            }
        }
    }

    for( k = 0; k < n_places; k++ )
    {
        scanf("%d",&curr_state[k]);
    }



    /* DEBUG: imprimir a matriz de "adjacencia"*/

    int i,j;
    for ( i = 1; i <= n_transactions; i++ )
    {
        printf("[");
        for ( j = 1; j <= n_places; j++ )
        {
            printf(" %d ",outgoing_nodes[i][j]);
        }
        printf("]\n");
    }


    return 0;
}
