#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>

//Funciones prototipo
int capturar_tamano(void);
int * crear_matriz(int);
void poblar_matriz(int*);


int main(){
    int n = capturar_tamano();
    int *matriz = crear_matriz(n);
}


//Captura parametros
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

int * crear_matriz(int n){
    int *matriz = (int*) malloc(n * sizeof(int));
    return(matriz);
}