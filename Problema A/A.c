#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define MAX_PIECES 2

/* STRUCTS AND CONSTANTS ------------------------------------------------------------*/
typedef struct {
	int firstIndex, secondIndex;
} Side;

typedef struct {
	int seq[3];
} Piece;

Side a,b,c;

struct Playing_field_coords {
	int x, y;
};

int num_parts = 1, score = 0, scoreIndex = 0;
int z, o, l, length;
int scores[200]; /*isto nao esta muito bem assim mas q safoda por agr*/

/*cada peça voltada para cima tem de ter 3 vizinhos voltados para baixo e vice versa*/

/* PROTOTYPES ---------------------------------------------------------------------*/
void rotate_piece (Piece * my_piece);
int isEmpty (int x, int y);
void printField (Piece (* playing_field)[MAX_PIECES*2]);
void establishSides();
void putOnPosition (int x, int y, Piece* available_pieces, int index, Piece (* playing_field)[MAX_PIECES*2]);
int recursive_method (int num_parts, int x, int y, Piece available_pieces[], Piece playing_field[MAX_PIECES*2][MAX_PIECES*2], int score);
int checkMatch(Piece* myPiece, int x, int y, Piece available_pieces[], char insertOrientation, int* score, Piece playing_field[MAX_PIECES*2][MAX_PIECES*2], int rotation, int availablePieceIndex);

/*FUNCTIONS ---------------------------------------------------------------------*/
int main(int argc, char const *argv[]) {

	Piece available_pieces[MAX_PIECES];
	Piece playing_field[MAX_PIECES*2][MAX_PIECES*2]; /* se x e y tiverem a mesma paridade, entao a face é voltada para cima; caso contrário a face é voltada para baixo*/

	/*inicializar indices de orientação das peças*/
	establishSides();

	/*in the begining everything is empty -1*/
	memset (playing_field, -1, sizeof(playing_field));
	memset (scores, -1, sizeof(scores));

	while(scanf("%d %d %d",&available_pieces[num_parts - 1].seq[0], &available_pieces[num_parts - 1].seq[1],&available_pieces[num_parts - 1].seq[2]) != EOF && num_parts < MAX_PIECES ) {
		num_parts++;
	}

	/*coloca a primeira peça no centro*/
	putOnPosition ((MAX_PIECES*2)/2, (MAX_PIECES*2)/2, available_pieces, 0, playing_field);

	/* imprimir tabuleiro
	printField(playing_field);
	*/

	length = recursive_method(num_parts-1, (MAX_PIECES*2)/2, (MAX_PIECES*2)/2, available_pieces, playing_field, score);

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
	int rotation = 0, availablePieceIndex = 1;
	if (num_parts == 0){
		scores[scoreIndex] = score;
		scoreIndex++;
		return scoreIndex;
	} else {
		if (playing_field[x-1][y].seq[0] == -1){ 	/*COMEÇAR A PREENCHER À ESQUERDA*/
			if (checkMatch (&playing_field[x][y], x-1, y, available_pieces, 'e', &score, playing_field, rotation, availablePieceIndex) != -404){
				/*SÓ CHAMAMOS RECURSIVAMENTE O MÉTODO SE O VIZINHO FOR PREENCHIDO*/
				recursive_method (num_parts -1, x-1, y, available_pieces, playing_field, score);
			}
		}
		if (playing_field[x+1][y].seq[0] == -1) {  /*COMEÇAR A PREENCHER À DIREITA*/
			if (checkMatch (&playing_field[x][y], x+1, y, available_pieces, 'd', &score, playing_field, rotation, availablePieceIndex) != -404){
				recursive_method (num_parts -1, x+1, y, available_pieces, playing_field, score);
			}
		}
		if (x % 2 == y % 2 && playing_field[x][y+1].seq[0] == -1) { /*COMEÇAR A PREENCHER ACIMA*/
			if (checkMatch (&playing_field[x][y], x, y+1, available_pieces, 'c', &score, playing_field, rotation, availablePieceIndex) != -404){
				recursive_method (num_parts -1, x, y+1, available_pieces, playing_field, score);
			}
		} else if (x % 2 != y % 2 && playing_field[x][y-1].seq[0] == -1) {  /*COMEÇAR A PREENCHER ABAIXO*/
			if (checkMatch (&playing_field[x][y], x, y-1, available_pieces, 'b', &score, playing_field, rotation, availablePieceIndex) != -404){
				recursive_method (num_parts -1, x, y-1, available_pieces, playing_field, score);
			}
		} else {
			scores[scoreIndex] = score;
			scoreIndex++;
			return scoreIndex;
		}
	}
	return scoreIndex;
}

