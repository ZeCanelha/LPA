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

int num_parts = 1, score = 0, scoreIndex = 0;

int scores[200]; /*isto nao esta muito bem assim*/


/* PROTOTYPES ---------------------------------------------------------------------*/
void rotate_piece (Piece * my_piece);
int isEmpty (int x, int y);
void printField (Piece (* playing_field)[MAX_PIECES*2]);
void establishSides(Piece* available_pieces);
void putOnPosition (int x, int y, Piece* available_pieces, int index, Piece (* playing_field)[MAX_PIECES*2]);
int recursive_method (int num_parts, int x, int y, Piece available_pieces[], Piece playing_field[MAX_PIECES*2][MAX_PIECES*2], int score);
int checkMatch(Piece myPiece, int x, int y, Piece* available_pieces, char myPieceSide, int* score, Piece (* playing_field)[MAX_PIECES*2]);

/*FUNCTIONS ---------------------------------------------------------------------*/
int main(int argc, char const *argv[]) {
	int l;

	Piece available_pieces[MAX_PIECES];
	Piece playing_field[MAX_PIECES*2][MAX_PIECES*2]; /* se x e y tiverem a mesma paridade, entao a face é voltada para cima; caso contrário a face é voltada para baixo*/

	/*in the begining everything is empty -1*/
	memset (playing_field, -1, sizeof(playing_field));
	memset (scores, -1, sizeof(scores));

	while(scanf("%d %d %d",&available_pieces[num_parts - 1].seq[0], &available_pieces[num_parts - 1].seq[1],&available_pieces[num_parts - 1].seq[2]) != EOF && num_parts < MAX_PIECES ) {
		num_parts++;
	}

	establishSides(available_pieces);

	/*coloca a primeira peça no centro*/
	putOnPosition ((MAX_PIECES*2)/2, (MAX_PIECES*2)/2, available_pieces, 0, playing_field);

	/* imprimir tabuleiro
	printField(playing_field);
	*/

	int length = recursive_method(num_parts-1, (MAX_PIECES*2)/2, (MAX_PIECES*2)/2, available_pieces, playing_field, score);

	/*find max score*/
	int maxValue = scores[0];
	for (l = 0; l < length; ++l) {
		if ( scores[l] > maxValue ) {
		 	maxValue = scores[l];
		} else if (scores[l] == -1) {
			break;
		}
	}

	printf("%d\n", maxValue);
	return 0;
}

int recursive_method (int num_parts, int x, int y, Piece available_pieces[], Piece playing_field[MAX_PIECES*2][MAX_PIECES*2], int score) {
	/*cada vez que se invoca o metodo recursivo uma copia do tabuleiro e das peças disponiveis tem que ser guardada*/
	if (num_parts == 0){
		printf("KAPUT 1: %d\n", score);
		scores[scoreIndex] = score;
		scoreIndex++;
		return scoreIndex;
	} else {
		if (playing_field[x-1][y].seq[0] == -1){ /*Side a*/
			printf("ENTRO NO A\n");
			if (checkMatch (playing_field[x][y], x-1, y, available_pieces, 'a', &score, playing_field) == 1){
				printf("ENTRO NO A 2.0\n");
				recursive_method (num_parts -1, x-1, y, available_pieces, playing_field, score);
			}
		}
		if (playing_field[x+1][y].seq[0] == -1) { /*Side b*/
			printf("ENTRO NO B\n");
			if (checkMatch (playing_field[x][y], x+1, y, available_pieces, 'b', &score, playing_field) == 1){
				printf("ENTRO NO B 2.0\n");
				recursive_method (num_parts -1, x+1, y, available_pieces, playing_field, score);
			}
		}

		if (x % 2 == y % 2 && playing_field[x][y+1].seq[0] == -1) { /*Side c*/
			printf("ENTRO NO C1\n");
			if (checkMatch (playing_field[x][y], x, y+1, available_pieces, 'c', &score, playing_field) == 1){
				printf("ENTRO NO C1 2.0\n");
				recursive_method (num_parts -1, x, y+1, available_pieces, playing_field, score);
			}
		} else if (x % 2 != y % 2 && playing_field[x][y-1].seq[0] == -1) {
			printf("ENTRO NO C2\n");
			if (checkMatch (playing_field[x][y], x, y-1, available_pieces, 'c', &score, playing_field) == 1){

				printf("ENTRO NO C2 2.0\n");
				recursive_method (num_parts -1, x, y-1, available_pieces, playing_field, score);
			}
		} else {
			printf("KAPUT 2: %d\n", score);
			scores[scoreIndex] = score;
			scoreIndex++;
			return scoreIndex;
		}
	}
}

