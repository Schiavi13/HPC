#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <sys/mman.h>
#include <time.h>

//#define nucleos 4

//Funciones prototipo
int capturar_tamano(void);
int ** crear_matriz(int**, int);
void poblar_matriz(int**, int);
void mostrar_matriz(int**, int);
void producto_punto(int**, int**, int**, int, int);
void multiplicar_matrices(int**, int**,pid_t*, int**, int);


int main(int argc, char *argv[]){
    srand(time(NULL));
    int n = (int)atoi(argv[1]);
    int **matriz1 = NULL;
    int **matriz2 = NULL;
    int **matrizResultado = NULL;
    pid_t *forks = (pid_t*) malloc(n*sizeof(pid_t));
    matriz1 = crear_matriz(matriz1, n);
    matriz2 = crear_matriz(matriz2, n);
    matrizResultado = crear_matriz(matrizResultado, n);
    poblar_matriz(matriz1, n);
    poblar_matriz(matriz2, n);
    
    mostrar_matriz(matriz1, n);
    mostrar_matriz(matriz2, n);
    
    clock_t inicio = clock();
    multiplicar_matrices(matriz1,matriz2,forks,matrizResultado,n);
    clock_t fin = clock();
    float segundos = (float)(fin - inicio) / CLOCKS_PER_SEC;
    mostrar_matriz(matrizResultado,n);
    /*
    free(matriz1);
    free(matriz2);
    free(matrizResultado);
    */
    printf("La ejecucion ha tomado %.4f segundos\n", segundos);
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
    matriz = (int **) mmap(NULL,sizeof(int *)*n,PROT_READ | PROT_WRITE,MAP_SHARED | MAP_ANONYMOUS,1,0);
    
    for(int i=0;i<n;i++){
        matriz[i] = (int*)mmap(NULL,sizeof(int *)*n,PROT_READ | PROT_WRITE,MAP_SHARED | MAP_ANONYMOUS,1,0);
    }
    return matriz;
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
void producto_punto(int **matriz1, int ** matriz2, int ** matrizResultado, int n, int fila){
    int productoPunto = 0;
    for(int i=0;i<n;i++){
        matrizResultado[fila][i] = 0;
        for(int j=0;j<n;j++){
            matrizResultado[fila][i] += matriz1[fila][j]*matriz2[i][j]; //suponiendo que matriz2 ya es la traspuesta de la matriz2
                                                                                                    //original
        }
        //printf("%d \n",matrizResultado[fila][i]);
    }   
}

//Realiza la multiplicacion de matrices, haciendo uso de la funcion producto_punto()
void multiplicar_matrices(int ** matriz1, int ** matriz2, pid_t* forks, int ** matrizResultado, int n){
    for(int i=0;i<n;++i){
        if((forks[i]=fork()) < 0){
            perror("fork");
            abort();
        }
        else if(forks[i] == 0){
            producto_punto(matriz1, matriz2, matrizResultado, n, i);
            exit(0);
        }
    }

    int status;
    pid_t pid;
    while(n>0){
        pid = wait(&status);
        //printf("Hijo con PID %ld salio con estatus 0x%x. \n", (long)pid, status);
        --n;
    }
}