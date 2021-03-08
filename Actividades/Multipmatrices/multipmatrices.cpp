#include <stdio.h>
#include <stdlib.h>
#include <time.h>

//Funciones prototipo
int capturar_tamano(void);
int ** crear_matriz(int**, int);
void poblar_matriz(int**, int);
void mostrar_matriz(int**, int);
int producto_punto(int*,int**,int,int);
int ** multiplicar_matrices(int**, int**, int**, int);


int main(){
    srand(time(NULL));
    int n = capturar_tamano();
    int **matriz1 = NULL;
    int **matriz2 = NULL;
    int **matrizResultado = NULL;
    matriz1 = crear_matriz(matriz1, n);
    matriz2 = crear_matriz(matriz2, n);
    matrizResultado = crear_matriz(matrizResultado, n);
    poblar_matriz(matriz1, n);
    poblar_matriz(matriz2, n);
    //mostrar_matriz(matriz1, n);
    //mostrar_matriz(matriz2, n);
    clock_t inicio = clock();
    matrizResultado = multiplicar_matrices(matriz1,matriz2,matrizResultado,n);
    clock_t fin = clock();
    float segundos = (float)(fin - inicio) / CLOCKS_PER_SEC;
    printf("La ejecucion ha tomado %.4f segundos\n", segundos);
    //mostrar_matriz(matrizResultado,n);
    free(matriz1);
    free(matriz2);
    free(matrizResultado);
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
int producto_punto(int * fila, int ** matriz2, int columna, int n){
    int productoPunto = 0;
    for(int i=0;i<n;i++){
        /*
            Realiza el producto punto de una fila con una columna
            Recibe el apuntador a una fila, y la segunda matriz para acceder a la columna
            Si se recibe la fila 1 y la columna 2:
            *fila = p1, que a su vez apunta a {m11,m12,m13,...,m1n}

            **matriz2, junto la columna 2, para acceder a la columna:
            matriz2[i][2] = {b12,b22,b32,...,bn2}

            El resto es la operacion aritmetica de producto punto bien concida
            producto Punto = m11*b12 + m12*b22 + m13*b32 +...+ m1n*bn2
        */
        productoPunto = productoPunto + fila[i]*matriz2[i][columna];
    }
    return productoPunto;
}

//Realiza la multiplicacion de matrices, haciendo uso de la funcion producto_punto()
int ** multiplicar_matrices(int ** matriz1, int ** matriz2, int ** matrizResultado, int n){
    
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            /*Asigna a matrizResultado[i][j] 
            el producto punto entre la fila i de la matriz1 y la columna j de la matriz2
            */
            matrizResultado[i][j] = producto_punto(matriz1[i],matriz2,j,n);
        }
    }
    return(matrizResultado);
}