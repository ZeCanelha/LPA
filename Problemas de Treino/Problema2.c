#include <stdlib.h>
#include <stdio.h>


int coin_sack( int , int , int, int , int);

int max_geral = 0;
int matrix[100];

int main(int argc, char const *argv[]) {

    int n_problems;
    int n_coins;
    int soma = 0;
    int i , j;
    int ret_val = 0;
    scanf("%d",&n_problems);

    for ( i = 0; i < n_problems; i++ )
    {
        scanf("%d",&n_coins);

        for ( j = 0; j < n_coins; j++ )
        {
            if ( j == (n_coins -1) )
            {
                scanf("%d",&matrix[j]);
            }
            else
                scanf("%d ",&matrix[j]);
            soma += matrix[j];
        }

        ret_val = coin_sack(0,0,n_coins,0,soma/2);
        printf("%d\n",ret_val);
    }

    return 0;
}

int coin_sack( int i , int j , int n_coins , int val, int soma )
{
    /*
     * Verifica todas as somas possiveis até encontrar o valor
     * Se o valor for par dá pra divir sempre (?)
     * Se não for par encontrar a maior sequencia
     * TODO: MAL IMPLEMENTADADA A SOMA
     */
     printf("oi\n");
     if ( val == soma )
     {
         printf("Encontrei solução: %d\n", val);
         return val;
     }
    int k;
    if ( i == n_coins -1  &&  j == n_coins -1 )
    {
        return (soma - val);
    }

    if (  j == n_coins -1  )
    {
        return coin_sack(i+1,0,n_coins,val,soma);
    }

    val = 0;
    val = val + matrix[i];
    printf("->Começar com %d\n", j);
    for ( k = 0; k < n_coins; k++ )
    {
        if ( i == k || j == k)
            continue;
        if ( val + matrix[k] > soma )
            continue;
        else
        {
            printf("Vou somar: %d\n", matrix[k] );
            val += matrix[k];
            printf("Soma actual: %d\n", val );
        }
    }
    if ( val > max_geral )
    {
        max_geral = val;
    }
    coin_sack(i,j+1,n_coins,val,soma);
    return val;
}
