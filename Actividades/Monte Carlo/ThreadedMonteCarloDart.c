#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <error.h>
#include <pthread.h>

#define MAX_THREADS 8

pthread_mutex_t mutex;
long long suma = 0;
typedef struct{
    long long iteraciones;
    long long total_iteraciones;
    int thread;
}estructura_datos;

//Funciones prototipo
void monte_carlo(estructura_datos*,pthread_t*,long long );
void *darts(void*estructura_datos);

int main(int argc, char *argv[]){
    srand(time(NULL));
    long long iteraciones = atoll(argv[1]);
    double pi;
    estructura_datos * datos;
    pthread_t *hilos = (pthread_t*) malloc(MAX_THREADS*sizeof(pthread_t));
    
    clock_t inicio = clock();
    monte_carlo(datos,hilos,iteraciones);
    //Calcula el valor de Pi
    pi = 4.0*suma/(double) iteraciones;
    clock_t fin = clock();
    float segundos = (float)(fin - inicio) / CLOCKS_PER_SEC;
    printf("Pi: %f\n",pi);
    printf("La ejecucion ha tomado %.4f segundos\n", segundos);
    return 0;
}

void monte_carlo(estructura_datos * datos,pthread_t * hilos, long long iteraciones){

    pthread_mutex_init(&mutex,NULL);
    for(int i=0;i<MAX_THREADS;i++){
        datos = (estructura_datos *) malloc(sizeof(estructura_datos));
        datos->iteraciones=iteraciones/MAX_THREADS;
        datos->total_iteraciones = iteraciones;
        datos->thread = i;
        pthread_create(&(hilos[i]),NULL,darts,(void *) datos);
    }
    for(int i=0;i<MAX_THREADS;i++){
        pthread_join(hilos[i],NULL);
    }
    pthread_mutex_destroy(&mutex);

}

void * darts(void * estructura){
    estructura_datos *datos = (estructura_datos *) estructura;
    double x, y, d;
    long long iteraciones = datos->iteraciones;
    for(long long i=0; i<iteraciones; i++){
        //Genera una coordenada (x,y)
        x = (double)rand()/(double)(RAND_MAX/2);
        x = x - 1;
        y = (double)rand()/(double)(RAND_MAX/2);
        y = y - 1;
        //Calcula si el dardo cae en el circulo
        d = (x*x) + (y*y);
        if(d<=1){
            pthread_mutex_lock(&mutex);
            suma = suma+1;
            pthread_mutex_unlock(&mutex);
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
                pthread_mutex_lock(&mutex);
                suma = suma+1;
                pthread_mutex_unlock(&mutex);
            }
        }
    }
    return NULL;
}