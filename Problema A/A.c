#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define MAX_PIECES 7

/* STRUCTS AND CONSTANTS ------------------------------------------------------------*/
typedef struct {
	int firstIndex, secondIndex;
} Side;

typedef struct {
	int seq[3];
	int rotation;
} Piece;

Side a,b,c;

typedef struct {
	Piece array[MAX_PIECES*2];
} ArrayPieces;

typedef struct {
	ArrayPieces matrix[MAX_PIECES*2];
} MatrixPieces;

int conta = 0;

int num_partsCopy = 0; /*TODO:isto provavelmente vai ser mudado*/
int num_parts = 1, score = 0, scoreIndex = 0;
int availablePieceIndex = 1, matchScore = 0;
int scores[200] = {0}; /*TODO:isto nao esta muito bem assim mas q safoda por agr*/

/*TODO: temos que fazer e desfazer o tabuleiro e as available_pieces em vez de passar copias*/

/*cada peça voltada para cima tem de ter 3 vizinhos voltados para baixo e vice versa*/

/* PROTOTYPES ---------------------------------------------------------------------*/
void rotate_piece (Piece * my_piece);
int isEmpty (int x, int y);
void printField (MatrixPieces playing_field);
void establishSides();
MatrixPieces putOnPosition (int x, int y, ArrayPieces available_pieces, int index, MatrixPieces playing_field);
void recursive_method (int num_parts, int x, int y, ArrayPieces available_pieces, MatrixPieces playing_field, int score);
ArrayPieces disablePiece (ArrayPieces available_pieces, int index);

/*FUNCTIONS ---------------------------------------------------------------------*/
int main(int argc, char const *argv[]) {
	int l;
	MatrixPieces playing_field;
	ArrayPieces available_pieces;

	/*inicializar indices de orientação das peças*/
	establishSides();

	/*in the begining everything is empty -1*/
	memset (playing_field.matrix, -1, sizeof(playing_field.matrix));
	memset (available_pieces.array, -1, sizeof(available_pieces.array));

	while(scanf("%d %d %d",&available_pieces.array[num_parts - 1].seq[0], &available_pieces.array[num_parts - 1].seq[1],&available_pieces.array[num_parts - 1].seq[2]) != EOF && num_parts < MAX_PIECES ) {
		num_parts++;
	}
	num_partsCopy = num_parts;

	/*coloca a primeira peça no centro*/
	playing_field.matrix[MAX_PIECES].array[MAX_PIECES] = available_pieces.array[0];

	recursive_method(num_parts, MAX_PIECES, MAX_PIECES, available_pieces, playing_field, score);

	/*find max score*/
	int maxValue = scores[0];
	for (l = 0; l < scoreIndex; ++l) {
		printf("SCORE POSSÍVEL: %d\n", scores[l] );
		if ( scores[l] > maxValue ) {
		 	maxValue = scores[l];
		}
	}

	printf("SCORE IGUAL A: 	%d\n", maxValue);
	return 0;
}

