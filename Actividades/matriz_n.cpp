#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>

//Funciones prototipo
int capturar_tamano(void);
int ** crear_matriz(int);
void poblar_matriz(int*);

int main(){
    int n = capturar_tamano();
    int **matriz = crear_matriz(n);
}

//Captura el tamaño de la matriz
int capturar_tamano(){
    int n = 0;
    printf("n: \n");
    while(n<=0){
        scanf("%d",&n);
        if(n<=0){
            printf("Por favor ingrese un entero positivo");
        }
    }
    return n;
}

//Reserva el espacio en memoria para la matriz
int ** crear_matriz(int n){
    int **matriz = (int**) malloc(n * sizeof(int));
    for(int i=0;i<n;i++){
        matriz[i] = (int *) malloc(n * sizeof(int));
    }
    return(matriz);
}