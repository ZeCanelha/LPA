/*TODO: RESOLVER SITUAÇÃO EM Q APARECEM BURACOS*/
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>

#define MAX_PIECES 20

/* STRUCTS AND CONSTANTS ------------------------------------------------------------*/
typedef struct {
	int firstIndex, secondIndex;
} Side;

typedef struct {
	int seq[3];
	int x, y;
} Piece;

Side a,b,c;

typedef struct {
	Piece array[MAX_PIECES*2];
} ArrayPieces;

typedef struct {
	ArrayPieces matrix[MAX_PIECES*2];
} MatrixPieces;

int num_partsCopy = 0;
long maxValue = 0;
long score = 0;

/* PROTOTYPES ---------------------------------------------------------------------*/
void rotate_piece (Piece * my_piece);
int isEmpty (int x, int y);
void printField (MatrixPieces playing_field);
void establishSides();
MatrixPieces putOnPosition (int x, int y, ArrayPieces available_pieces, int index, MatrixPieces playing_field);
void recursive_method (int num_parts, ArrayPieces used_pieces, ArrayPieces available_pieces, MatrixPieces playing_field, int score, int used_array_size);
ArrayPieces disablePiece (ArrayPieces available_pieces, int index);
ArrayPieces deleteFromArray(ArrayPieces myArray, int position, int n);

/*FUNCTIONS ---------------------------------------------------------------------*/
int main(int argc, char const *argv[]) {
	/* int im; */
	int num_parts = 0, used_array_size = 1;
	MatrixPieces playing_field;
	ArrayPieces available_pieces;
	ArrayPieces used_pieces;
	ArrayPieces newAvailablePieces;
	clock_t begin, end;
	double tempo;

	/*inicializar indices de orientação das peças*/
	establishSides();

	/*in the begining everything is empty -1*/
	memset (playing_field.matrix, -1, sizeof(playing_field.matrix));
	memset (available_pieces.array, -1, sizeof(available_pieces.array));
	memset (used_pieces.array, -1 , sizeof(used_pieces.array));

	while(scanf("%d %d %d",&available_pieces.array[num_parts].seq[0], &available_pieces.array[num_parts].seq[1],&available_pieces.array[num_parts].seq[2]) != EOF && num_parts < MAX_PIECES ) {
		num_parts++;
	}

	num_partsCopy = num_parts;

	/*
	* Actualiza a lista de peças usadas
	* TODO: Se actualizar aqui a lista das peças usadas estou sempre a passar um array com + 1 peço nova
	* TODO: mxPain solution; escolher a melhor peça;
			*coloca a primeira peça no centro*/
	begin = clock();
	used_pieces.array[0].x = MAX_PIECES;
	used_pieces.array[0].y = MAX_PIECES;

	playing_field.matrix[MAX_PIECES].array[MAX_PIECES] = available_pieces.array[0];
	/*elimina das available_pieces*/
	newAvailablePieces = deleteFromArray(available_pieces, 0, num_partsCopy - used_array_size);
	recursive_method(num_parts, used_pieces, newAvailablePieces, playing_field, score, 1);

	printf("%ld\n", maxValue);
		end = clock();

	tempo = (double)(end-begin)/CLOCKS_PER_SEC;
	printf("%f\n", tempo);
	return 0;
}

