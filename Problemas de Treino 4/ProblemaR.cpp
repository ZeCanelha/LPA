#include <iostream>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <list>

using namespace std;

#define NIL -1


int childrens[800];

using namespace std;

class Graph{
	int nr_vertices;
public:
	list<int> *adj;
	Graph(int nr_vertices);
	void addEdge(int v, int w);
	void art_points_util(int u, bool visited[], int disc[], int low[], int parent[], bool ap[]);
	void articulation_points();
};

Graph::Graph(int nr_vertices){
	this->nr_vertices = nr_vertices;
	adj = new list<int>[nr_vertices];
}

void Graph::addEdge(int v, int w){
	adj[v].push_back(w);
	//Undirected graph
	adj[w].push_back(v);
}

void Graph::art_points_util(int u, bool visited[], int disc[], int low[], int parent[], bool ap[]){
	static int time = 0;

	int children = 0;

	//Marcar atual como visitado
	visited[u] = true;

	disc[u] = low[u] = ++time;

	list<int>::iterator i;

	//Percorrer vertices adjacentes
	for (i=adj[u].begin(); i != adj[u].end(); ++i){
		int v = *i;

		if (!visited[v]){
			children++;
			parent[v] = u;
			art_points_util(v,visited,disc,low,parent,ap);

			low[u] = min(low[u],low[v]);

			//U é um ponto de articulação nos seguintes casos

			if (parent[u] == NIL && children > 1){
				ap[u] = true;
			}

			if (parent[u] != NIL && low[v] >= disc[u]){
               ap[u] = true;
			}
		}
		else if (v != parent[u]){
            low[u]  = min(low[u], disc[v]);
		}
	}
}

void Graph::articulation_points(){

    bool *visited = new bool[nr_vertices];
    int *disc = new int[nr_vertices];
    int *low = new int[nr_vertices];
    int *parent = new int[nr_vertices];
    int maior = 0;

    bool *ap = new bool[nr_vertices];


    for (int i = 0; i < nr_vertices; i++){
        parent[i] = NIL;
        visited[i] = false;
        ap[i] = false;
    }

    for (int i = 0; i < nr_vertices; i++)
        if (visited[i] == false)
            art_points_util(i, visited, disc, low, parent, ap);


    for (int i = 0; i < nr_vertices; i++){
        if (ap[i] == true){
            if (childrens[i] > maior){
            	maior = childrens[i];
            }
        }
    }

    if (maior == 0){
    	cout << "Strong network\n";
    }
    else{
    	cout << maior << "\n";
    }
}


int main()
{
    int i , j;
    int n_nodes;
    int known_associates,ids;
    while( cin >> n_nodes)
    {
        Graph g(n_nodes);
        for ( i = 0; i < n_nodes; i++ )
        {
            cin >> known_associates;
            childrens[i] = known_associates;
            for ( j = 0; j < known_associates; j++ )
            {
                cin >> ids;
                g.addEdge(i,ids-1);
            }
        }
        g.articulation_points();
    }

}
