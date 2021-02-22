#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <time.h>

//Funciones prototipo
int capturar_tamano(void);
int ** crear_matriz(int**, int);
void poblar_matriz(int**, int);



int main(){
    srand(time(NULL));
    int n = capturar_tamano();
    int **matriz = NULL;
    matriz = crear_matriz(matriz, n);
    poblar_matriz(matriz,n);
    free(matriz);
    return 0;
}

//Captura el tamaño de la matriz
int capturar_tamano(){
    int n = 0;
    printf("n: ");
    while(n<=0){
        scanf("%d",&n);
        if(n<=0){
            printf("Por favor ingrese un entero positivo");
        }
    }
    return n;
}

//Reserva el espacio en memoria para la matriz
int ** crear_matriz(int **matriz, int n){
    /*Se crea un apuntador a apuntadores, estos apuntadores apuntaran a las 'columnas'
    que seran espacios de memoria reservados para los datos de cada fila.

    m = {p1, p2, p3,...,pn}
    donde p1 -> {a11, a12, a13,..., a1n}
          p2 -> {a21, a22, a23,..., a2n}
          .
          .
          .
          pn -> {an1, an2, an3,..., ann}

    */
    matriz = (int**) malloc(n * sizeof(int));
    for(int i=0;i<n;i++){
        matriz[i] = (int *) malloc(n * sizeof(int));
    }
    return(matriz);
}

//Llena la matriz con enteros positivos aleatorios
void poblar_matriz(int ** matriz, int n){
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            matriz[i][j] = rand()%100; //entero maximo = 100
        }
    }
}
