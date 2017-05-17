#include <stdlib.h>
#include <stdio.h>
#include <string.h>


int * can_fire(int ingoing_nodes[5][5], int state[5], int n_transactions, int n_places);


int main(int argc, char const *argv[])
{
    int n_places;
    int n_transactions;
    char input_reader[20];
    int k;
    int * trigger_matrix;
    char * aux;
    int n1, n2, n3;

    int i,j;

    /* TODO:
     *
     * Quando o ultimo numero for 2 corresponde ás ligações do nó a transição *
     * Quando o ultimo numero for 1 corresponde ás ligações da transição para o nó *
     * Função para calcular as transições que podem ser disparadas
     *
    */

    scanf("%d %d",&n_places,&n_transactions);
    getchar();

    int curr_state[50][n_places];

    int ingoing_nodes[n_transactions+1][n_places+1];
    int outgoing_nodes[n_transactions+1][n_places+1];
    int d_matrix[n_transactions + 1][n_places+1];

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
                ingoing_nodes[n2][n1] += 1;
            }
        }
    }

    for( k = 0; k < n_places; k++ )
    {
        scanf("%d",&curr_state[0][k]);
    }

    for (i = 1; i <= n_transactions; i++) {
      for (j = 1;  j <= n_places; j++) {
        d_matrix[i][j] = ingoing_nodes[i][j] - outgoing_nodes[i][j];
      }
    }

    for ( i = 1; i <= n_transactions; i++ )
    {
        printf("[");
        for ( j = 1; j <= n_places; j++ )
        {
            printf(" %d ",ingoing_nodes[i][j]);
        }
        printf("]\n");
    }



    trigger_matrix = can_fire(ingoing_nodes,curr_state[0],n_transactions,n_places);
    printf("[");
    for ( i = 1; i <= n_transactions; i++)
        printf(" %d ", *(trigger_matrix+i) );
    printf("]\n");



    return 0;
}

int * can_fire( int ingoing_nodes[5][5] , int state[5], int n_transactions, int n_places )
{
    int i,j;
    int * triggers = ( int *) malloc (sizeof(n_transactions + 1));
    int trigger = 0;
    for ( i = 1; i <= n_transactions; i++ )
    {
        for ( j = 1; j <= n_places; j++ )
        {
            if( ingoing_nodes[i][j] > 0 )
            {
                if ( state[j-1] >= ingoing_nodes[i][j] )
                {
                    //printf("State de p%d -> Arcos: %d\n",j,ingoing_nodes[i][j]);
                    trigger = 1;
                }
                else
                    trigger = 0;
            }
        }
        *(triggers+i) = trigger;
        trigger = 0;
    }

    return triggers;
}


/* DEBUG: imprimir a matriz de "adjacencia"

int i,j;
for ( i = 1; i <= n_transactions; i++ )
{
    printf("[");
    for ( j = 1; j <= n_places; j++ )
    {
        printf(" %d ",ingoing_nodes[i][j]);
    }
    printf("]\n");
}

*/
