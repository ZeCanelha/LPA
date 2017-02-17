#include <stdlib.h>
#include <stdio.h>

/*CONSTANTS & STRUCTS ------------------------------------------------------------*/

#define MAX_PIECES 19

int num_parts = 0;

typedef struct {
	int seq[3];
} Piece;

struct Playing_field_coords {
	int x, y;
};

Piece available_pieces[MAX_PIECES];
Piece playing_field[MAX_PIECES][MAX_PIECES];

/* PROTOTYPES ---------------------------------------------------------------------*/
void rotate_piece (Piece * my_piece);

/*FUNCTIONS ---------------------------------------------------------------------*/
int main(int argc, char const *argv[]) {

	while(scanf("%d %d %d",&available_pieces[num_parts].seq[0], &available_pieces[num_parts].seq[1],&available_pieces[num_parts].seq[2]) != EOF) {

		printf("VOU RODAR UMA VEZ!\n" );
		rotate_piece (&available_pieces[num_parts]);

		printf("%d, %d, %d\n", available_pieces[num_parts].seq[0], available_pieces[num_parts].seq[1], available_pieces[num_parts].seq[2]);
		printf("VOU RODAR SEGUNDA VEZ!\n" );
		rotate_piece (&available_pieces[num_parts]);
		printf("%d, %d, %d\n", available_pieces[num_parts].seq[0], available_pieces[num_parts].seq[1], available_pieces[num_parts].seq[2]);
		num_parts++;

	}

	return 0;
}

/*method that rotates a piece one time*/
void rotate_piece (Piece * my_piece){
	Piece copy = *my_piece;
	int i;

	for (i = 0; i < 3; ++i) {
		my_piece->seq[(i+1) % 3] = copy.seq[i];
	}
	return;
}

/* print_game () {

}*/

/* recursive_method () {

}*/

/* print_available_pieces() {

}*/
