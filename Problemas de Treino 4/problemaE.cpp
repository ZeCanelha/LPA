#include<iostream>
#include <list>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
using namespace std;

//IDEIA: VERIFICAR SE CADA PAR (u,v) QUE EXISTE NA GONDOLA 1 É UM PAR "REACHABLE" NA GONDOLA 2

int test_cases;
int gondola1[600][600];
int gondola2[600][600];
int connections1, connections2;
int cities;
int indice;
int minConections;

class Graph {
    int V;

public:
    list<int> *adj;
    Graph(int V);
    void addEdge(int v, int w);

};

bool isRedundant(Graph g1, Graph g2);

Graph::Graph(int V) {
    this->V = V;
    adj = new list<int>[V];
}

void Graph::addEdge(int v, int w) {
    adj[v].push_back(w);
}


bool isReachable(int s, int d, Graph g) {

    bool *visited = new bool[26];
    for (int i = 0; i < 26; i++) {
        visited[i] = false;
    }

    list<int> queue;

    visited[s] = true;
    queue.push_back(s);

    list<int>::iterator i;

    while (!queue.empty()) {
        s = queue.front();
        queue.pop_front();

        for (i = g.adj[s].begin(); i != g.adj[s].end(); ++i) {
            if (*i == d){
                return true;
            }

            if (!visited[*i]) {
                visited[*i] = true;
                queue.push_back(*i);
            }
        }
    }

    return false;
}

bool isRedundant(Graph g1, Graph g2){
    list<int>::iterator i;
    int l;
    for (l = 0; l < 26; l++) {
        for (i = g1.adj[l].begin(); i != g1.adj[l].end(); ++i) {
            if(!isReachable(l, *i, g2)){
                return false;
            }
        }
    }
    for (l = 0; l < 26; l++) {
        for (i = g2.adj[l].begin(); i != g2.adj[l].end(); ++i) {
            if(!isReachable(l, *i, g1)){
                return false;
            }
        }
    }


    return true;
}

int main(int argc, char const *argv[]) {
    int i;
    char u, v;
    scanf("%d",&test_cases);
    while (test_cases) {
        Graph g1(26);

        indice = 0;
        scanf("%d\n",&connections1);
        for (i = 0; i < connections1; i++) {
            scanf("%c %c\n", &u, &v);
            g1.addEdge(u-'A', v-'A');

        }

        Graph g2(26);
        indice = 0;
        scanf("%d\n",&connections2);
        for (i = 0; i < connections2; i++) {
            scanf("%c %c\n", &u, &v);
            g2.addEdge(u-'A', v-'A');
        }

        if(isRedundant(g1, g2))
            cout<< "YES\n";
        else
            cout<< "NO\n";

        if (--test_cases != 0) {
            printf("\n");
        }
    }

    return 0;
}
