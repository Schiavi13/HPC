#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <sys/types.h>
#include <unistd.h>
#include <time.h>
#include <omp.h>

#ifndef MPI
#define M_PI 3.14159265358979323846
#endif
#define MAX_THREADS 8

long long suma = 0;

void monte_carlo(double, long long);

int main(int argc, char *argv[]){
    srand(time(NULL));
    double l = atof(argv[1]);
    long long iteraciones = atoll(argv[2]); 
    double p, pi;

    clock_t inicio = clock();
    monte_carlo(l,iteraciones);
    p = suma/(double) iteraciones;
    pi = 2.0/(p*l);
    clock_t fin = clock();
    float segundos = (float)(fin - inicio) / CLOCKS_PER_SEC;
    printf("Probabilidad: %f\n",p);
    printf("Pi: %f\n", pi);
    printf("La ejecucion ha tomado %.4f segundos\n", segundos);

    return 0;
}

void monte_carlo(double l, long long iteraciones){
    long long i;
    double x, theta, n;
    long long rep = 0;
    #pragma omp parallel for num_threads(MAX_THREADS) private(x, theta, n) shared(suma) schedule(static)
    for(i=0; i<iteraciones; i++){
        //Genera el estado (X, Theta)
        rep ++;
        x = (double)rand()/(double)(RAND_MAX/l);
        theta = (double)rand()/(double)(RAND_MAX/M_PI);

        //Calcula si la aguja cruza
        n = sin(theta)/2.0;
        if(x+n >= l || x-n<= 0){
            suma = suma+1;    
        }
    }
    #pragma omp barrier
}

