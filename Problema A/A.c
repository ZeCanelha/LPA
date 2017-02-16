#include <stdlib.h>
#include <stdio.h>

#define MAX_PIECES 19

int num_parts = 0;

struct Piece {
	int seq[3];
};

struct Playing_field_coords {
	int x, y;
};

struct Piece puzzle_parts[MAX_PIECES];

int main(int argc, char const *argv[]) {

	while(scanf("%d %d %d",&puzzle_parts[num_parts].seq[0], &puzzle_parts[num_parts].seq[1],&puzzle_parts[num_parts].seq[2]) != EOF && num_parts <= MAX_PIECES) {
	}

	return 0;
}

// rotate_piece (){

}

// print_game () {

}

// recursive_method () {

}

//print_available_pieces() {

}
