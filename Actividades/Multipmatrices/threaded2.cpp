#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <error.h>
#include <pthread.h>

#define nucleos 8
/*estructura para almacenar los datos que serán utilizados en la multiplicación de matrices, aquí se
empaquetan los parámetros que necesitamos en la operación
*/
typedef struct{
    int n = 0;
    int fila = 0;
    //int columna = 0;
    int **matriz1 = NULL, **matriz2 = NULL, **matrizResultado = NULL;
}estructura_matrices;

//Funciones prototipo
int capturar_tamano(void);
int ** crear_matriz(int**, int);
void poblar_matriz(int**, int);
void mostrar_matriz(int**, int);
void *producto_punto(void * estructura_matrices);

void multiplicar_matrices(estructura_matrices*,pthread_t*,int**,int**,int**,int);

int main(){
    srand(time(NULL));
    int n = capturar_tamano();
    int **matriz1 = NULL;
    int **matriz2 = NULL;
    int **matrizResultado = NULL;
    estructura_matrices * matrices;
    pthread_t *hilos = (pthread_t*) malloc(n*sizeof(pthread_t));  //Reserva de memoria para n*n hilos
    
    matriz1 = crear_matriz(matriz1, n);
    matriz2 = crear_matriz(matriz2, n);
    matrizResultado = crear_matriz(matrizResultado, n);

    poblar_matriz(matriz1, n);
    poblar_matriz(matriz2, n);

    clock_t inicio = clock();
    multiplicar_matrices(matrices,hilos,matriz1,matriz2,matrizResultado,n);
    for(int i=0;i<n;i++){
        pthread_join(hilos[i],NULL);
    }
    clock_t fin = clock();
    /*
    for(int i=0;i<(n*n);i++){
        pthread_join(hilos[i],NULL);
    }
    */

    //clock_t fin = clock();
    float segundos = (float)(fin - inicio) / CLOCKS_PER_SEC;
    
    
    /*
    mostrar_matriz(matriz1, n);
    mostrar_matriz(matriz2, n);
    mostrar_matriz(matrizResultado,n);
    */
    printf("La ejecucion ha tomado %.4f segundos\n", segundos);
    free(matrices);
    free(hilos);
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
            matriz[i][j] = rand()%10; //entero maximo = 100
        }
    }
}

void mostrar_matriz(int ** matriz, int n){
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            printf("m%d%d:%d ",i,j,matriz[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

//Realiza el producto punto entre filas de la matriz 1 y columnas de la matriz 2
void * producto_punto(void * matrices){
    /*Debido a la solución adaptada los parámetros se empaquetan en una estructura de datos, de la cual
    se envía su apuntador
    */
    
    estructura_matrices *datos = (estructura_matrices *) matrices;
    int n = datos->n, fila = datos->fila;
    for(int j=0;j<n;j++){
            /*Es necesario realizar este empaquetado de datos en nuevas estructuras por cada iteración,
            de otro modo es posible que la información a la que accedan los hilos no sea la que se requiere en la 
            lógica de la solución, es posible que un hilo accediera a un dato "futuro" y no al correspondiente
            */
            
            /*Asigna a matrizResultado[i][j] 
            el producto punto entre la fila i de la matriz1 y la columna j de la matriz2
            */
        datos->matrizResultado[fila][j] = 0;
        for(int i=0;i<n;i++){
            /*
                Realiza el producto punto de una fila con una columna
                Recibe el numero de fila y columna a multiplar, almacenados en la estructura que llega como parámetro

                El resto es la operacion aritmetica de producto punto bien concida
                producto Punto = m11*b12 + m12*b22 + m13*b32 +...+ m1n*bn2
            */
            datos->matrizResultado[fila][j] += datos->matriz1[fila][i] * datos->matriz2[i][j];
        }
    }
    return NULL;
}

//Realiza la multiplicacion de matrices, haciendo uso de la funcion producto_punto()
void multiplicar_matrices(estructura_matrices * matrices, pthread_t * hilos, int ** matriz1, int ** matriz2, int ** matrizResultado, int n){
    int iterHilo = 0;
    for(int i=0;i<n;i++){
            matrices = (estructura_matrices *) malloc(sizeof(estructura_matrices));
            matrices->fila = i;
            //matrices->columna = j;
            matrices->matriz1=matriz1;
            matrices->matriz2=matriz2;
            matrices->matrizResultado=matrizResultado;
            matrices->n=n;
            pthread_create(&(hilos[i]),NULL,producto_punto,(void *) matrices); 
    } 
}