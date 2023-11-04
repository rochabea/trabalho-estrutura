#include <stdio.h>
#include <stdlib.h>
#include "matriz.h"

// Função para criar uma matriz vazia
Matriz criaMatriz(int nlin, int ncol) {
    Matriz A;
    A.nlin = nlin;
    A.ncol = ncol;
    A.cabeca = (Celula*)malloc(sizeof(Celula));
    A.cabeca->linha = -1;
    A.cabeca->coluna = -1;
    A.cabeca->valor = 0.0;
    A.cabeca->direita = A.cabeca;
    A.cabeca->abaixo = A.cabeca;

    return A;
}

// Função para inserir uma célula na linha i, coluna j da matriz A
void insere(Matriz *A, int i, int j, float v) {
    Celula *nova = (Celula*)malloc(sizeof(Celula));
    nova->linha = i;
    nova->coluna = j;
    nova->valor = v;

    Celula *anterior_l, *anterior_c, *atual_l, *atual_c;

    anterior_l = A->cabeca;
    atual_l = A->cabeca->abaixo;
    while (atual_l != A->cabeca && atual_l->linha < i) {
        anterior_l = atual_l;
        atual_l = atual_l->abaixo;
    }

    anterior_c = A->cabeca;
    atual_c = A->cabeca->direita;
    while (atual_c != A->cabeca && atual_c->coluna < j) {
        anterior_c = atual_c;
        atual_c = atual_c->direita;
    }

    if (atual_l->linha == i && atual_c->coluna == j) {
        // Célula já existe
        free(nova);
    } else {
        nova->abaixo = atual_l;
        anterior_l->abaixo = nova;
        nova->direita = atual_c;
        anterior_c->direita = nova;
    }
}

// Função para retirar uma célula da linha i, coluna j da matriz A
void retira(Matriz *A, int i, int j) {
    Celula *anterior_l, *anterior_c, *atual_l, *atual_c;

    anterior_l = A->cabeca;
    atual_l = A->cabeca->abaixo;
    while (atual_l != A->cabeca && atual_l->linha < i) {
        anterior_l = atual_l;
        atual_l = atual_l->abaixo;
    }

    anterior_c = A->cabeca;
    atual_c = A->cabeca->direita;
    while (atual_c != A->cabeca && atual_c->coluna < j) {
        anterior_c = atual_c;
        atual_c = atual_c->direita;
    }

    if (atual_l->linha == i && atual_c->coluna == j) {
        anterior_l->abaixo = atual_l->abaixo;
        anterior_c->direita = atual_c->direita;
        free(atual_l);
    }
}



void imprimeMatriz(Matriz A) {
    for (int i = 1; i <= A.nlin; i++) {
        Celula* linha_atual = A.cabeca->abaixo;

        for (int j = 1; j <= A.ncol; j++) {
            if (linha_atual != A.cabeca && linha_atual->coluna == j) {
                printf("%f ", linha_atual->valor);
                linha_atual = linha_atual->direita;
            } else {
                printf("0.0 ");
            }
        }
        printf("\n");
    }
}

Matriz leMatriz() {
    Matriz A;
    A.nlin = 0;
    A.ncol = 0;
    A.cabeca = criaCelula(-1, -1, 0.0);

    int m, n;
    printf("Digite o número de linhas e colunas: ");
    scanf("%d %d", &m, &n);

    A.nlin = m;
    A.ncol = n;

    int i, j;
    float valor;
    printf("Digite os elementos diferentes de zero (i, j, valor):\n");

    while (1) {
        if (scanf("%d %d %f", &i, &j, &valor) != 3) {
            break;
        }
        if (i <= m && j <= n) {
            insere(A.cabeca, i, j, valor);
        } else {
            printf("Coordenadas fora dos limites da matriz.\n");
        }
    }

    return A;
}

Matriz somaMatrizes(Matriz A, Matriz B) {
    if (A.nlin != B.nlin || A.ncol != B.ncol) {
        printf("As matrizes não têm o mesmo tamanho e não podem ser somadas.\n");
        exit(EXIT_FAILURE);
    }

    Matriz C;
    
    C.nlin = A.nlin;
    C.ncol = A.ncol;
    C.cabeca = criaCelula(-1, -1, 0.0);

    for (int i = 1; i <= A.nlin; i++) {
        Celula* linha_A = A.cabeca->abaixo;
        Celula* linha_B = B.cabeca->abaixo;

        for (int j = 1; j <= A.ncol; j++) {
            float soma = 0.0;

            if (linha_A != A.cabeca && linha_A->coluna == j) {
                soma += linha_A->valor;
                linha_A = linha_A->direita;
            }

            if (linha_B != B.cabeca && linha_B->coluna == j) {
                soma += linha_B->valor;
                linha_B = linha_B->direita;
            }

            if (soma != 0.0) {
                insere(&C, i, j, soma);
            }
        }
    }

    return C;
}

Matriz multiplicaMatrizes(Matriz A, Matriz B) {
    if (A.ncol != B.nlin) {
        printf("O número de colunas de A não é igual ao número de linhas de B. Multiplicação impossível.\n");
        exit(EXIT_FAILURE);
    }

    Matriz C;
    
    C.nlin = A.nlin;
    C.ncol = B.ncol;
    C.cabeca = criaCelula(-1, -1, 0.0);

    for (int i = 1; i <= A.nlin; i++) {
        for (int j = 1; j <= B.ncol; j++) {
            float produto = 0.0;
            Celula* linha_A = A.cabeca->abaixo;
            Celula* coluna_B = B.cabeca->direita;

            while (linha_A != A.cabeca && coluna_B != B.cabeca) {
                if (linha_A->coluna == coluna_B->linha) {
                    produto += linha_A->valor * coluna_B->valor;
                    linha_A = linha_A->direita;
                    coluna_B = coluna_B->abaixo;
                } else if (linha_A->coluna < coluna_B->linha) {
                    linha_A = linha_A->direita;
                } else {
                    coluna_B = coluna_B->abaixo;
                }
            }

            if (produto != 0.0) {
                insere(&C, i, j, produto);
            }
        }
    }

    return C;
}
