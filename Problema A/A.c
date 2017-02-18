#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define MAX_PIECES 2

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

int num_parts = 0, score = 0, i = 0;

int scores[200]; /*isto nao esta muito bem assim*/

Piece available_pieces[MAX_PIECES];
Piece playing_field[MAX_PIECES][MAX_PIECES]; /* se x e y tiverem a mesma paridade, entao a face é voltada para cima; caso contrário a face é voltada para baixo*/

/* PROTOTYPES ---------------------------------------------------------------------*/
void rotate_piece (Piece * my_piece);
int isEmpty (int x, int y);
void printField ();
void putOnPosition (int x, int y, Piece* available_pieces, int index);
int recursive_method (int num_parts, int x, int y, Piece available_pieces[], Piece playing_field[MAX_PIECES][MAX_PIECES], int score);
int checkMatch(Piece myPiece, int x, int y, Piece* available_pieces, char myPieceSide);

/*FUNCTIONS ---------------------------------------------------------------------*/
int main(int argc, char const *argv[]) {
	/*in the begining everything is empty -1*/
	memset (playing_field, -1, sizeof(playing_field));
	memset (scores, -1, sizeof(scores));

	while(scanf("%d %d %d",&available_pieces[num_parts].seq[0], &available_pieces[num_parts].seq[1],&available_pieces[num_parts].seq[2]) != EOF && num_parts < MAX_PIECES-1) {
		available_pieces[num_parts].a.first = available_pieces[num_parts].seq[0];
		available_pieces[num_parts].a.second = available_pieces[num_parts].seq[1];
		available_pieces[num_parts].b.first = available_pieces[num_parts].seq[1];
		available_pieces[num_parts].b.second = available_pieces[num_parts].seq[2];
		available_pieces[num_parts].c.first = available_pieces[num_parts].seq[1];
		available_pieces[num_parts].c.second = available_pieces[num_parts].seq[3];
		num_parts++;
	}
	/*coloca a primeira peça no centro*/
	putOnPosition (num_parts/2, num_parts/2, available_pieces, 0);

	printField();

	int length = recursive_method(num_parts, num_parts/2, num_parts/2, available_pieces, playing_field, score);

	/*find max score*/
	int maxValue = scores[0];
	for (i = 0; i < length; ++i) {
		if ( scores[i] > maxValue ) {
		 	maxValue = scores[i];
		} else if (scores[i] == -1) {
			break;
		}
	}
	printf("%d\n", maxValue);
	return 0;
}

int recursive_method (int num_parts, int x, int y, Piece available_pieces[], Piece playing_field[MAX_PIECES][MAX_PIECES], int score) {

	/*cada vez que se invoca o metodo recursivo uma copia do tabuleiro e das peças disponiveis tem que ser guardada*/
	if (num_parts == 0){
		scores[i] = score;
		i++;
		return i;
	} else {
		if (playing_field[x-1][y].seq[0] == -1){ /*Side a*/
			score += checkMatch (playing_field[x][y], x-1, y, available_pieces, 'a');

			return recursive_method (num_parts -1, x-1, y, available_pieces, playing_field, score);
		}
		if (playing_field[x+1][y].seq[0] == -1) { /*Side b*/
			score += checkMatch (playing_field[x][y], x+1, y, available_pieces, 'b');
			return recursive_method (num_parts -1, x+1, y, available_pieces, playing_field, score);
		}
		if (x % 2 == y % 2 && playing_field[x][y+1].seq[0] == -1) { /*Side c*/
			score += checkMatch (playing_field[x][y], x, y+1, available_pieces, 'c');
			return recursive_method (num_parts -1, x, y+1, available_pieces, playing_field, score);
		} else if (x % 2 != y % 2 && playing_field[x][y-1].seq[0] == -1) {
			score += checkMatch (playing_field[x][y], x, y-1, available_pieces, 'c');
			return recursive_method (num_parts -1, x, y-1, available_pieces, playing_field, score);
		} else {
			scores[i] = score;
			i++;
			return i;
		}
	}
}

/*method that checks any possible neighbour to put on field*/
int checkMatch(Piece myPiece, int x, int y, Piece* available_pieces, char myPieceSide){
	int i, score = 0;
	/*testar todas as combinações com peças disponiveis ainda para jogar*/
	for ( i = 0; i < num_parts; i++) {
		if (available_pieces[i].seq[0] != -1) {
			/*se emparelhar com o lado a da minha peça...*/
			if (myPieceSide == 'a') {
				if ((myPiece.a.first == available_pieces[i].a.first && myPiece.a.second == available_pieces[i].a.second) || (myPiece.a.first == available_pieces[i].b.first && myPiece.a.second == available_pieces[i].b.second) || (myPiece.a.first == available_pieces[i].c.first && myPiece.a.second == available_pieces[i].c.second)){
					score = myPiece.a.first + myPiece.a.second;
					break;
				}
				/*se emparelhar com o lado b da minha peça...*/
			} else if (myPieceSide == 'b') {
				if ((myPiece.b.first == available_pieces[i].a.first && myPiece.b.second == available_pieces[i].a.second) || (myPiece.b.first == available_pieces[i].b.first && myPiece.b.second == available_pieces[i].b.second) || (myPiece.b.first == available_pieces[i].c.first && myPiece.b.second == available_pieces[i].c.second)){
					score = myPiece.b.first + myPiece.b.second;
					break;
				}
				/*se emparelhar com o lado c da minha peça...*/
			} else {
				if ((myPiece.c.first == available_pieces[i].a.first && myPiece.c.second == available_pieces[i].a.second) || (myPiece.c.first == available_pieces[i].b.first && myPiece.c.second == available_pieces[i].b.second) || (myPiece.c.first == available_pieces[i].c.first && myPiece.c.second == available_pieces[i].c.second)){
					score = myPiece.c.first + myPiece.c.second;
					break;
				}
			}
		}
	}

	/*coloca no tabuleiro o vizinho escolhido e torna indisponivel a peça para voltar a jogar*/
	putOnPosition (x, y, available_pieces, i);

	return score;
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

/*put piece on the field*/
void putOnPosition (int x, int y, Piece* available_pieces, int index) {
	playing_field[x][y].seq[0] = available_pieces[index].seq[0];
	playing_field[x][y].seq[1] = available_pieces[index].seq[1];
	playing_field[x][y].seq[2] = available_pieces[index].seq[2];
	/*peça deixa de estar disponível*/
	available_pieces[index].seq[0] = -1;
	available_pieces[index].seq[1] = -1;
	available_pieces[index].seq[2] = -1;
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