/*method that checks any possible neighbour to put on field*/
int checkMatch(Piece* myPiece, int x, int y, Piece available_pieces[], char insertOrientation, int* score, Piece playing_field[MAX_PIECES*2][MAX_PIECES*2], int rotation, int availablePieceIndex) {
	int foundRotation = 0;
	int foundPiece = 0;
	/*testar todas as combinações com peças disponiveis ainda para jogar*/
	for ( z = availablePieceIndex +1; z < num_parts; ++z) {
		/*se a peça ainda nao tiver no tabuleiro*/
		if (available_pieces[z].seq[0] != -1) {
			if (insertOrientation == 'e') {

				if (x % 2 == y % 2) { /*INSERIR PEÇA VOLTADA PARA CIMA*/
					for (o = rotation + 1; o < 2; o++) {	/*NO MAXIMO RODO 2 VEZES*/
						/*EMPARELHAR O LADO C DA MINHA PEÇA COM O LADO B DA PEÇA NOVA*/
						if (!(myPiece->seq[c.firstIndex] == available_pieces[z].seq[b.secondIndex] && myPiece->seq[c.secondIndex] == available_pieces[z].seq[b.firstIndex])) {
							rotate_piece(&available_pieces[z]);
						} else {
							/*volta se a chamar recursivamente se ainda houver rotações por experimentar*/
							checkMatch(myPiece, x, y, available_pieces, insertOrientation, score, playing_field, o, z);
							score += myPiece->seq[c.firstIndex] + myPiece->seq[c.secondIndex];
							foundRotation = 1;
							break;
						}
					}
				} else { /*INSERIR PEÇA VOLTADA PARA BAIXO*/
					for (o = rotation; o < 2; o++) {
						/*EMPARELHAR O LADO A DA MINHA PEÇA COM O LADO B DA PEÇA NOVA*/
						if (!(myPiece->seq[a.firstIndex] == available_pieces[z].seq[b.secondIndex] && myPiece->seq[a.secondIndex] == available_pieces[z].seq[b.firstIndex])) {
							rotate_piece(&available_pieces[z]);
						} else {
							/*volta se a chamar recursivamente se ainda houver rotações por experimentar*/
							checkMatch(myPiece, x, y, available_pieces, insertOrientation, score, playing_field, o, z);
							score += myPiece->seq[a.firstIndex] + myPiece->seq[a.secondIndex];
							foundRotation = 1;
							break;
						}
					}
				}

			} else if (insertOrientation == 'd') {

				if (x % 2 == y % 2) { /*INSERIR PEÇA VOLTADA PARA CIMA*/
					for (o = rotation; o < 2; o++) {	/*NO MAXIMO RODO 2 VEZES*/
						/*EMPARELHAR O LADO B DA MINHA PEÇA COM O LADO A DA PEÇA NOVA*/
						if (!(myPiece->seq[b.firstIndex] == available_pieces[z].seq[a.secondIndex] && myPiece->seq[b.secondIndex] == available_pieces[z].seq[a.firstIndex])) {
							rotate_piece(&available_pieces[z]);
						} else {
							/*volta se a chamar recursivamente se ainda houver rotações por experimentar*/
							checkMatch(myPiece, x, y, available_pieces, insertOrientation, score, playing_field, o, z);
							score += myPiece->seq[b.firstIndex] + myPiece->seq[b.secondIndex];
							foundRotation = 1;
							break;
						}
					}
				} else { /*INSERIR PEÇA VOLTADA PARA BAIXO*/
					for (o = rotation; o < 2; o++) {
						/*EMPARELHAR O LADO B DA MINHA PEÇA COM O LADO C DA PEÇA NOVA*/
						if (!(myPiece->seq[b.firstIndex] == available_pieces[z].seq[c.secondIndex] && myPiece->seq[b.secondIndex] == available_pieces[z].seq[c.firstIndex])) {
							rotate_piece(&available_pieces[z]);
						} else {
							/*volta se a chamar recursivamente se ainda houver rotações por experimentar*/
							checkMatch(myPiece, x, y, available_pieces, insertOrientation, score, playing_field, o, z);
							score += myPiece->seq[b.firstIndex] + myPiece->seq[b.secondIndex];
							foundRotation = 1;
							break;
						}
					}
				}

			} else if (insertOrientation == 'c') { /*INSERIR PEÇA VOLTADA PARA CIMA*/
				for (o = rotation; o < 2; o++) {	/*NO MAXIMO RODO 2 VEZES*/
					/*EMPARELHAR O LADO A DA MINHA PEÇA COM O LADO C DA PEÇA NOVA*/
					if (!(myPiece->seq[a.firstIndex] == available_pieces[z].seq[c.secondIndex] && myPiece->seq[a.secondIndex] == available_pieces[z].seq[c.firstIndex])) {
						rotate_piece(&available_pieces[z]);
					} else {
						/*volta se a chamar recursivamente se ainda houver rotações por experimentar*/
						checkMatch(myPiece, x, y, available_pieces, insertOrientation, score, playing_field, o, z);
						score += myPiece->seq[a.firstIndex] + myPiece->seq[a.secondIndex];
						foundRotation = 1;
						break;
					}
				}
			} else { /*INSERIR PEÇA VOLTADA PARA BAIXO*/
				for (o = rotation; o < 2; o++) {	/*NO MAXIMO RODO 2 VEZES*/
					/*EMPARELHAR O LADO C DA MINHA PEÇA COM O LADO A DA PEÇA NOVA*/
					if (!(myPiece->seq[c.firstIndex] == available_pieces[z].seq[a.secondIndex] && myPiece->seq[c.secondIndex] == available_pieces[z].seq[a.firstIndex])) {
						rotate_piece(&available_pieces[z]);
					} else {
						/*volta se a chamar recursivamente se ainda houver rotações por experimentar*/
						checkMatch(myPiece, x, y, available_pieces, insertOrientation, score, playing_field, o, z);
						score += myPiece->seq[c.firstIndex] + myPiece->seq[c.secondIndex];
						foundRotation = 1;
						break;
					}
				}
			}
			if (foundRotation == 1) {
				foundPiece = 1;
				/*SE ENCONTROU UMA POSIÇÃO DA PEÇA ADEQUADA, VAI VERIFICAR RECURSIVAMENTE A OUTRA A OUTRA ROTAÇÃO*/
				putOnPosition (x, y, available_pieces, z, playing_field);
				checkMatch(myPiece, x, y, available_pieces, insertOrientation, score, playing_field, o, z);
				return *score;
			}

		}
	}
	/*SE ENCONTROU UMA PEÇA ADEQUADA*/
	if (foundPiece == 1) {
		return *score;
	} else {
		/*NAO ENCONTROU NENHUMA PEÇA ADEQUADA*/
		return -404;
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

/*coloca no tabuleiro o vizinho escolhido e torna indisponivel a peça para voltar a jogar*/
void putOnPosition (int x, int y, Piece* available_pieces, int index, Piece (* playing_field)[MAX_PIECES*2]) {
	playing_field[x][y].seq[0] = available_pieces[index].seq[0];
	playing_field[x][y].seq[1] = available_pieces[index].seq[1];
	playing_field[x][y].seq[2] = available_pieces[index].seq[2];
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

void establishSides() {
	a.firstIndex = 0;
	a.secondIndex = 1;
	b.firstIndex = 1;
	b.secondIndex = 2;
	c.firstIndex = 0;
	c.secondIndex = 2;
}
