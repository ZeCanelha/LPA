#include <stdlib.h>
#include <stdio.h>
#include <string.h>


int can_fire(int ingoing_nodes[6][6], int state[6], int n_transactions, int n_places, int i);
void build_tree(int n_transactions, int n_places, int d_matrix[6][6],int trigger_matrix[4], int current[6],int init_state, int ingoing_nodes[6][6], int used_nodes[1000][6]);
void check_dominance( int state[6], int curr_state[1000][6], int n_places , int curr_pos, int new_state[6]);
int is_cycle( int current_state[6], int n_places , int used_nodes[1000][6], int curr_pos);


int main(int argc, char const *argv[])
{
    int n_places;
    int n_transactions;
    char input_reader[20];
    int i,j,k;
    char * aux;
    int trigger_matrix[4];
    int n1, n2, n3;

    scanf("%d %d",&n_places,&n_transactions);
    getchar();

    int used_nodes[1000][6];

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
        scanf("%d",&used_nodes[0][k]);
        printf("%d ", used_nodes[0][k]);
    }

    printf("\n");

    for (i = 1; i <= n_transactions; i++)
    {
        for (j = 1;  j <= n_places; j++)
        {
            d_matrix[i][j] = outgoing_nodes[i][j] - ingoing_nodes[i][j];
        }
    }

    build_tree(n_transactions,n_places,d_matrix,trigger_matrix,used_nodes[0],0, ingoing_nodes, used_nodes);

    return 0;
}

int can_fire( int ingoing_nodes[6][6] , int state[6], int n_transactions, int n_places, int i)
{
    int j;
    for ( j = 1; j <= n_places; j++ )
    {
        if( ingoing_nodes[i][j] > 0 )
        {
            if ( state[j] < ingoing_nodes[i][j] )
            {
                return 0;
            }
        }
    }
    return 1;
}


void build_tree(int n_transactions, int n_places, int d_matrix[6][6], int trigger_matrix[4],int current[6],int init_state, int ingoing_nodes[6][6], int used_nodes[1000][6] )
{
    int i,j,k;
    int sum = 0;
    int aux = 0;
    int new_state[6];
    int aux_state[6];

    for ( i = 1; i <= n_transactions; i++ )
    {
        if (can_fire(ingoing_nodes,current,n_transactions,n_places,i) == 1)
        {
            aux++;
            trigger_matrix[i] = 1;

            for ( j = 1; j <= n_places; j++ )
            {
                for ( k = 1; k <= n_transactions; k++ )
                {
                    sum += trigger_matrix[k] * d_matrix[k][j];
                }
                aux_state[j] = sum + current[j];

                sum = 0;
            }
            trigger_matrix[i] = 0;

            if ( aux < 2)
            {
                init_state++;
            }

            /* Verficar se é um estado dominate */
            check_dominance(aux_state,used_nodes,n_places,init_state,new_state);

            /* Imprimir */

            for ( j = 1;j <= n_places;j++)
            {
                if (used_nodes[init_state-1][j] == -1)
                {
                    new_state[j] = -1;
                }
            }

            for ( j = 0; j < init_state; j++ )
            {
                printf(" ");
            }

            for ( j = 1; j <= n_places; j++ )
            {
                if ( new_state[j] == -1)
                {
                    if ( j == n_places )
                        printf("w");
                    else
                        printf("w ");
                }
                else
                {
                    if ( j == n_places )
                        printf("%d", new_state[j]);
                    else
                        printf("%d ", new_state[j]);
                }
            }
            printf("\n");



            /* Verificar se é ciclo: caso não seja ,recursão. */


            if ( is_cycle(new_state,n_places,used_nodes,init_state) == 1 )
            {
                for ( j = 1; j  <= n_places; j++ )
                    used_nodes[init_state][j] = new_state[j];

                build_tree(n_transactions,n_places,d_matrix,trigger_matrix, aux_state, init_state, ingoing_nodes,used_nodes);

            }


        }
    }

}

void check_dominance( int state[6], int curr_state[1000][6], int n_places , int curr_pos, int new_state[6])
{
    int i, j,k;
    int flag = 0;
    int at_least = 0;
    int cond = 0;


    for ( i = 0; i < curr_pos; i++ )
    {
        for ( j = 1; j <= n_places; j++ )
        {
            new_state[j] = state[j];
            if ( curr_state[i][j] < state[j])
                at_least++;

            if ( curr_state[i][j] == state[j])
                flag++;
        }
        cond = at_least + flag;

        if ( at_least != 0 && cond == n_places )
        {
            for ( k = 1; k <= n_places; k++ )
            {
                if ( curr_state[i][k] < state[k])
                    new_state[k] = -1;
            }
            break;
        }
        else
        {
            flag = 0;
            at_least = 0;

        }
    }
}

int is_cycle( int current_state[6], int n_places , int used_nodes[1000][6] , int curr_pos)
{
    int i,j;
    int checker = 0;
    for ( i = 0 ; i < curr_pos; i++ )
    {
        for ( j = 1; j <= n_places; j++ )
        {
            if ( current_state[j] == used_nodes[i][j] )
                checker++;
        }
        if ( checker == n_places )
            return 0;

        else
            checker = 0;
    }

    return 1;

}
