#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <error.h>
#include <pthread.h>




#ifndef MPI
#define M_PI 3.14159265358979323846
#endif
#define MAX_THREADS 8

typedef struct{
    long long iteraciones;
    long long total_iteraciones;
    double l;
    int thread;
    double *sumas;
}estructura_datos;

//Funciones prototipo
long long monte_carlo(estructura_datos*,pthread_t*,double,long long );
void *needles(void*estructura_datos);

int main(int argc, char *argv[]){
    srand(time(NULL));
    double l = atof(argv[1]);
    long long iteraciones = atoll(argv[2]); 
    double p, pi;
    long long n_cruzados;
    estructura_datos * datos;
    pthread_t *hilos = (pthread_t*) malloc(MAX_THREADS*sizeof(pthread_t));
    

    //Calcula la probabilidad de que las agujas se crucen
    clock_t inicio = clock();
    n_cruzados = monte_carlo(datos,hilos,l,iteraciones);
    //printf("cruce: %lld",n_cruzados);
    p = n_cruzados/(double) iteraciones;
    //Infiere Pi desde la probabilidad, sabiendo P = 2*longitud/Pi*Distancia
    pi = 2.0/(p*l);
    clock_t fin = clock();
    float segundos = (float)(fin - inicio) / CLOCKS_PER_SEC;
    printf("Probabilidad: %f\n",p);
    printf("Pi: %f\n", pi);
    printf("La ejecucion ha tomado %.4f segundos\n", segundos);
    return 0;
}

long long monte_carlo(estructura_datos * datos,pthread_t * hilos, double l, long long iteraciones){
    double sumas[8] = {0};
    double suma = 0;
    for(int i=0;i<MAX_THREADS;i++){
        datos = (estructura_datos *) malloc(sizeof(estructura_datos));
        datos->iteraciones=iteraciones/MAX_THREADS;
        datos->total_iteraciones = iteraciones;
        datos->l=l;
        datos->sumas = sumas;
        datos->thread = i;
        pthread_create(&(hilos[i]),NULL,needles,(void *) datos);
    }
    for(int i=0;i<MAX_THREADS;i++){
        pthread_join(hilos[i],NULL);
    }

    for(int i=0;i<MAX_THREADS;i++){
        suma = suma + sumas[i];
    }
    return suma;
}

void * needles(void * estructura){
    estructura_datos *datos = (estructura_datos *) estructura;
    long long n_cruzados = 0;
    double x, theta, n;
    long long iteraciones = datos->iteraciones;
    double l = datos->l;
    datos -> sumas[pthread_self()-1] = 0;
    for(long long i=0; i<iteraciones; i++){
        //Genera el estado (X, Theta)
        x = (double)rand()/(double)(RAND_MAX/l);
        theta = (double)rand()/(double)(RAND_MAX/M_PI);

        //Calcula si la aguja cruza
        n = sin(theta)/2.0;
        if(x+n >= l || x-n<= 0){
            datos->sumas[datos->thread] = datos->sumas[datos->thread] + 1;
        }
    }
    if(datos->thread==0){
        double resto = datos->total_iteraciones%MAX_THREADS;

        for(int i=0;i<resto;i++){
            x = (double)rand()/(double)(RAND_MAX/l);
            theta = (double)rand()/(double)(RAND_MAX/M_PI);

            //Calcula si la aguja cruza
            n = sin(theta)/2.0;
            if(x+n >= l || x-n<= 0){
                datos->sumas[datos->thread] = datos->sumas[datos->thread] + 1;
            }
        }
    }

}