#include <stdlib.h>
#include <stdio.h>
#include <string.h>


int max_value(int a, int b) { return (a > b)? a : b; }

int main(int argc, char const *argv[]) {


  int sub_sum = 0;
  int n_cases = 0;
  int n_coins = 0;
  int i, j, k;

  scanf("%d",&n_cases);

  /*SCAN THE CASE TESTS*/
  for ( i = 0; i < n_cases; i++ )
  {

    scanf("%d", &n_coins);
    printf("N_COINS: %d\n", n_coins);
    int coins_value[n_coins];

    for (j = 0; j < n_coins; j++) {
      scanf("%d", &coins_value[j]);
    }

    int sum = 0;
    /*Create the sum of every coin*/
    for (j = 0; j < n_coins; j++) {
      sum += coins_value[j];
    }

    if (sum %2 != 0) {
      sub_sum = (sum /2) + 1;
    } else {
      sub_sum = sum /2;
    }

    printf("SUB_SUM:%d\n", sub_sum);
    /*Create the dynamic_table for dynamic programming*/

    int dynamic_table[n_coins+1][sub_sum+1];

    memset(dynamic_table, 0, sizeof(dynamic_table));
    /*Now we have to start filling the table. The solution will give us the maximum capacity of each sack.
    And if the solution = sub_sum; Then it's true, and the minimum difference will be 0. Else the minimum difference
    will be given by the difference of the total and the solution given by the dynamic table*/

    for (k = 1; k < n_coins+1; k++) {
      for (j = 1; j < sub_sum +1; j++) {
        /*If the weight value is superior than actual weight*/
        if (coins_value[k] > j) {
          dynamic_table[k][j] = dynamic_table[k-1][j];
        } else {
          dynamic_table[k][j] = max_value(dynamic_table[k-1][j], coins_value[k] + dynamic_table[k-1][j - coins_value[k]]);
        }
      }
    }

    printf("AFTER\n");
    for (k = 1; k < n_coins+1; k++) {
      for (j = 1; j < sub_sum +1; j++) {
        /*If the weight value is superior than actual weight*/
        printf("%d ", dynamic_table[k][j]);
      }
      printf("\n");
    }

    printf("LAST ELEMENT: %d\n", dynamic_table[n_coins+1][sub_sum+1]);
    printf("A DIFERENCA ENTRE sub_sum(%d) e o melhor(%d) é = (%d)\n", sub_sum, dynamic_table[n_coins+1][sub_sum+1], sub_sum - dynamic_table[n_coins+1][sub_sum+1] );
    printf("%d\n", sub_sum - dynamic_table[n_coins+1][sub_sum+1] );

  }
  return 0;
}
