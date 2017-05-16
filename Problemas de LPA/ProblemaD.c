#include <stdlib.h>
#include <stdio.h>
#include <string.h>



int main(int argc, char const *argv[])
{
    int n_places;
    int n_transactions;
    char input_reader[20];
    char * aux;
    int n1, n2, n3;

    /*
     *
     * Quando o ultimo numero for 2 corresponde ás ligações do nó a transição *
     * Quando o ultimo numero for 1 corresponde ás ligações da transição para o nó *
     *
    */

    scanf("%d %d",&n_places,&n_transactions);
    getchar();

    int ingoing_nodes[n_transactions][n_places];
    int outgoing_nodes[n_transactions][n_places];

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
                outgoing_nodes[n1][n2] = 1;
            }
            else
            {
                ingoing_nodes[n2][n1] = 1;
            }
        }
    }

    /* DEBUG: imprimir a matriz de "adjacencia" */
    int i,j;
    for ( i = 0; i < n_transactions; i++ )
    {
        printf("[");
        for ( j = 0; j < n_places; j++ )
        {
            printf(" %d ",ingoing_nodes[i][j]);
        }
        printf("]\n");
    }


    return 0;
}
