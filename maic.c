#include <stdio.h>
#include "matriz.h"



int main(void) {
    Matriz A, B, C;
    
    printf("Digite a matriz A:\n");
    A = leMatriz();
    
    printf("Matriz A:\n");
    imprimeMatriz(A);
    
    printf("Digite a matriz B:\n");
    B = leMatriz();
    
    printf("Matriz B:\n");
    imprimeMatriz(B);
    
    C = somaMatrizes(A, B);
    printf("Matriz A + B:\n");
    imprimeMatriz(C);
    
    C = multiplicaMatrizes(A, B);
    printf("Matriz A * B:\n");
    imprimeMatriz(C);

    
    return 0;
}
