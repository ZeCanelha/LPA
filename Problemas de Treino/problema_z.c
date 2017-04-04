#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int nodes, edges, test_cases = 0;
int adjacency_1[10][10];
int tamanho;
int permutations[10];
int maxPermutations;
int actualPermutations = 1;
int level = 0;
int** adjacency_2;


int* permutation(int* matrix, int a) {
    int i;
    int* tempMatrix = malloc(tamanho*tamanho*sizeof(int));
    int* rowBackUp = malloc(tamanho*sizeof(int));
    memcpy(tempMatrix, matrix, tamanho * tamanho * sizeof(int));
    if (a == level){
        return tempMatrix;
    }

    for (i = 0; i < tamanho; i++) {
        tempMatrix[i * tamanho + a] = matrix[i * tamanho + level];
        tempMatrix[i * tamanho + level] = matrix[i * tamanho + a];
    }

    memcpy(rowBackUp, tempMatrix + a * tamanho, tamanho * sizeof(int));
    memcpy(tempMatrix + a * tamanho, tempMatrix + level * tamanho, tamanho * sizeof(int));
    memcpy(tempMatrix + level * tamanho, rowBackUp, tamanho * sizeof(int));


    return tempMatrix;
}


int factorial() { return (tamanho == 1 || tamanho == 0) ? 1 : factorial(tamanho - 1) * tamanho; }

int equal() {
    int i,j;

    for (i = 0; i < tamanho; i++) {
        for (j = 0; j < tamanho; j++) {
            if (adjacency_1[i * tamanho + j] != adjacency_2[i * tamanho + j]){
                return 0;
            }
        }
    }
    return 1;
}

int isomorphism(int** permutedGraph) {
    int i;
    if (actualPermutations == maxPermutations) {
        return 1;
    }
    if (equal()) {
        return 1;
    }

    for (i = level; i < tamanho; i++) {
        int temp = permutations[i];
        permutations[i] = permutations[level];
        permutations[level] = temp;
        level++;
        actualPermutations++;
        if (isomorphism(permutation(permutedGraph,i))){
            return 1;
        }
        actualPermutations--;
        level--;
        permutations[level] = permutations[i];
        permutations[i] = temp;
    }

    return 0;
}





int main(int argc, char const *argv[]) {
    int i, x, y, j;
    scanf("%d", &test_cases);

    for (i = 0; i < test_cases; i++) {
        scanf("%d %d", &nodes, &edges);
        printf("EDGES: %d\n", edges);
        for (j = 0; j < edges; j++) {
            scanf("%d %d",&x, &y);
            adjacency_1[x][y] = 1;
            adjacency_1[y][x] = 1;
        }
        for (j = 0; j < edges; j++) {
            scanf("%d %d",&x, &y);
            adjacency_2[x][y] = 1;
            adjacency_2[y][x] = 1;
        }
    }
    tamanho = nodes;
    maxPermutations = factorial();
    adjacency_2 = malloc(100*sizeof(int));

    for (i = 0; i < tamanho; i++) {
        permutations[i] = i + 1;
    }

    if (isomorphism(adjacency_2) == 1) {
        printf("YES\n");
    } else {
        printf("NO\n");
    }

    return 0;
}
