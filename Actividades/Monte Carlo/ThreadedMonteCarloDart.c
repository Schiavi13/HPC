#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <error.h>
#include <pthread.h>

#define MAX_THREADS 8

typedef struct{
    long long iteraciones;
    long long total_iteraciones;
    int thread;
    double *sumas;
}estructura_datos;

//Funciones prototipo
long long monte_carlo(estructura_datos*,pthread_t*,long long );
void *darts(void*estructura_datos);

int main(int argc, char *argv[]){
    srand(time(NULL));
    long long iteraciones = atoll(argv[1]);
    double pi;
    long long p_circulo;
    estructura_datos * datos;
    pthread_t *hilos = (pthread_t*) malloc(MAX_THREADS*sizeof(pthread_t));
    
    clock_t inicio = clock();
    p_circulo = monte_carlo(datos,hilos,iteraciones);
    //Calcula el valor de Pi
    pi = 4.0*p_circulo/(double) iteraciones;
    clock_t fin = clock();
    float segundos = (float)(fin - inicio) / CLOCKS_PER_SEC;
    printf("Pi: %f\n",pi);
    printf("La ejecucion ha tomado %.4f segundos\n", segundos);
    return 0;
}

long long monte_carlo(estructura_datos * datos,pthread_t * hilos, long long iteraciones){
    double sumas[8] = {0};
    double suma = 0;
    for(int i=0;i<MAX_THREADS;i++){
        datos = (estructura_datos *) malloc(sizeof(estructura_datos));
        datos->iteraciones=iteraciones/MAX_THREADS;
        datos->total_iteraciones = iteraciones;
        datos->sumas = sumas;
        datos->thread = i;
        pthread_create(&(hilos[i]),NULL,darts,(void *) datos);
    }
    for(int i=0;i<MAX_THREADS;i++){
        pthread_join(hilos[i],NULL);
    }

    for(int i=0;i<MAX_THREADS;i++){
        suma = suma + sumas[i];
    }
    return suma;
}

void * darts(void * estructura){
    estructura_datos *datos = (estructura_datos *) estructura;
    long long n_cruzados = 0;
    double x, y, d;
    long long iteraciones = datos->iteraciones;
    datos -> sumas[pthread_self()-1] = 0;
    for(long long i=0; i<iteraciones; i++){
        //Genera una coordenada (x,y)
        x = (double)rand()/(double)(RAND_MAX/2);
        x = x - 1;
        y = (double)rand()/(double)(RAND_MAX/2);
        y = y - 1;
        //Calcula si el dardo cae en el circulo
        d = (x*x) + (y*y);
        if(d<=1){
            datos->sumas[datos->thread] = datos->sumas[datos->thread] + 1;
        }
        
    }
    if(datos->thread==0){
        double resto = datos->total_iteraciones%MAX_THREADS;

        for(int i=0;i<resto;i++){
            x = (double)rand()/(double)(RAND_MAX/2);
            x = x - 1;
            y = (double)rand()/(double)(RAND_MAX/2);
            y = y - 1;
            //Calcula si el dardo cae en el circulo
            d = (x*x) + (y*y);
            if(d<=1){
                datos->sumas[datos->thread] = datos->sumas[datos->thread] + 1;
            }
        }
    }
}