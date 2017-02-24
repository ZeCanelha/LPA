#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define MAX_PIECES 6

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
int num_parts = 1;
long maxValue = 0;
long score = 0;

/*TODO: temos que fazer e desfazer o tabuleiro e as available_pieces em vez de passar copias*/
/*TODO: RESOLVER SITUAÇÃO EM Q APARECEM BURACOS*/

/*cada peça voltada para cima tem de ter 3 vizinhos voltados para baixo e vice versa*/

/* PROTOTYPES ---------------------------------------------------------------------*/
void rotate_piece (Piece * my_piece);
int isEmpty (int x, int y);
void printField (MatrixPieces playing_field);
void establishSides();
MatrixPieces putOnPosition (int x, int y, ArrayPieces available_pieces, int index, MatrixPieces playing_field);
void recursive_method (int num_parts, ArrayPieces used_pieces, ArrayPieces available_pieces, MatrixPieces playing_field, int score);
ArrayPieces disablePiece (ArrayPieces available_pieces, int index);

/*FUNCTIONS ---------------------------------------------------------------------*/
int main(int argc, char const *argv[]) {
	int im;
	MatrixPieces playing_field;
	ArrayPieces available_pieces;
	ArrayPieces used_pieces;

	/*inicializar indices de orientação das peças*/
	establishSides();

	/*in the begining everything is empty -1*/
	memset (playing_field.matrix, -1, sizeof(playing_field.matrix));
	memset (available_pieces.array, -1, sizeof(available_pieces.array));
	memset (used_pieces.array, -1 , sizeof(used_pieces.array));

	while(scanf("%d %d %d",&available_pieces.array[num_parts - 1].seq[0], &available_pieces.array[num_parts - 1].seq[1],&available_pieces.array[num_parts - 1].seq[2]) != EOF && num_parts < MAX_PIECES ) {
		num_parts++;
	}
	num_partsCopy = num_parts;

	/*
	for (im = 0; im < num_partsCopy; im++) {
		/*coloca a primeira peça no centro
		playing_field.matrix[MAX_PIECES].array[MAX_PIECES] = available_pieces.array[im];

		/* Actualiza a lista de peças usadas */
		/* TODO: Se actualizar aqui a lista das peças usadas estou sempre a passar um array com + 1 peço nova */
		/* TODO: mxPain solution; escolher a melhor peça;

		recursive_method(num_parts, used_pieces, available_pieces, playing_field, score);
	} */

	playing_field.matrix[MAX_PIECES].array[MAX_PIECES] = available_pieces.array[0];

	used_pieces.array[0].x = MAX_PIECES;
	used_pieces.array[0].y = MAX_PIECES;

	recursive_method(num_parts, used_pieces, available_pieces, playing_field, score,1);

	printf("%ld\n", maxValue);
	return 0;
}

