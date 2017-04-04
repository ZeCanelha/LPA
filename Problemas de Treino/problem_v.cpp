#include <cstdio>
#include <queue>

using namespace std;
long budget;
long gifts[750];

struct edge {
	int v;
	int w;
};

bool operator <( edge a, edge b ) {
	return a.w < b.w;
}

#define INF 10000000

int dist[750];
int bill[750] = {0};

void dijkstra( vector< edge > graph[], int N, int S, int T ) {
	int i;

	priority_queue< edge > q;
	q.push( ( edge ) { S, 0 } );
	dist[ S ] = 0;
	bill[ S ] = 0;

	while ( !q.empty() ) {
		edge p = q.top();
		q.pop();

		for ( i = 0; i < (int)graph[ p.v ].size(); ++i ) {
				edge k = graph[ p.v ][ i ];
				if ( (dist[ p.v ] + k.w < dist[ k.v ]) && (bill[p.v] + gifts[k.v] <= budget)) {
					dist[ k.v ] = dist[ p.v ] + k.w;
					bill[k.v] = bill[p.v] + gifts[k.v];
					q.push( k );
				}
		}
	}
	if ( dist[ T ] != INF ) {
		printf( "%d\n", dist[ T ] );
	}
	else {
		printf( "Bye Bye Natalia!\n" );
	}
}

int main() {
	int t, N, m;
	int u, v, w, i;
	scanf( "%d", &t );

	while ( t > 0 ) {
		scanf( "%d%d%ld", &N, &m, &budget);
		vector< edge > graph[ N + 1 ];

		for ( i = 0; i < m; ++i ) {
			scanf( "%d%d%d", &u, &v, &w );
			graph[ u ].push_back( ( edge ) { v, w } );
			graph[ v ].push_back( ( edge ) { u, w } );
		}
		for (i = 0; i < N; i++) {
			scanf("%ld", &gifts[i+1]);
			dist[i] = INF;
		}
		dist[i] = INF;
		dijkstra( graph, N, 1, N );

		--t;
	}

	return 0;
}
