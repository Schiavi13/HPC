#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <error.h>
#include <pthread.h>

//Funciones prototipo
int monte_carlo(long long);

typedef struct{
    long long iteraciones;
    long long p_circulo;
    double x;
    double y;
    double d;
    double *sumas;
}estructura_datos;


int main(int argc, char *argv[]){
    long long iteraciones = atoll(argv[1]);
    double pi;
    long long p_circulo;
    
    //Define la semilla usando el reloj del sistema
    srand(time(NULL));
    clock_t inicio = clock();
    p_circulo = monte_carlo(iteraciones);
    //Calcula el valor de Pi
    pi = 4.0*p_circulo/(double) iteraciones;
    clock_t fin = clock();
    float segundos = (float)(fin - inicio) / CLOCKS_PER_SEC;
    printf("Pi: %f\n",pi);
    printf("La ejecucion ha tomado %.4f segundos\n", segundos);
    return 0;
}

int monte_carlo(long long iteraciones){
    double x, y, d;
    long long p_circulo=0;

    for(long long i=0; i<iteraciones; i++){
        //Genera una coordenada (x,y)
        x = (double)rand()/(double)(RAND_MAX/2);
        x = x - 1;
        y = (double)rand()/(double)(RAND_MAX/2);
        y = y - 1;
        //Calcula si el dardo cae en el circulo
        d = (x*x) + (y*y);
        if(d<=1){
            p_circulo++;
        }
        
    }
    return p_circulo;
}