void recursive_method (int num_parts, ArrayPieces used_pieces, ArrayPieces available_pieces, MatrixPieces playing_field, int score, int used_array_size) {
	/*cada vez que se invoca o metodo recursivo uma copia do tabuleiro e das peças disponiveis tem que ser guardada*/
	int newScore = 0;
	int matched = 0;
	int f,z,v,h,q,l, n, m, tmp, i;
	int x, y;

	/*TODO:adicionar outro caso base: se ja nao houver match de peça nenhuma retorna logo sem registar score*/
	if (num_parts == 1){
		if (score >= maxValue){
			maxValue = score;
		}
		return;
	} else {

		/* Verificar se a peça encaixa num dos lados e criar um caminho recursivo para cada um dos lados */

		for ( z = 1; z < num_partsCopy; z++ )
		{
			/* Verificar se esta peça encaixa em qq uma do tabuleiro */
			/* Se a peça estiver disponível */
			/* TODO: Verificar até que ponto esta condição se verifica nesta nova recursão */
			if (available_pieces.array[z].seq[0] != -1){

				/* TODO: Esta variável está em falta, só pra ver a situação e como resolver ( used_array_size ) */

				for ( i = 0; i < used_array_size; i++ )
				{
					/* Se a peça tiver uma aresta disponivel á esquerda, começar a preencher á esquerda */
					x = used_pieces.array[i].x;
					y = used_pieces.array[i].y;

					if ( playing_field.matrix[x].array[y - 1].seq[0] == -1 )
					{
						/* Rotação da piça */

						for (l=0; l < 3; l++) { /*NO MAXIMO RODA 2 VEZES*/

							/*PEÇA VIRADA PARA CIMA*/
							if (x%2 == y%2) {

								/*EMPARELHAR O LADO A DA MINHA PEÇA COM O LADO B DA PEÇA NOVA*/
								matched = (playing_field.matrix[x].array[y].seq[a.firstIndex] == available_pieces.array[z].seq[b.secondIndex]) && (playing_field.matrix[x].array[y].seq[a.secondIndex] == available_pieces.array[z].seq[b.firstIndex]);
								/*printf("EMPARELHEI COM PEÇA VIRADA PARA CIMA à ESQUERDA: %d\n", matched);*/
								newScore = score + playing_field.matrix[x].array[y].seq[a.firstIndex] + playing_field.matrix[x].array[y].seq[a.secondIndex];
							/*PEÇA VIRADA PARA BAIXO*/
							} else {

								/*EMPARELHAR O LADO C DA MINHA PEÇA COM O LADO B DA PEÇA NOVA*/
								matched = (playing_field.matrix[x].array[y].seq[c.firstIndex] == available_pieces.array[z].seq[b.firstIndex]) && (playing_field.matrix[x].array[y].seq[c.secondIndex] == available_pieces.array[z].seq[b.secondIndex]);
								/*printf("EMPARELHEI COM PEÇA VIRADA PARA BAIXO à ESQUERDA: %d\n", matched);*/
								newScore = score + playing_field.matrix[x].array[y].seq[c.firstIndex] + playing_field.matrix[x].array[y].seq[c.secondIndex];
							}

							if (matched) {
								tmp = available_pieces.array[z].seq[0];

								/*COLOCA A PEÇA DE NOVO NO TABULEIRO*/
								playing_field.matrix[x].array[y-1] = available_pieces.array[z];
								available_pieces.array[z].x = x;
								available_pieces.array[z].y = y;
								used_pieces.array[used_array_size] = available_pieces.array[z];

								/*PEÇA DEIXA DE ESTAR DISPONIVEL*/
								available_pieces.array[z].seq[0] = -1;

								recursive_method (num_parts-1, used_pieces, available_pieces, playing_field, newScore, ++used_array_size);

								/*DESFAZ ALTERAÇÂONO TABULEIRO*/
								playing_field.matrix[x].array[y-1].seq[0] = -1;

								/*PEÇA VOLTA A ESTAR DISPONIVEL -> TODO: Grande FINO */
								available_pieces.array[z].seq[0] = tmp;

								/*TODO: SE SOBRAR APENAS UMA PEÇA, TESTA LOGO SE A PODE COLOCAR OU NAO EM VEZ DE ESTAR A CHAMAR RECURSIVAMENTE OUTRA VEZ*/
								break; /*uma peça nao pode ter 2 lados que encaixem num lado de outra peça portanto podemos sair logo*/
							} else {
								/*SO RODA A PEÇA SE NÂO HOUVER MATCH DE UM LADO*/
								rotate_piece(&available_pieces.array[z]);
							}
					}
				}
			}
		}

		/* Verificar se pode preencher á direita */

	}

		if (playing_field.matrix[x].array[y+1].seq[0] == -1){ 	/*COMEÇAR A PREENCHER À DIREITA*/
			/*CORRER AS PEÇAS DISPONIVEIS TODAS*/
			for (f = 1; f < num_partsCopy; f++) {/*testar todas as combinações com peças disponiveis ainda para jogar - TODO:OTIMIZAR ISTO PORQUE ITERATIVAMENTE DEMORA MUITO TEMPO*/
				if (available_pieces.array[f].seq[0] != -1) {
					for (q=0; q < 3; q++) { /*NO MAXIMO RODA 2 VEZES*/
						/*PEÇA VIRADA PARA CIMA*/
						if (x%2 == y%2) {
							/*EMPARELHAR O LADO B DA MINHA PEÇA COM O LADO C DA PEÇA NOVA*/
							matched = (playing_field.matrix[x].array[y].seq[b.firstIndex] == available_pieces.array[f].seq[c.firstIndex]) && (playing_field.matrix[x].array[y].seq[b.secondIndex] == available_pieces.array[f].seq[c.secondIndex]);
							/*printf("EMPARELHEI COM PEÇA VIRADA PARA CIMA à DIREITA: %d\n", matched);*/
							newScore = score + playing_field.matrix[x].array[y].seq[b.firstIndex] + playing_field.matrix[x].array[y].seq[b.secondIndex];
						/*PEÇA VIRADA PARA BAIXO*/
						} else {
							/*EMPARELHAR O LADO B DA MINHA PEÇA COM O LADO A DA PEÇA NOVA*/
							matched = (playing_field.matrix[x].array[y].seq[b.firstIndex] == available_pieces.array[f].seq[a.secondIndex]) && (playing_field.matrix[x].array[y].seq[b.secondIndex] == available_pieces.array[f].seq[a.firstIndex]);
							/*printf("EMPARELHEI COM PEÇA VIRADA PARA BAIXO à DIREITA: %d\n", matched);*/
							newScore = score + playing_field.matrix[x].array[y].seq[b.firstIndex] + playing_field.matrix[x].array[y].seq[b.secondIndex];
						}

						if (matched) {
							tmp = available_pieces.array[f].seq[0];

							/*COLOCA A PEÇA DE NOVO NO TABULEIRO*/
							playing_field.matrix[x].array[y+1] = available_pieces.array[f];

							/*PEÇA DEIXA DE ESTAR DISPONIVEL*/
							available_pieces.array[f].seq[0] = -1;

							recursive_method (num_parts-1, x, y+1, available_pieces, playing_field, newScore);

							/*DESFAZ ALTERAÇÂO NO TABULEIRO NO TABULEIRO*/
							playing_field.matrix[x].array[y+1].seq[0] = -1;

							/*PEÇA VOLTA A ESTAR DISPONIVEL*/
							available_pieces.array[f].seq[0] = tmp;

							/*TODO: SE SOBRAR APENAS UMA PEÇA, TESTA LOGO SE A PODE COLOCAR OU NAO EM VEZ DE ESTAR A CHAMAR RECURSIVAMENTE OUTRA VEZ*/
							break; /*uma peça nao pode ter 2 lados que encaixem num lado de outra peça portanto podemos sair logo*/

						} else {
							/*SO RODA A PEÇA SE NÂO HOUVER MATCH DE UM LADO*/
							rotate_piece(&available_pieces.array[f]);
						}
					}
				}
			}
		}

		/*COMEÇAR A PREENCHER ABAIXO*/
		if ((y % 2 == x% 2) && playing_field.matrix[x+1].array[y].seq[0] == -1){
			for (v = 1; v < num_partsCopy; v++) {/*testar todas as combinações com peças disponiveis ainda para jogar - TODO:OTIMIZAR ISTO PORQUE ITERATIVAMENTE DEMORA MUITO TEMPO*/
				if (available_pieces.array[v].seq[0] != -1) {
					for (h=0; h < 3; h++) { /*NO MAXIMO RODA 2 VEZES*/
						matched = (playing_field.matrix[x].array[y].seq[c.firstIndex] == available_pieces.array[v].seq[a.firstIndex]) && (playing_field.matrix[x].array[y].seq[c.secondIndex] == available_pieces.array[v].seq[a.secondIndex]);
						/*printf("EMPARELHEI COM PEÇA VIRADA PARA CIMA à ABAIXO: %d\n", matched);*/
						newScore = score + playing_field.matrix[x].array[y].seq[c.firstIndex] + playing_field.matrix[x].array[y].seq[c.secondIndex];
						if (matched) {
							tmp = available_pieces.array[v].seq[0];

							/*COLOCA A PEÇA DE NOVO NO TABULEIRO*/
							playing_field.matrix[x+1].array[y] = available_pieces.array[v];

							/*PEÇA DEIXA DE ESTAR DISPONIVEL*/
							available_pieces.array[v].seq[0] = -1;

							recursive_method (num_parts-1, x+1, y, available_pieces, playing_field, newScore);

							/*DESFAZ ALTERAÇÂO NO TABULEIRO NO TABULEIRO*/
							playing_field.matrix[x+1].array[y].seq[0] = -1;

							/*PEÇA VOLTA A ESTAR DISPONIVEL*/
							available_pieces.array[v].seq[0] = tmp;

							/*TODO: SE SOBRAR APENAS UMA PEÇA, TESTA LOGO SE A PODE COLOCAR OU NAO EM VEZ DE ESTAR A CHAMAR RECURSIVAMENTE OUTRA VEZ*/
							break; /*uma peça nao pode ter 2 lados que encaixem num lado de outra peça portanto podemos sair logo*/
						} else {
							/*SO RODA A PEÇA SE NÂO HOUVER MATCH DE UM LADO*/
							rotate_piece(&available_pieces.array[v]);
						}
					}
				}
			}
		}
		if ((y % 2 != x% 2) && playing_field.matrix[x-1].array[y].seq[0] == -1) {		/*COMEÇAR A PREENCHER ACIMA*/
			for (n = 1; n < num_partsCopy; n++) {/*testar todas as combinações com peças disponiveis ainda para jogar - TODO:OTIMIZAR ISTO PORQUE ITERATIVAMENTE DEMORA MUITO TEMPO*/
				if (available_pieces.array[n].seq[0] != -1) {
					for (m=0; m < 3; m++) { /*NO MAXIMO RODA 2 VEZES*/
						matched = (playing_field.matrix[x].array[y].seq[a.firstIndex] == available_pieces.array[n].seq[c.firstIndex]) && (playing_field.matrix[x].array[y].seq[a.secondIndex] == available_pieces.array[n].seq[c.secondIndex]);
						/*printf("EMPARELHEI COM PEÇA VIRADA PARA BAIXO à ACIMA: %d\n", matched);*/
						newScore = score + playing_field.matrix[x].array[y].seq[a.firstIndex] + playing_field.matrix[x].array[y].seq[a.secondIndex];
						if (matched) {
							tmp = available_pieces.array[n].seq[0];

							/*COLOCA A PEÇA DE NOVO NO TABULEIRO*/
							playing_field.matrix[x-1].array[y] = available_pieces.array[n];

							/*PEÇA DEIXA DE ESTAR DISPONIVEL*/
							available_pieces.array[n].seq[0] = -1;

							recursive_method (num_parts-1, x-1, y, available_pieces, playing_field, newScore);

							/*DESFAZ ALTERAÇÂO NO TABULEIRO NO TABULEIRO*/
							playing_field.matrix[x-1].array[y].seq[0] = -1;

							/*PEÇA VOLTA A ESTAR DISPONIVEL*/
							available_pieces.array[n].seq[0] = tmp;

							/*TODO: SE SOBRAR APENAS UMAPEÇA, TESTA LOGO SE A PODE COLOCAR OU NAO EM VEZ DE ESTAR A CHAMAR RECURSIVAMENTE OUTRA VEZ*/
							break; /*uma peça nao pode ter 2 lados que encaixem num lado de outra peça portanto podemos sair logo*/
						} else {
							/*SO RODA A PEÇA SE NÂO HOUVER MATCH DE UM LADO*/
							rotate_piece(&available_pieces.array[n]);
						}
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
