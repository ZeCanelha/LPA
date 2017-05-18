#include <stdlib.h>
#include <stdio.h>
#include <string.h>


int can_fire(int ingoing_nodes[6][6], int state[6], int n_transactions, int n_places, int i);
int build_tree(int n_transactions, int n_places, int d_matrix[6][6],int trigger_matrix[4], int curr_state[100][6],int init_state, int ingoing_nodes[6][6] );


int main(int argc, char const *argv[])
{
    int n_places;
    int n_transactions;
    char input_reader[20];
    int i,j,k;
    char * aux;
    int trigger_matrix[4];
    int n1, n2, n3;

    /* TODO:
     *
     * Quando o ultimo numero for 2 corresponde ás ligações do nó a transição *
     * Quando o ultimo numero for 1 corresponde ás ligações da transição para o nó *
     * Função para calcular as transições que podem ser disparadas
     * A matrix de trigger tem q ser calculada em separado
     *
    */

    scanf("%d %d",&n_places,&n_transactions);
    getchar();

    int curr_state[100][6];

    int ingoing_nodes[6][6];
    int outgoing_nodes[6][6];
    int d_matrix[6][6];

    memset(&ingoing_nodes,0,sizeof(ingoing_nodes));
    memset(&outgoing_nodes,0,sizeof(outgoing_nodes));
    memset(&trigger_matrix,0,sizeof(trigger_matrix));

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

    for( k = 1; k <= n_places; k++ )
    {
        scanf("%d",&curr_state[0][k]);
    }

    for (i = 1; i <= n_transactions; i++) {
      for (j = 1;  j <= n_places; j++) {
        d_matrix[i][j] = outgoing_nodes[i][j] - ingoing_nodes[i][j];
      }
    }

    build_tree(n_transactions,n_places,d_matrix,trigger_matrix,curr_state,0, ingoing_nodes);


    return 0;
}

int can_fire( int ingoing_nodes[6][6] , int state[6], int n_transactions, int n_places, int i)
{
    int j;
    int trigger = 0;
    for ( j = 1; j <= n_places; j++ )
    {

        if( ingoing_nodes[i][j] > 0 )
        {
            if ( state[j] >= ingoing_nodes[i][j] )
            {
                trigger = 1;
            }
            else
            {
                trigger = 0;
            }
        }
    }
    return trigger;
}


int build_tree(int n_transactions, int n_places, int d_matrix[6][6], int trigger_matrix[4],int curr_state[100][6],int init_state, int ingoing_nodes[6][6] )
{
    int i,j,k;
    int sum = 0;
    for ( i = 1; i <= n_transactions; i++ )
    {
        if (can_fire(ingoing_nodes,curr_state[init_state],n_transactions,n_places,i) == 1)
        {
            printf(" %d ", i);
            trigger_matrix[i] = 1;
            printf("State\n[");
            for ( j = 1; j <= n_places; j++ )
            {
                for ( k = 1; k <= n_transactions; k++ )
                {
                    sum += trigger_matrix[k] * d_matrix[k][j];
                }
                curr_state[init_state+1][j] = sum + curr_state[init_state][j];
                printf(" %d ",curr_state[init_state+1][j]);
                sum = 0;
            }
            printf("]\n");

            // Se for ciclo infinito n chamo build_tree || se não originar chamo;
            trigger_matrix[i] = 0;
            build_tree(n_transactions,n_places,d_matrix,trigger_matrix,curr_state,init_state+1, ingoing_nodes);



        }
    }

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

printf("[");
for ( i = 1; i <= n_transactions; i++)
    printf(" %d ", *(trigger_matrix+i) );
printf("]\n");
*/
