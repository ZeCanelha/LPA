#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

/*GLOBAL VARIABLES*/
char goal[8];
int grauMax = 0; /*grau do maior polinómio*/
char st[2];
long int *goalCoeficients;
long int **restrictionsCoeficients;
long int restrictionsB[46][2]; /*valores de b e comparadores das restrições*/


/*PROTOTYPES*/
int branchAndBound();
int parse(char* function, int flag, int index);

/*MAIN FUNCTION*/
int main(){
    int i, k;
    clock_t begin = clock();
    goalCoeficients = (long int*) malloc(46*sizeof(int));
    restrictionsCoeficients = (long int**) malloc(1000*sizeof(long int*));

    for(k = 0; scanf("%s", goal) != EOF; k++) {
        int max = 0;
        if (strcmp(goal, "maximize") == 0){
            max = 1;
        }

        char goalFunction[100000];
        scanf("%s", goalFunction);

        parse(goalFunction, 0, 0);


        scanf("%s", st);

        char restriction[100000];
        scanf("%s", restriction);

        for (i = 0; restriction[0] != 'B'; i++) {
            int index;
            char *e, *token3, *endString;

            e = strchr(restriction, '=');
            if (e != 0) {
                index = (int)(e - restriction);
                if(restriction[index-1] == '<') { /*Menor ou igual*/
                    restrictionsB[i][0] = 1;
                } else if (restriction[index-1] == '>') {   /*Maior ou igual*/
                    restrictionsB[i][0] = 2;
                } else {                    /*Igual*/
                    restrictionsB[i][0] = 3;
                }
            } else {
                e = strchr(restriction, '<'); /*Menor*/
                if (e != 0) {
                    restrictionsB[i][0] = 4;
                } else {                        /*Maior*/
                    restrictionsB[i][0] = 5;
                }
            }

            token3 = strtok_r(restriction, "><=", &endString);
            parse(restriction,1,i);
            token3 = strtok_r(restriction, "><=", &endString);
            restrictionsB[i][1] = atoi(token3);

            scanf("%s", restriction);
        }

        branchAndBound();

    }
    clock_t end = clock();
    double time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
    printf("%lf\n", time_spent);
    return 0;
}

int parse(char* function, int flag, int index) {

    long int * coeficients ;
    long int coeficiente = 0;
    int grauAtual = 0;
    char *endString, *endToken;
    char *copy = strdup(function);
    char temp = function[0];
    char temp1;

    if (!flag) { /*goal function*/
        coeficients = goalCoeficients;
    } else {    /*restrictions*/
        restrictionsCoeficients[index] = (long int*) malloc(46*sizeof(long int));
        coeficients = restrictionsCoeficients[index];
    }

    char *token = strtok_r(function, "+-", &endString);
    while (token != NULL) {

        temp1 = copy[token-function+strlen(token)];

        if (token[0] == 'x') {
            coeficiente = 1;
            if(temp == '-'){
                coeficiente = -1;
            }

            char *token2 = strtok_r(token, "x", &endToken);
            grauAtual = atoi(token2);
            token2 = strtok_r(NULL, "x", &endToken);
            token2 = strtok_r(NULL, "x", &endToken);

        } else {
            char *token2 = strtok_r(token, "x", &endToken);
            if(temp == '-'){
                coeficiente = -1*atoi(token2);
            } else {
                coeficiente = atoi(token2);
            }
            token2 = strtok_r(NULL, "x", &endToken);
            grauAtual = atoi(token2);
            token2 = strtok_r(NULL, "x", &endToken);
        }

        coeficients[grauAtual] = coeficiente;
        if (grauAtual > grauMax) {
            grauMax = grauAtual;
        }

        token = strtok_r(NULL, "+-", &endString);
        temp = temp1;
    }
    return 1;
}

int branchAndBound() {

    return 0;
}
