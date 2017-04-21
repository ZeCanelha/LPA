#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

/*GLOBAL VARIABLES*/
char goal[8];
int grauMax; /*grau do maior polinÃƒÆ’Ã‚Â³mio*/
int z;
int x;
char st[2];
int *goalCoeficients;
int **restrictionsCoeficients;
int restrictionsB[46][3]; /*valores de b e comparadores das restriÃƒÆ’Ã‚Â§ÃƒÆ’Ã‚Âµes*/
int j[46];
int maximize;
int num_restricoes;


/*PROTOTYPES*/
int parse(char* function, int flag, int index);
int branchAndBound(int* varFixas, long int* best, int* usadas, int* incumbentes, int* array, int n, int* numNo);
int g(int* varFixas, int* usadas);
long int bounding(int* vector1, int* vector2);
int accept(int* vars);
int check(int* varFixas, int* usadas);
int cmp (const void *pa, const void *pb );
int check(int* varFixas, int* usadas);

/*MAIN FUNCTION*/
int main(){
    int i, k;
    long int best;

    goalCoeficients = (int*) malloc(46*sizeof(int));
    restrictionsCoeficients = (int**) malloc(1000*sizeof(int*));

    for(k = 0; scanf("%s", goal) != EOF; k++) {
        num_restricoes = 0;

        grauMax = 0;
        if (strcmp(goal, "maximize") == 0){
            best = -2147483648;
            z = 1;
            x = 0;
            maximize = 1;
        } else {
            best = 2147483648;
            z = 0;
            x = 1;
            maximize = 0;
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
            token3 = strtok_r(NULL, "><=", &endString);
            restrictionsB[i][1] = atoi(token3);
            restrictionsB[i][2] = i;

            scanf("%s", restriction);
        }
        num_restricoes = i;

        qsort(restrictionsB, num_restricoes, sizeof (restrictionsB[0]), cmp);

        if (i != 0) {        /*Se tem restriÃƒÆ’Ã‚Â§ÃƒÆ’Ã‚Âµes...*/
            int numNo = 1;
            int usadas[46];
            memset(usadas, -1, sizeof(int) * grauMax);
            int array[46];
            memset(array, -1, sizeof(int) * grauMax);
            int incumbentes[46];
            memset(incumbentes, -1, sizeof(int) * grauMax);
            int varFixas[46];
            memset(varFixas, -1, sizeof(int) * grauMax);

            branchAndBound(varFixas, &best, usadas, incumbentes, array, 0, &numNo);
        }
        if(best == 2147483648 || best == -2147483648){
            printf("INFEASIBLE\n");
        } else {
            printf("%ld\n", best);
        }

    }
    return 0;
}


int branchAndBound(int* varFixas, long int* best, int* usadas, int* incumbentes, int* array, int n, int* numNo) {
    int i, upperBound, k;

    if(n == grauMax+1)  /*base case*/
        return 1;

    array[n] = (*numNo)++;

    upperBound = g(varFixas, usadas);
    if(((upperBound >= *best) && maximize == 0) || ((upperBound <= *best) && maximize == 1))    /*bounding test*/
        return 1;


    if(accept(usadas)) {       /*Update*/
        for(i = 0; i <= grauMax; i++) {
            incumbentes[i] = usadas[i];
        }
        (*best) = upperBound;
        return 1;
    }

    if(!check(varFixas, usadas)) {
        return 1;
    }

    varFixas[n] = 1;
    k = n + 1;
    branchAndBound(varFixas, best, usadas, incumbentes, array, n + 1, numNo);
    while (k <= grauMax) {
        array[k] = -1;
        varFixas[k] = -1;
        k++;
    }

    varFixas[n] = 0;
    branchAndBound(varFixas, best, usadas, incumbentes, array, n + 1, numNo);
    while (k <= grauMax) {
        array[k] = -1;
        varFixas[k] = -1;
        k++;
    }

    return 1;
}

long int bounding(int* coefficients, int* usadas) {
    long int bound = 0;
    int k = 0;
    while (k <= grauMax) {
        bound += (coefficients[k] * usadas[k]);
        k++;
    }
    return bound;
}

