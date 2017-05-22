#include <queue>
#include <iostream>
#include <list>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

using namespace std;
int graph[1000][1000];
int distances[1000];
int analises[1000];
int visited[1000];
int test_cases;
int star_systems, whormholes;

//IDEIA: VERIFICAR SE EXISTEM CICLOS NEGATIVOS -> APLICAR ALGORITMO DE BELLMAN FORD

bool BellmanFord() {
	int i, l;
	queue<int> fifo;
	for(i = 0;i < star_systems; i++) {
		distances[i] = 2147483647; //inteiro maximo
		analises[i] = 0;
		visited[i] = 0;
	}

	distances[0] = 0;
	fifo.push(0);

	//em cada iteração analisamos todos os nós
	while(!fifo.empty()) {
		int p = fifo.front();
		//à partida marco o nó em analise como visitado
		visited[p] = 0;
		//correr todas as arestas que esse vertice tem
		for (l = 0; l < star_systems; l++) {
			if (graph[p][l]) {
				if(distances[p] + graph[p][l] < distances[l] && distances[p] != 2147483647 ) {
					if(++analises[l] >= star_systems) {					//no maximo só analiso "star_systems"-1 vezes cada nó.
						return true;								//se analisei pelo menos "star_systems" vezes então é porque começo a entrar num ciclo negativo
					}												//se tiver a certeza que nao existem ciclos negativos, entao nao é este if só gasta recurso computacionais desnecessariamente
					if(visited[l] == 0) {
						fifo.push(l);
					}

					distances[l] = distances[p] + graph[p][l]; //como encontrei uma forma mais curta de chegar até l, atualizo a distancia de l
					visited[l] = 1;	//marco o nó adjacente como visitado se tiver encontrado uma forma mais curta de chegar até ele
				}
			}
		}
		fifo.pop();
	}
	return false;
}

int main() {
	int x,y,wheight;
	int i;
	scanf("%d", & test_cases);

	while(test_cases) {
    	memset(graph, 0,sizeof(graph));
		scanf("%d %d", &star_systems, &whormholes);

		for(i = 0;i< whormholes; i++) {
			scanf("%d %d %d", &x, &y, &wheight);
			graph[x][y] = wheight;
		}

		if(BellmanFord()) {
			printf("possible\n");
		}
		else {
			printf("not possible\n");
		}

		test_cases--;
	}
	return 0;
}
