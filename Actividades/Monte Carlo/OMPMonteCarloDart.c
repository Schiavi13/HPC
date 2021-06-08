#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <sys/types.h>
#include <unistd.h>
#include <time.h>
#include <omp.h>

#define MAX_THREADS 8

long long suma = 0;

void monte_carlo(long long );

int main(int argc, char *argv[]){
    srand(time(NULL));
    long long iteraciones = atoll(argv[1]);
    double pi;

    clock_t inicio = clock();
    monte_carlo(iteraciones);
    pi = 4.0*suma/(double) iteraciones;
    clock_t fin = clock();
    float segundos = (float)(fin - inicio) / CLOCKS_PER_SEC;
    printf("Pi: %f\n",pi);
    printf("La ejecucion ha tomado %.4f segundos\n", segundos);

    return 0;
}

void monte_carlo(long long iteraciones){
    long long i;
    double x, y, d;
    #pragma omp parallel for num_threads(MAX_THREADS) private(x, y, d) shared(suma) schedule(static)
    for(long long i=0; i<iteraciones; i++){
        //Genera una coordenada (x,y)
        x = (double)rand()/(double)(RAND_MAX/2);
        x = x - 1;
        y = (double)rand()/(double)(RAND_MAX/2);
        y = y - 1;
        //Calcula si el dardo cae en el circulo
        d = (x*x) + (y*y);
        if(d<=1){
            suma = suma+1;
        }
    }
    #pragma omp barrier
}