/*method that checks any possible neighbour to put on field*/
int checkMatch(Piece myPiece, int x, int y, Piece* available_pieces, char myPieceSide, int* score, Piece (* playing_field)[MAX_PIECES*2]){

	int z;
	int found = 0;
	/*testar todas as combinações com peças disponiveis ainda para jogar*/
	for ( z = 0; z < num_parts; ++z) {
		/*se a peça ainda nao tiver no tabuleiro*/
		if (available_pieces[z].seq[0] != -1) {
			printf("AI O CARALHO: %d\n", myPiece.b.first);

			/*se emparelhar com o lado a da minha peça...*/
			if (myPieceSide == 'a') {

				if ((myPiece.a.first == available_pieces[z].a.first && myPiece.a.second == available_pieces[z].a.second) || (myPiece.a.first == available_pieces[z].b.first && myPiece.a.second == available_pieces[z].b.second) || (myPiece.a.first == available_pieces[z].c.first && myPiece.a.second == available_pieces[z].c.second)){
					*score += myPiece.a.first + myPiece.a.second;
					found = 1;
					break;
				}

			} else if (myPieceSide == 'b') { /*se emparelhar com o lado b da minha peça...*/

				if ((myPiece.b.first == available_pieces[z].a.first && myPiece.b.second == available_pieces[z].a.second) || (myPiece.b.first == available_pieces[z].b.first && myPiece.b.second == available_pieces[z].b.second) || (myPiece.b.first == available_pieces[z].c.first && myPiece.b.second == available_pieces[z].c.second)){

					*score += myPiece.b.first + myPiece.b.second;
					found = 1;
					break;
				}

			} else { /*se emparelhar com o lado c da minha peça...*/
				if ((myPiece.c.first == available_pieces[z].a.first && myPiece.c.second == available_pieces[z].a.second) || (myPiece.c.first == available_pieces[z].b.first && myPiece.c.second == available_pieces[z].b.second) || (myPiece.c.first == available_pieces[z].c.first && myPiece.c.second == available_pieces[z].c.second)){
					*score += myPiece.c.first + myPiece.c.second;
					found = 1;
					break;
				}
			}
		}
	}
	if (found == 1) {
		/*coloca no tabuleiro o vizinho escolhido e torna indisponivel a peça para voltar a jogar*/
		putOnPosition (x, y, available_pieces, z, playing_field);
		return 1;
	} else {
		return 0;
	}
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
void putOnPosition (int x, int y, Piece* available_pieces, int index, Piece (* playing_field)[MAX_PIECES*2]) {
	playing_field[x][y].seq[0] = available_pieces[index].seq[0];
	playing_field[x][y].seq[1] = available_pieces[index].seq[1];
	playing_field[x][y].seq[2] = available_pieces[index].seq[2];
	playing_field[x][y].a.first = available_pieces[index].seq[0];
	playing_field[x][y].a.second = available_pieces[index].seq[1];
	playing_field[x][y].b.first = available_pieces[index].seq[1];
	playing_field[x][y].b.second = available_pieces[index].seq[2];
	playing_field[x][y].c.first = available_pieces[index].seq[1];
	playing_field[x][y].c.second = available_pieces[index].seq[3];
	/*peça deixa de estar disponível*/
	available_pieces[index].seq[0] = -1;
	return;
}

/* print status of the game */
void printField (Piece (* playing_field)[MAX_PIECES*2]) {
	int i, j, m, k,z;
	for (i = 0; i < MAX_PIECES*2; i++) {
		for (m = 0; m < 2; m++) {
			for (j = 0; j < MAX_PIECES*2; j++) {
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
		for ( z = 0; z < MAX_PIECES*2; z++) {
			printf("------");
		}
		printf("\n");
	}
	printf("\n\n");
}

void establishSides(Piece* available_pieces) {
	available_pieces[num_parts - 1].a.first = available_pieces[num_parts - 1].seq[0];
	available_pieces[num_parts - 1].a.second = available_pieces[num_parts - 1].seq[1];
	available_pieces[num_parts - 1].b.first = available_pieces[num_parts - 1].seq[1];
	available_pieces[num_parts - 1].b.second = available_pieces[num_parts - 1].seq[2];
	available_pieces[num_parts - 1].c.first = available_pieces[num_parts - 1].seq[1];
	available_pieces[num_parts - 1].c.second = available_pieces[num_parts - 1].seq[3];
}
