#include<iostream>
#include<cstdio>
#include<cstring>
using namespace std;

//OBJETIVO: ENCONTRAR ARTICULATION POINTS - > TARJAN ALGORITHM

int graph[100][100];
int articPoints[100];
int low[100], dicoveryTime[100], visited[100];
int num_places;


void tarjan(int no, int father, int dtime){
    int i;
    visited[no] = 1;
    dicoveryTime[no] = dtime;
    low[no] = dtime;

    int children = 0;
    //correr todos os nos adjacentes
    for(i = 0;i < num_places;i ++) {
        if(graph[no][i]){

            if(!visited[i]){
                tarjan(i, no, dtime + 1);

                children ++;

                //verificar se a subtree de raíz no nó adjacente-i tem conexão com um ancestral do meu "no"
                if(low[no] > low[i]) {
                    low[no] = low[i];
                }

                //identificar ARTICULATION POINTS
                if((father == 0 && children > 1) || (father != 0 && low[i] >= dicoveryTime[no])) {  //ou é root e a root tem 2 filhos independentes; ou o discoveryTime é menor que o low time de um dos seus adjacente
                    articPoints[no] = 1;
                }
            } else if (i != father && i != 0){  //ENCONTREI UM CICLO E VOU VOU VOLTAR PARA TRAS, LOGO O MEU LOW TIME VAI TER QUE SER O MINIMO COMPARADO COM O DISCOVERY TIME DO ADJACENTE (com exceção da root)
                if(low[no] > dicoveryTime[i]) {
                    low[no] = dicoveryTime[i];
                }
            }
        }
    }
}

int main(){
    int vertex, u;
    scanf("%d", &num_places);
    while(num_places != 0){
        memset(dicoveryTime, 0, sizeof(dicoveryTime));
        memset(low, 0, sizeof(low));
        memset(visited, 0, sizeof(visited));
        memset(articPoints, 0, sizeof(articPoints));
        memset(graph, 0, sizeof(graph));

        scanf("%d", &vertex);
        while(vertex){
            while(getchar() != '\n'){
                scanf("%d", &u);
                graph[u-1][vertex-1] = 1;      //as ligações são bidirecionais
                graph[vertex-1][u-1] = 1;
            }
            scanf("%d", &vertex);
        }


        int ans = 0;
        tarjan(1, 0, 0); //o primeiro nó é a nossa root
        for(int i = 0;i < num_places;i ++ ){
            if(articPoints[i]) ans ++;
        }
        printf("%d\n", ans);


        scanf("%d", &num_places);
    }
    return 0;
}
