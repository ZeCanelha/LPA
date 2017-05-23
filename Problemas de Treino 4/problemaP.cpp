#include <string.h>
#include <cstdio>
#include <iostream>
#include <queue>
#include <sstream>

using namespace std;

//LOGICA: CALCULAR O SHORTEST PATH COM PESOS POSITIVOS -> DIJKSTRA

struct Node{
    int distancia;
    int node;
    Node(){}
    Node(int n, int c){node = n;distancia = c;}
    bool operator <(const Node & node)const{    //fundamental para a priority queue
        return distancia > node.distancia;
    }
};

typedef pair < int , int > ii;  //guardamos o no adjacente e o peso da ligacao
vector < ii > g[100];   //vetores de adjacencia
int  num_elevadores, final_floor;

int distancias[100];

int dijkstra(){

    int from, adjacente, weight;
    memset(distancias, -1, sizeof(distancias));
    distancias[0] = 0;

    /*como não sabemos quantos nós diferentes temos, nao podemos fazer ciclo como no problema A, temos que ter uma queue*/
    /*tem que ser priority queue porque nos nao queremos tirar da fila simplesmente os primeiros que lá entraram, mas sim os que se encontrarm mais perto do nó que estamos a analisar*/
    /*semelhante à funcao minDistance do problema A*/
    priority_queue< Node > pq;
    pq.push(Node(0, 0));    //queremos analisar o shortest path a partir do piso 0

    while( !pq.empty()){
        from = pq.top().node;   //o top() nao devolve necessariamente o elemento que está na frente da fila!
        pq.pop();

        if( final_floor == from) { //o dijkstra só itera uma vez pelos nós todos, portanto assim que se chega ao final_floor acaba-se
            return distancias[final_floor];
        }

        //iterar sobre todos os seus adjacentes
        for( int i = 0; i < (int)g[from].size(); i++ ){
            adjacente = g[from][i].first;
            weight = g[from][i].second;

            if( distancias[adjacente] == -1 || distancias[adjacente] > distancias[from] + weight + 60){
                //Atualizar no vetor distancias e na priority_queue
                distancias[adjacente] = distancias[from] + weight + 60;
                pq.push(Node(adjacente, distancias[adjacente]));
            }
        }
    }
    return distancias[final_floor];
}

int main(){
    int  ind, ans, i;
    string line;
    int tempos[5];
    int nos[101];
    stringstream ss;

    while (scanf("%d %d", &num_elevadores, &final_floor) != EOF) {
        memset(tempos, 0, sizeof(tempos));
        memset(nos, 0, sizeof(nos));

        for (i = 0; i < num_elevadores; i++) {
            scanf("%d", &tempos[i]);
        }

        getline(cin, line); //necessario por causa do ultimo \n
        for( int i = 0; i <num_elevadores; i++ ){
            getline(cin, line); //obtem linha das nos
            ss.clear();
            ss << line;         //permite fazer um split
            ind = 0;
            while(ss >> nos[ind++]);  //mete tudo no array
            ind--;

            for( int x = 0; x < ind; x++ ) {
                for( int y = x + 1; y < ind; y++){
                    //tem que ser com uma lista ligada que nos permita guardar os pesos porque se nao perderiamos ligacoes de nós iguais mas de elevadores diferentes
                    g[ nos[x] ].push_back(ii(nos[y], (nos[y] - nos[x])*tempos[i])); //se o elevador pára no 1 e no 3, entao estamos a guardar as ligacoes 0->1 e 0->3
                    g[ nos[y] ].push_back(ii(nos[x], (nos[y] - nos[x])*tempos[i])); //sao bidirecionais as ligacoes
                }
            }
        }

        ans = dijkstra();


        if( ans == -1) {
            printf("IMPOSSIBLE\n");
        }else{
            if( final_floor != 0) {
             ans -= 60;
            }
            printf("%d\n", ans);
        }
        for( int i = 0; i < 100; i++ ) {
            g[i].clear();
        }
  }

    return 0;
}
