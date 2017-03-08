#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int max(int a, int b){
  if (a > b) {
    return a;
  }
  return b;
}

int main(int argc, char const *argv[]) {
  int n_cases;
  int n_rows;
  int row, column;
  int i, j, z;

  int max_geral = 0;

  scanf("%d",&n_cases);

  /*SCAN THE CASE TESTES*/
  for ( i = 0; i < n_cases; i++ )
  {

    scanf("%d", &n_rows);

    /*CREATE AUX MATRIX*/
    int matrix[n_rows][n_rows];
    for ( j = 0; j < n_rows; j++)
    {
      for ( z = 0; z <= j; z++)
      {
        if ( z == j )
        {
            scanf("%d",&matrix[j][z]);
        }
        else
          scanf("%d ", &matrix[j][z]);
      }
    }

    int dynamic_matrix[n_rows+1][n_rows+1];
    memset(dynamic_matrix, 0, sizeof(dynamic_matrix));

    dynamic_matrix[1][1] = matrix[0][0];

    for (row = 1; row < n_rows+1; row++) {
      for (column = 1; column < row+1 ; column++) {
        /*VERIFICA EM CIMA*/
        if (dynamic_matrix[row-1][column] > dynamic_matrix[row-1][column-1]) {
          dynamic_matrix[row][column] = dynamic_matrix[row-1][column] + matrix[row][column];
        } else if(dynamic_matrix[row-1][column] < dynamic_matrix[row-1][column-1]){
          /*VERIFICA ESQUERDA*/
          dynamic_matrix[row][column] = dynamic_matrix[row-1][column] + matrix[row][column-1];
        }
      }
    }

    printf("NOVA MATRIX:\n");
    for (row = 0; row < n_rows+1; row++) {
      for (column = 0; column < row+1; column++) {
        /*VERIFICA EM CIMA*/
        printf("%d ", dynamic_matrix[row][column]);
      }
      printf("\n");
    }
  }
  printf("Score: %d\n", max_geral);
  return 0;
}
