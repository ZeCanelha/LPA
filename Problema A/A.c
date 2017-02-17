#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define MAX_PIECES 3

/* STRUCTS AND CONSTANTS ------------------------------------------------------------*/
typedef struct {
	int first, second;
} Side;

typedef struct {
	int seq[3];
	Side a,b,c;
} Piece;

struct Playing_field_coords {
	int x, y;
};

int num_parts = 0;

Piece available_pieces[MAX_PIECES];
Piece playing_field[MAX_PIECES][MAX_PIECES]; /* se x e y tiverem a mesma paridade, entao a face é voltada para cima; caso contrário a face é voltada para baixo*/

/* PROTOTYPES ---------------------------------------------------------------------*/
void rotate_piece (Piece * my_piece);
int isEmpty (int x, int y);
void printField ();
int itMatches (Side pieceSide, Side neighbourSide);
void putOnPosition (int x, int y, Piece myPiece);
int sideMatches (Side pieceSide, Side neighbourSide);
void recursive_method (int num_parts, int x, int y);

/*FUNCTIONS ---------------------------------------------------------------------*/
int main(int argc, char const *argv[]) {

	/*in the begining everything is empty -1*/
	memset (playing_field, -1, sizeof(playing_field));

	while(scanf("%d %d %d",&available_pieces[num_parts].seq[0], &available_pieces[num_parts].seq[1],&available_pieces[num_parts].seq[2]) != EOF && num_parts < MAX_PIECES-1) {
		available_pieces[num_parts].a.first = available_pieces[num_parts].seq[0];
		available_pieces[num_parts].a.second = available_pieces[num_parts].seq[1];
		available_pieces[num_parts].b.first = available_pieces[num_parts].seq[1];
		available_pieces[num_parts].b.second = available_pieces[num_parts].seq[2];
		available_pieces[num_parts].c.first = available_pieces[num_parts].seq[1];
		available_pieces[num_parts].c.second = available_pieces[num_parts].seq[3];
		num_parts++;
	}
	putOnPosition (num_parts/2, num_parts/2, available_pieces[num_parts]);
	printField();
	printf("%d\n", recursive_method(num_parts, num_parts/2, num_parts/2));

	return 0;
}

int recursive_method (int num_parts, int x, int y) {
	int score = 0;

	if (num_parts == 0){
		return score;
	} else {
		if (isEmpty(x-1, y)){ /*Side a*/
			score += checkMatch (playing_field[x][y], num_parts - 1);
		} else if (isEmpty(x+1, y)) { /*Side b*/

		} else { /*Side c*/
			if (x % 2 == y % 2 && isEmpty(x, y+1)) {


			} else if (x % 2 != y % 2 && isEmpty(x, y-1)) {

			}

		}

		return recursive_method(num_parts - 1, );
	}
}

/*method that checks any possible neighbour to put on field*/
int checkMatch(Piece* myPiece, int available_pieces){
	int i;
	for (i = num_parts -1; i => num_parts - available_pieces; i--) {
		/* code */
	}
	putOnPosition (x, y+1, neighbour);
	return sideMatches (Side pieceSide, Side neighbourSide);

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

/* checks if two sides of different pieces matches*/
int sideMatches (Side pieceSide, Side neighbourSide) {
	if (pieceSide.first == neighbourSide.first && pieceSide.second == neighbourSide.second){
		return pieceSide.first + pieceSide.second;
	}
	return 0;
}

/*checks if position is empty*/
int isEmpty (int x, int y) {
	if(playing_field[x][y].seq[0] == -1)
		return 1;
	else
		return 0;
}

/*put piece on the field*/
void putOnPosition (int x, int y, Piece myPiece) {
	playing_field[x][y].seq[0] = myPiece.seq[0];
	playing_field[x][y].seq[1] = myPiece.seq[1];
	playing_field[x][y].seq[2] = myPiece.seq[2];
	return;
}

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
			printf("------");
		}
		printf("\n");
	}
}
