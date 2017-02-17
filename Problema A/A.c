#include <stdlib.h>
#include <stdio.h>
#include <string.h>

/*CONSTANTS & STRUCTS ------------------------------------------------------------*/

#define MAX_PIECES 3

int num_parts = 1;

typedef struct {
	int seq[3];
} Piece;

struct Playing_field_coords {
	int x, y;
};

Piece available_pieces[MAX_PIECES];
Piece playing_field[MAX_PIECES][MAX_PIECES]; /* se x e y tiverem a mesma paridade, entao a face é voltada para cima; caso contrário a face é voltada para baixo*/

/* PROTOTYPES ---------------------------------------------------------------------*/
void rotate_piece (Piece * my_piece);
int isEmpty (int x, int y);
void printField ();

/*FUNCTIONS ---------------------------------------------------------------------*/
int main(int argc, char const *argv[]) {

	/*in the begining everything is empty -1*/
	memset (playing_field, -1, sizeof(playing_field));

	while(scanf("%d %d %d",&available_pieces[num_parts].seq[0], &available_pieces[num_parts].seq[1],&available_pieces[num_parts].seq[2]) != EOF && num_parts < MAX_PIECES) {
		num_parts++;

	}
	printField();

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

/* before place a tile in empty position, check whether the numbers in already places tiles agree
int isSideMatched () {

}*/

/*checks if position is empty*/
int isEmpty (int x, int y) {
	if(playing_field[x][y].seq[0] == 6)
		return 1;
	else
		return 0;
}

/*put piece on the field
int putOnField () {

}*/

/* print status of the game */
void printField () {
	int i, j, m, k,z;
	for (i = 0; i < MAX_PIECES; i++) {
		for (m = 0; m < 2; m++) {
			for (j = 0; j < MAX_PIECES; j++) {
					for (k = 0; k < 3; k++) {
						if (i % 2 == j% 2) {
							if (m == 0) {
								if (k == 0){
									printf(" ");
								} else if (k == 1) {
									printf("%d", playing_field[i][j].seq[1]);
								} else {
									printf(" ");
								}
							} else {
								if (k == 0){
									printf("%d", playing_field[i][j].seq[0]);
								} else if (k == 1) {
									printf(" ");
								} else {
									printf("%d", playing_field[i][j].seq[2]);
								}
							}
						} else {
							if (m == 0) {
								if (k == 0){
									printf("%d", playing_field[i][j].seq[0]);
								} else if (k == 1) {
									printf(" ");
								} else {
									printf("%d", playing_field[i][j].seq[2]);
								}
							} else {
								if (k == 0){
									printf(" ");
								} else if (k == 1) {
									printf("%d", playing_field[i][j].seq[1]);
								} else {
									printf(" ");
								}
							}
						}
					}
				printf("|");
			}
			printf("\n");
		}
		for ( z = 0; z < num_parts; z++) {
			printf("-----");
		}
		printf("\n");
	}
}

/* recursive_method () {
	base case:
		colocar a peça na posição x e y no centro


	varia consoante x e y??
}*/
