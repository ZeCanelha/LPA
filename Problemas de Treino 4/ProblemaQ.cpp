#include<iostream>
#include <list>

using namespace std;



class Graph
{
    int V;
    list<int> *adj;
public:
    Graph(int V);
    void addEdge(int v, int w);
    void BFS(int s, int end_node);
};

Graph::Graph(int V)
{
    this->V = V;
    adj = new list<int>[V];
}

void Graph::addEdge(int v , int w)
{
    adj[v].push_back(w);
}

void Graph::BFS(int s, int end_node)
{
    int count_path = 1;
    int flag = 1;
    bool *visited = new bool[V];
    for(int i = 0; i < V; i++)
        visited[i] = false;


    list<int> queue;


    visited[s] = true;
    queue.push_back(s);


    list<int>::iterator i;

    while(!queue.empty() )
    {

        s = queue.front();
        queue.pop_front();

        for(i = adj[s].begin(); i != adj[s].end(); ++i)
        {
            if(!visited[*i])
            {

                visited[*i] = true;
                queue.push_back(*i);
            }
            if ( *i == end_node - 1 )
            {
                flag = 0;
                cout << count_path<< "\n";
                break;
            }

        }
        if ( flag == 0)
            break;
        count_path++;

    }
    if ( flag == 1)
        cout << "King of popularity!" << '\n';
}

int main()
{
    int max_aux;
    int max = 0;
    int i,j;
    int input;
    int current_ze_followers = 0;
    int starting_node;

    while( cin >> starting_node)
    {
        Graph g(starting_node);
        for(i = 0; i < starting_node;i++)
        {
            cin >> max_aux;
            if ( max_aux > max )
                max = max_aux;
            for ( j = 0; j < max_aux; j++ )
            {
                cin >> input;
                if ( input == starting_node)
                    current_ze_followers++;

                g.addEdge(i,input-1);
            }
        }

        g.BFS(starting_node-1,max);
    }





}
