#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#define INT_MAX 2147483647

long graph[200][200];
int final_node;
long min;
long wheight;
int n_cities;

int minDistance(int dist[], bool sptSet[]) {

   int min = INT_MAX, min_index;

   for (int v = 0; v < n_cities; v++)
     if (sptSet[v] == false && dist[v] <= min)
         min = dist[v], min_index = v;

   return min_index;
}


int printSolution(int dist[], int n) {
   for (int i = 0; i < n_cities; i++){
       if (i == final_node-1) {
           printf("%d\n", dist[i]);
       }
   }
    return 1;

}


void dijkstra(long graph[200][200], int src) {
    int dist[n_cities];

    bool sptSet[n_cities];

    for (int i = 0; i < n_cities; i++)
        dist[i] = INT_MAX, sptSet[i] = false;

    dist[src] = 0;

    for (int count = 0; count < n_cities-1; count++) {
       int u = minDistance(dist, sptSet);

       sptSet[u] = true;

       for (int v = 0; v < n_cities; v++)

         if (!sptSet[v] && graph[u][v] && graph[u][v] != -1 && dist[u] != INT_MAX  && dist[u]+graph[u][v] < dist[v])
            dist[v] = dist[u] + graph[u][v];
     }

     printSolution(dist, n_cities);
}

int main(int argc, char const *argv[])
{
    int i, j;
    scanf("%d %d",&n_cities, &final_node);

    memset(graph, 0,sizeof(graph));

    for (i = 0; i < n_cities; i++) {
        for (j = 0; j <= n_cities; j++) {
            scanf("%ld",&wheight);
            if (j != 0) {
                graph[i][j-1] = wheight;
            }
        }

    }
    dijkstra(graph, 0);
    return 0;
}