void recursive_method (int num_parts, ArrayPieces used_pieces, ArrayPieces available_pieces, MatrixPieces playing_field, int score, int used_array_size) {
	/*cada vez que se invoca o metodo recursivo uma copia do tabuleiro e das peças disponiveis tem que ser guardada*/
	int newScore = 0;
	int matched = 0;
	int h,q,l,it, il, t, ih, iq, id;
	int x, y;
	int used_array_sizeCopy = used_array_size;
	ArrayPieces newAvailablePieces;

	if (num_parts == 1){
		if (score >= maxValue){
			maxValue = score;
		}
		return;
	} else {
		/*TODO:nao pode ser até used_array_size*/
		for (it = 0; it < used_array_sizeCopy; it++) {

			x = used_pieces.array[it].x;
			y = used_pieces.array[it].y;

			/*INSERIR À ESQUERDA*/
			if ( playing_field.matrix[x].array[y - 1].seq[0] == -1 ) {
				for (il = 0; il < num_partsCopy - used_array_size; il++) {
					for (l=0; l < 3; l++) { /*NO MAXIMO RODA 2 VEZES*/
						/*PEÇA VIRADA PARA CIMA*/
						if (x%2 == y%2) {
							/*EMPARELHAR O LADO A DA MINHA PEÇA COM O LADO B DA PEÇA NOVA*/
							matched = (playing_field.matrix[x].array[y].seq[a.firstIndex] == available_pieces.array[il].seq[b.secondIndex]) && (playing_field.matrix[x].array[y].seq[a.secondIndex] == available_pieces.array[il].seq[b.firstIndex]);
							newScore = score + playing_field.matrix[x].array[y].seq[a.firstIndex] + playing_field.matrix[x].array[y].seq[a.secondIndex];
						/*PEÇA VIRADA PARA BAIXO*/
						} else {
							/*EMPARELHAR O LADO C DA MINHA PEÇA COM O LADO B DA PEÇA NOVA*/
							matched = (playing_field.matrix[x].array[y].seq[c.firstIndex] == available_pieces.array[il].seq[b.firstIndex]) && (playing_field.matrix[x].array[y].seq[c.secondIndex] == available_pieces.array[il].seq[b.secondIndex]);
							/*printf("EMPARELHEI COM PEÇA VIRADA PARA BAIXO à ESQUERDA: %d\n", matched);*/
							newScore = score + playing_field.matrix[x].array[y].seq[c.firstIndex] + playing_field.matrix[x].array[y].seq[c.secondIndex];
						}
						if (matched) {
							if (num_parts == 2){
								if (newScore >= maxValue){
									maxValue = newScore;
								}
								return;
							}
							available_pieces.array[il].x = x;
							available_pieces.array[il].y = y - 1;
							/*COLOCA NO TABULEIRO*/
							playing_field.matrix[x].array[y-1] = available_pieces.array[il];

							/*elimina das available_pieces*/
							newAvailablePieces = deleteFromArray(available_pieces, il, num_partsCopy - used_array_size);

							/*ACRESCENTA AO USED ARRAY*/
							used_array_sizeCopy++;

							used_pieces.array[used_array_size-1] = playing_field.matrix[x].array[y-1] ;

							recursive_method (num_parts-1, used_pieces, newAvailablePieces, playing_field, newScore, used_array_sizeCopy);

							/*DESFAZ ALTERAÇÂO NO TABULEIRO*/
							playing_field.matrix[x].array[y-1].seq[0] = -1;

							used_array_sizeCopy--;

							/*TODO: SE SOBRAR APENAS UMA PEÇA, TESTA LOGO SE A PODE COLOCAR OU NAO EM VEZ DE ESTAR A CHAMAR RECURSIVAMENTE OUTRA VEZ*/
							break; /*uma peça nao pode ter 2 lados que encaixem num lado de outra peça portanto podemos sair logo*/
						} else {
							/*SO RODA A PEÇA SE NÂO HOUVER MATCH DE UM LADO*/
							rotate_piece(&available_pieces.array[il]);
						}
					}
				}
			}

			/*INSERIR À DIREITA*/
			if ( playing_field.matrix[x].array[y + 1].seq[0] == -1 ) {
				for (iq = 0; iq < num_partsCopy - used_array_size; iq++) {
					for (q=0; q < 3; q++) { /*NO MAXIMO RODA 2 VEZES*/
						/*PEÇA VIRADA PARA CIMA*/
						if (x%2 == y%2) {
							/*EMPARELHAR O LADO B DA MINHA PEÇA COM O LADO C DA PEÇA NOVA*/
							matched = (playing_field.matrix[x].array[y].seq[b.firstIndex] == available_pieces.array[iq].seq[c.firstIndex]) && (playing_field.matrix[x].array[y].seq[b.secondIndex] == available_pieces.array[iq].seq[c.secondIndex]);
							/*printf("EMPARELHEI COM PEÇA VIRADA PARA CIMA à DIREITA: %d\n", matched);*/
							newScore = score + playing_field.matrix[x].array[y].seq[b.firstIndex] + playing_field.matrix[x].array[y].seq[b.secondIndex];
						/*PEÇA VIRADA PARA BAIXO*/
						} else {
							/*EMPARELHAR O LADO B DA MINHA PEÇA COM O LADO A DA PEÇA NOVA*/
							matched = (playing_field.matrix[x].array[y].seq[b.firstIndex] == available_pieces.array[iq].seq[a.secondIndex]) && (playing_field.matrix[x].array[y].seq[b.secondIndex] == available_pieces.array[iq].seq[a.firstIndex]);
							/*printf("EMPARELHEI COM PEÇA VIRADA PARA BAIXO à DIREITA: %d\n", matched);*/
							newScore = score + playing_field.matrix[x].array[y].seq[b.firstIndex] + playing_field.matrix[x].array[y].seq[b.secondIndex];
						}

						if (matched) {
							if (num_parts == 2){
								if (newScore >= maxValue){
									maxValue = newScore;
								}
								return;
							}

							available_pieces.array[iq].x = x;
							available_pieces.array[iq].y = y + 1;

							/*COLOCA A PEÇA DE NOVO NO TABULEIRO*/
							playing_field.matrix[x].array[y+1] = available_pieces.array[iq];

							/*elimina das available_pieces*/
							newAvailablePieces = deleteFromArray(available_pieces, iq, num_partsCopy - used_array_size);

							/*ACRESCENTA AO USED ARRAY*/
							used_array_sizeCopy++;
							used_pieces.array[used_array_size-1] = playing_field.matrix[x].array[y+1] ;

							recursive_method (num_parts-1, used_pieces, newAvailablePieces, playing_field, newScore, used_array_size);

							/*DESFAZ ALTERAÇÂO NO TABULEIRO*/
							playing_field.matrix[x].array[y+1].seq[0] = -1;

							used_array_sizeCopy--;


							break; /*uma peça nao pode ter 2 lados que encaixem num lado de outra peça portanto podemos sair logo*/
						} else {
							/*SO RODA A PEÇA SE NÂO HOUVER MATCH DE UM LADO*/
							rotate_piece(&available_pieces.array[iq]);
						}
					}
				}
			}

			/*INSERIR À BAIXO*/
			if ( (y % 2 == x% 2) && playing_field.matrix[x+1].array[y].seq[0] == -1) {
				for (ih = 0; ih < num_partsCopy - used_array_size; ih++) {
					for (h=0; h < 3; h++) { /*NO MAXIMO RODA 2 VEZES*/
						matched = (playing_field.matrix[x].array[y].seq[c.firstIndex] == available_pieces.array[ih].seq[a.firstIndex]) && (playing_field.matrix[x].array[y].seq[c.secondIndex] == available_pieces.array[ih].seq[a.secondIndex]);
						/*printf("EMPARELHEI COM PEÇA VIRADA PARA CIMA à ABAIXO: %d\n", matched);*/
						newScore = score + playing_field.matrix[x].array[y].seq[c.firstIndex] + playing_field.matrix[x].array[y].seq[c.secondIndex];

						if (matched) {
							if (num_parts == 2){
								if (newScore >= maxValue){
									maxValue = newScore;
								}
								return;
							}
							available_pieces.array[ih].x = x + 1;
							available_pieces.array[ih].y = y;

							/*COLOCA A PEÇA DE NOVO NO TABULEIRO*/
							playing_field.matrix[x+1].array[y] = available_pieces.array[ih];

							/*elimina das available_pieces*/
							newAvailablePieces = deleteFromArray(available_pieces, ih, num_partsCopy - used_array_size);

							/*ACRESCENTA AO USED ARRAY*/
							used_array_sizeCopy++;
							used_pieces.array[used_array_size-1] = playing_field.matrix[x+1].array[y];

							recursive_method (num_parts-1, used_pieces, newAvailablePieces, playing_field, newScore, used_array_size);

							/*DESFAZ ALTERAÇÂO NO TABULEIRO*/
							playing_field.matrix[x+1].array[y].seq[0] = -1;

							used_array_sizeCopy--;

							/*TODO: SE SOBRAR APENAS UMA PEÇA, TESTA LOGO SE A PODE COLOCAR OU NAO EM VEZ DE ESTAR A CHAMAR RECURSIVAMENTE OUTRA VEZ*/
							break; /*uma peça nao pode ter 2 lados que encaixem num lado de outra peça portanto podemos sair logo*/
						} else {
							/*SO RODA A PEÇA SE NÂO HOUVER MATCH DE UM LADO*/
							rotate_piece(&available_pieces.array[ih]);
						}
					}
				}
			}

			/*INSERIR À ACIMA*/
			if ( (y % 2 != x% 2) && playing_field.matrix[x-1].array[y].seq[0] == -1) {
				for (id = 0; id < num_partsCopy - used_array_size; id++) {
					for (t=0; t < 3; t++) { /*NO MAXIMO RODA 2 VEZES*/
						matched = (playing_field.matrix[x].array[y].seq[a.firstIndex] == available_pieces.array[id].seq[c.firstIndex]) && (playing_field.matrix[x].array[y].seq[a.secondIndex] == available_pieces.array[id].seq[c.secondIndex]);
						/*printf("EMPARELHEI COM PEÇA VIRADA PARA BAIXO à ACIMA: %d\n", matched);*/
						newScore = score + playing_field.matrix[x].array[y].seq[a.firstIndex] + playing_field.matrix[x].array[y].seq[a.secondIndex];

						if (matched) {
							if (num_parts == 2){
								if (newScore >= maxValue){
									maxValue = newScore;
								}
								return;
							}
							available_pieces.array[id].x = x - 1;
							available_pieces.array[id].y = y;

							/*COLOCA A PEÇA DE NOVO NO TABULEIRO*/
							playing_field.matrix[x-1].array[y] = available_pieces.array[id];

							/*elimina das available_pieces*/
							newAvailablePieces = deleteFromArray(available_pieces, id, num_partsCopy - used_array_size);

							/*ACRESCENTA AO USED ARRAY*/
							used_array_sizeCopy++;
							used_pieces.array[used_array_size-1] = playing_field.matrix[x-1].array[y];

							recursive_method (num_parts-1, used_pieces, newAvailablePieces, playing_field, newScore, used_array_size);

							/*DESFAZ ALTERAÇÂO NO TABULEIRO*/
							playing_field.matrix[x-1].array[y].seq[0] = -1;

							used_array_sizeCopy--;


							/*TODO: SE SOBRAR APENAS UMA PEÇA, TESTA LOGO SE A PODE COLOCAR OU NAO EM VEZ DE ESTAR A CHAMAR RECURSIVAMENTE OUTRA VEZ*/
							break; /*uma peça nao pode ter 2 lados que encaixem num lado de outra peça portanto podemos sair logo*/
						} else {
							/*SO RODA A PEÇA SE NÂO HOUVER MATCH DE UM LADO*/
							rotate_piece(&available_pieces.array[id]);
						}
					}
				}
			}

			if(!matched){
				if (score >= maxValue){
					maxValue = score;
				}
				return;
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

ArrayPieces deleteFromArray(ArrayPieces myArray, int position, int n) {
	int c;
      for ( c = position; c < n; c++ ){
         myArray.array[c] = myArray.array[c+1];
	 }
	return myArray;
}
