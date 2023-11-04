// matriz.h
#ifndef MATRIZ_H
#define MATRIZ_H

typedef struct Celula {
    struct Celula* direita;
    struct Celula* abaixo;
    int linha;
    int coluna;
    float valor;
} Celula;

typedef struct {
    Celula* cabeca;
    int nlin;
    int ncol;
} Matriz;

Matriz criaMatriz(int nlin, int ncol);
void insere(Matriz* A, int i, int j, float v);
void retira(Matriz* A, int i, int j);
void imprimeMatriz(Matriz A);
Matriz leMatriz();
Matriz somaMatrizes(Matriz A, Matriz B);
Matriz multiplicaMatrizes(Matriz A, Matriz B);

#endif