int accept(int* vars) {
    int feasible = 1, i = 0;

    while(feasible && (i < num_restricoes)) {
        int bValue = restrictionsB[i][1];
        int* coefficients = restrictionsCoeficients[restrictionsB[i][2]];
        int comparator = restrictionsB[i][0];


        long int bound = bounding(coefficients, vars);
        if(comparator == 1) {
            feasible = feasible && (bound <= bValue);
        } else if (comparator == 2) {
            feasible = feasible && (bound >= bValue);
        } else if (comparator == 3) {
            feasible = feasible && (bound == bValue);
        } else if (comparator == 4) {
            feasible = feasible && (bound < bValue);
        } else {
            feasible = feasible && (bound > bValue);
        }
        i++;
    }

    return feasible;
}

int g(int* varFixas, int* usadas) {
    int i, j, coef;
    for(i = 0; i <= grauMax; i++) {
        int coef = varFixas[i];
        if(coef == -1) {
            break;
        }
        usadas[i] = coef;
    }

    for(j = i; j <= grauMax; j++) {
        usadas[j] = -1;
    }

    while (i <= grauMax) {
        coef = goalCoeficients[i];
        if(coef > 0) {
            usadas[i] = z;
        } else if(coef < 0) {
            usadas[i] = x;
        } else {
            usadas[i] = 0;
        }
        i++;
    }

    return bounding(goalCoeficients, usadas);
}

int parse(char* function, int flag, int index) {

    int * coeficients ;
    int coeficiente = 0;
    int grauAtual = 0;
    char *endString, *endToken;
    char *copy = strdup(function);
    char *e;
    char temp1;

    if (!flag) { /*goal function*/
        goalCoeficients = (int*) malloc(46*sizeof(int));
        coeficients = goalCoeficients;
    } else {    /*restrictions*/
        restrictionsCoeficients[index] = (int*) malloc(46*sizeof(int));
        coeficients = restrictionsCoeficients[index];
    }
    char temp = function[0];

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
            e = strchr(token, 'x');
            if (e != 0) {
                char *token2 = strtok_r(token, "x", &endToken);
                if(temp == '-'){
                    coeficiente = -1*atoi(token2);
                } else {
                    coeficiente = atoi(token2);
                }
                token2 = strtok_r(NULL, "x", &endToken);
                grauAtual = atoi(token2);
                token2 = strtok_r(NULL, "x", &endToken);
            } else {
                if(temp == '-'){
                    coeficiente = -1*atoi(token);
                } else {
                    coeficiente = atoi(token);
                }
                grauAtual = 0;
            }
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

int cmp (const void *pa, const void *pb )
{
    const int *a = (const int *) pa;
    const int *b = (const int *) pb;
    if (abs(a[1]) < abs(b[1]))
        return -1;
    return (abs(b[1]) < abs(a[1]));
}


int check(int* varFixas, int* usadas) {
    int feasible = 1, i, k, n, high, low,  p, m;

    for(i = 0; feasible && (i < num_restricoes); i++) {
        for(p = 0; p <= grauMax; p++) {
            int coef = varFixas[p];
            if(coef == -1) {
                break;
            }
            usadas[p] = coef;
        }

        for(m = p; m <= grauMax; m++) {
            usadas[m] = -1;
        }

        int bValue = restrictionsB[i][1];
        int* coefficients = restrictionsCoeficients[restrictionsB[i][2]];
        int comparator = restrictionsB[i][0];


        high = 2147483648;
        if((comparator == 2) || (comparator == 3) || (comparator == 5)) {

            for(k = p; k <= grauMax; k++) {
                n = coefficients[k];
                if(n > 0) {
                    usadas[k] = 1;
                } else if(n < 0) {
                    usadas[k] = 0;
                } else {
                    usadas[k] = 0;
                }
            }

            high = bounding(coefficients, usadas);
        }

        low = -2147483648;
        if((comparator == 1) || (comparator == 3) || (comparator == 4)) {
            for(k = p; k <= grauMax; k++) {
                n = coefficients[k];
                if(n > 0) {
                    usadas[k] = 0;
                } else if(n < 0) {
                    usadas[k] = 1;
                } else {
                    usadas[k] = 0;
                }
            }
            low = bounding(coefficients, usadas);
        }

        feasible = (feasible && (low <= bValue) && (bValue <= high));
    }

    return feasible;
}
