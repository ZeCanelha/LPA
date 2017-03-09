#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int main(int argc, char const *argv[]) {

  int sum = 0;
  int sub_sum;
  int n_cases = 0;
  int n_coins = 0;
  int i, j;

  scanf("%d",&n_cases);

  /*SCAN THE CASE TESTES*/
  for ( i = 0; i < n_cases; i++ )
  {

    scanf("%d", &n_coins);
    /*CREATE ARRAY OF COINS*/
    int coins[n_coins];

    for (j = 0; j < n_coins; j++) {
      scanf("%d", &coins[j]);
      printf("FEZ SCAN\n");
    }

    /*CALCULATE THE SUM OF THE COINS*/
    for (j = 0; j < n_coins; j++) {
      sum += coins[j];
    }

    /*GET THE OPTIMAL SOLUTION OBTAINED IN DYNAMIC TABLE*/
    if (sum%2 != 0) {
      /*WE HAVE TO ROUND IT*/
      sub_sum = sum /2;
    }

    /*THE SUB_SUM WILL BE THE MAXIMUM CAPACITY OF THE BAG*/

    /*COINS OF THE OTHER PLAYER = SUM - SUM COINS IN THE BAG OF THE FIRST PLAYER*/
    /*MINIMUM DIFERENCE = COINS OF THE OTHER PLAYER - COINS OF THE FIRST PLAYER*/
    /*WE KNOW ITS MINIMUM BECAUSE THE TABLE WILL GIVE US THE SOLUTION WITH THE MAXIMUM VALUE IN THE BAG*/

  }

  printf("SUB SUM: %d\n", sub_sum);
  return 0;
}