void recursive_method (int num_parts, int x, int y, ArrayPieces available_pieces, MatrixPieces playing_field, int score) {
	/*cada vez que se invoca o metodo recursivo uma copia do tabuleiro e das peças disponiveis tem que ser guardada*/
	int newScore = 0;
	int matched = 0;
	int l = 0;
	int f = 1, z = 1;
	MatrixPieces newPlayingField;
	ArrayPieces newAvailablePieces;

	if (num_parts == 1 /*TODO:ou ja nao houver match de peça nenhuma*/){
		scores[scoreIndex] = score;
		scoreIndex++;
		return;
	} else {

		 if (playing_field.matrix[x].array[y+1].seq[0] == -1){ 	/*COMEÇAR A PREENCHER À DIREITA*/
			/*CORRER AS PEÇAS DISPONIVEIS TODAS*/
			for (f = 1; f < num_partsCopy; f++) {/*testar todas as combinações com peças disponiveis ainda para jogar - TODO:OTIMIZAR ISTO PORQUE ITERATIVAMENTE DEMORA MUITO TEMPO*/

				if (available_pieces.array[f].seq[0] != -1) {

					for (l=0; l < 3; l++) { /*NO MAXIMO RODA 2 VEZES*/

						/*PEÇA VIRADA PARA CIMA*/
						if (x%2 == y%2) {
							/*EMPARELHAR O LADO B DA MINHA PEÇA COM O LADO A DA PEÇA NOVA*/
							matched = (playing_field.matrix[x].array[y].seq[b.firstIndex] == available_pieces.array[f].seq[a.secondIndex]) && (playing_field.matrix[x].array[y].seq[b.secondIndex] == available_pieces.array[f].seq[a.firstIndex]);
							newScore = score + playing_field.matrix[x].array[y].seq[b.firstIndex] + playing_field.matrix[x].array[y].seq[b.secondIndex];
						/*PEÇA VIRADA PARA BAIXO*/
						} else {
							/*EMPARELHAR O LADO B DA MINHA PEÇA COM O LADO C DA PEÇA NOVA*/
							matched = (playing_field.matrix[x].array[y].seq[b.firstIndex] == available_pieces.array[f].seq[c.secondIndex]) && (playing_field.matrix[x].array[y].seq[b.secondIndex] == available_pieces.array[f].seq[c.firstIndex]);
							newScore = score + playing_field.matrix[x].array[y].seq[b.firstIndex] + playing_field.matrix[x].array[y].seq[b.secondIndex];
						}

						if (matched) {
							newPlayingField = playing_field;
							/*COLOCA A PEÇA DE NOVO NO TABULEIRO*/
							newPlayingField.matrix[x].array[y-1] = available_pieces.array[f];

							newAvailablePieces = available_pieces;

							/*PEÇA DEIXA DE ESTAR DISPONIVEL*/
							newAvailablePieces.array[f].seq[0] = -1;

							recursive_method (num_parts-1, x, y+1, newAvailablePieces, newPlayingField, newScore);

							/*TODO: SE SOBRAR APENAS UMA PEÇA, TESTA LOGO SE A PODE COLOCAR OU NAO EM VEZ DE ESTAR A CHAMAR RECURSIVAMENTE OUTRA VEZ*/

							break; /*uma peça nao pode ter 2 lados que encaixem num lado de outra peça portanto podemos sair logo*/

						} else {
							/*SO RODA A PEÇA SE NÂO HOUVER MATCH DE UM LADO*/
							rotate_piece(&available_pieces.array[z]);
						}
					}
				}
			}
		} else if ((y % 2 == x% 2) && playing_field.matrix[x+1].array[y].seq[0] == -1){ 	/*COMEÇAR A PREENCHER ABAIXO*/
			for (z = 1; z < num_partsCopy; z++) {

			}
		} else {
			for (z = 1; z < num_partsCopy; z++){

			}
		}







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

/* print status of the game */
void printField (MatrixPieces playing_field) {
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
									printf("%d", playing_field.matrix[i].array[j].seq[1]);
								} else {
									printf(" ");
								}
							} else {
								if (k == 0){
									printf("%d", playing_field.matrix[i].array[j].seq[0]);
								} else if (k == 1) {
									printf(" ");
								} else {
									printf("%d", playing_field.matrix[i].array[j].seq[2]);
								}
							}
						} else {
							if (m == 0) {
								if (k == 0){
									printf("%d", playing_field.matrix[i].array[j].seq[0]);
								} else if (k == 1) {
									printf(" ");
								} else {
									printf("%d", playing_field.matrix[i].array[j].seq[2]);
								}
							} else {
								if (k == 0){
									printf(" ");
								} else if (k == 1) {
									printf("%d", playing_field.matrix[i].array[j].seq[1]);
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

void establishSides() {
	a.firstIndex = 0;
	a.secondIndex = 1;
	b.firstIndex = 1;
	b.secondIndex = 2;
	c.firstIndex = 0;
	c.secondIndex = 2;
}
