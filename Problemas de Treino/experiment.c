
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>


int size, test_cases, edges;
int tempMatrix[100];
int rowBackUp[10];

int factorial(int n) {
    return (n == 1 || n == 0) ? 1 : factorial(n - 1) * n;
}

int* permutation(const int *matrix, int size, int a, int b) {
    int i;
    memcpy(tempMatrix, matrix, size * size * sizeof(int));
    if (a == b)
        return tempMatrix;
    for (i = 0; i < size; i++) {
        tempMatrix[i * size + a] = matrix[i * size + b];
        tempMatrix[i * size + b] = matrix[i * size + a];
    }

    memcpy(rowBackUp, tempMatrix + a * size, size * sizeof(int));
    memcpy(tempMatrix + a * size, tempMatrix + b * size, size * sizeof(int));
    memcpy(tempMatrix + b * size, rowBackUp, size * sizeof(int));

    return tempMatrix;
}

int equal(int * matrixA, int * matrixB, int size) {

    int i, j;
    for (i = 0; i < size; i++) {
        for (j = 0; j < size; j++) {
            if (matrixA[i * size + j] != matrixB[i * size + j])
                return 0;
        }
    }
    return 1;
}

int isomorphism(int* originalGraph, int* permutedGraph, int size, int level, int* permutations, int maxPermutations, int actualPermutations) {
    int i;
    if (maxPermutations == actualPermutations) {
        return 1;
    }
    if (equal(originalGraph, permutedGraph, size))
        return 1;


    for (i = level; i < size; i++) {

        int temp = permutations[i];
        permutations[i] = permutations[level];
        permutations[level] = temp;


        if (isomorphism(originalGraph, permutation(permutedGraph, size, level,
                i), size, level + 1, permutations, maxPermutations,
                ++actualPermutations))
            return 1;

        permutations[level] = permutations[i];
        permutations[i] = temp;
    }

    return 0;
}

void Isisomorphism(int* originalGraph,  int* permutedGraph, int size) {
    int i;
    int permutations[10];
    int maxPermutations = factorial(size);
    int actualPermutations = 1;

    for (i = 0; i < size; i++)
        permutations[i] = i + 1;
    if (isomorphism(originalGraph, permutedGraph, size, 0, permutations, maxPermutations, actualPermutations)) {
        printf("YES\n" );
    } else {
        printf("NO\n" );
    }
}

/* Main */
int main(int argc, char *argv[]) {
    int i, j,x,y;

    scanf("%d", &test_cases);

    for (i = 0; i < test_cases; i++) {
        scanf("%d %d", &size, &edges);

        int graphA[100];
        int graphB[100];
        for (j = 0; j < edges*2; j++) {
            if (j > 6) {
                scanf("%d %d",&x, &y);
                graphB[x * size + y - 1] = 1;
                graphB[y * size + x - 1] = 1;
            } else {
                scanf("%d %d",&x, &y);
                graphA[x * size + y - 1] = 1;
                graphA[y * size + x - 1] = 1;
            }
        }
        Isisomorphism(graphA, graphB, size);

    }

    return 0;
}
