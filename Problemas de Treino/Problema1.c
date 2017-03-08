#include <stdlib.h>
#include <stdio.h>

int function_path( int i , int h);


int main(int argc, char const *argv[])
{
  int test_cases;
  int n_rows;
  int i,j,z;

  scanf("%d",&test_cases);
  for ( i = 0; i < test_cases; i++ )
  {
    scanf("%d", &n_rows);
    int matrix[n_rows][n_rows];
    memset(matrix,-1,sizeof(matrix))
    for ( j = 0; j < n_rows; j++)
    {
      for ( z = 0; z < j; z++)
      {
        scanf("%d", matrix[j][z]);
      }
    }

    /* DENTRO DO CASO DE TESTE */

    int table_r[n_rows][n_rows];
    memset(matrix, -1 , sizeof(matrix))






  }




}
