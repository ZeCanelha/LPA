#include <iostream>
#include <cstring>
#include <vector>
#include <stdio.h>

#define N 50

using namespace std;

enum direction { West = 1, North = 2, East = 4, South = 8 };

int width = 0, height = 0;

int maze [N + 2] [N + 2];
vector <int> matrix [N * N + 5];
bool vis [N * N + 5];
int numberOfComponent;
int component [N * N + 5];
int componentFrequency [N * N + 5];
int dr [] = {-1, 0, 1, 0};
int dc [] = {0, 1, 0, -1};
int maxSizedRoom;
int resW, resH;
char resDir;


void dfs (int no, int c) {
    int i;
    if ( vis [no] ) {
        return;
    }
    vis [no] = true;
    component [no] = c;

    for (i = 0; i < (int) matrix [no].size (); i++ ) {
        dfs (matrix [no] [i], c);
    }
}

void checkByRemove (int p, int q) {
    int freq = -1;

    if ( p != 0 && component [maze [p] [q]] != component [maze [p - 1] [q]] ) {
        freq = componentFrequency [component [maze [p] [q]]] + componentFrequency [component [maze [p - 1] [q]]];
        if ( freq > maxSizedRoom ) {
            maxSizedRoom = freq;
            resW = q; resH = p; resDir = 'N';
        }
    }
    if ( q != width - 1 && component [maze [p] [q]] != component [maze [p] [q + 1]] ) {
        freq = componentFrequency [component [maze [p] [q]]] + componentFrequency [component [maze [p] [q + 1]]];
        if ( freq > maxSizedRoom ) {
            maxSizedRoom = freq;
            resW = q; resH = p; resDir = 'E';
        }
    }
}


int main () {

    scanf ("%d %d", &height, &width);
    int inp;

    int cnt = 1;

    for ( int i = 0; i < height; i++ ) {
        for ( int j = 0; j < width; j++ ) maze [i] [j] = cnt++;
    }
    memset(vis, false, sizeof (vis));
    memset(componentFrequency, 0, sizeof (vis));

    numberOfComponent = 0;
    maxSizedRoom = -1;

    bool dir [4];

    for ( int i = 0; i < height; i++ ) {

        for ( int j = 0; j < width; j++ ) {
            scanf ("%d", &inp);
            dir [0] = dir [1] = dir [2] = dir [3] = true;
            for ( int k = 8; k >= 1; k /= 2 ) {
                if ( inp >= k ) {
                    switch (k) {
                    case 8: dir [0] = false; break;
                    case 4: dir [1] = false; break;
                    case 2: dir [2] = false; break;
                    case 1: dir [3] = false; break;
                    }
                    inp -= k;
                }
            }

            if ( dir [0] ) matrix [maze [i] [j]].push_back(maze [i + 1] [j]);
            if ( dir [1] ) matrix [maze [i] [j]].push_back(maze [i] [j + 1]);
            if ( dir [2] ) matrix [maze [i] [j]].push_back(maze [i - 1] [j]);
            if ( dir [3] ) matrix [maze [i] [j]].push_back(maze [i] [j - 1]);
        }
    }


    for ( int i = 0; i < height; i++ ) {
        for ( int j = 0; j < width; j++ ) {
            if ( !vis [maze [i] [j]] ) {
                dfs (maze [i] [j], ++numberOfComponent);
            }
        }
    }

    printf ("%d\n", numberOfComponent);

    return 0;
}
