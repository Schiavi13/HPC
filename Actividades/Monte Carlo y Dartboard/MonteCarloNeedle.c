#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>


//Funciones prototipo
int monte_carlo(float,int);

#ifndef MPI
#define M_PI 3.14159265358979323846
#endif

int main(int argc, char *argv[]){
    float l = (float)atof(argv[1]);
    int iteraciones = (int)atoi(argv[2]); 
    float p, pi;
    int n_cruzados;
    //Define la semilla usando el reloj del sistema
    srand(time(NULL));

    //Calcula la probabilidad de que las agujas se crucen
    clock_t inicio = clock();
    n_cruzados = monte_carlo(l,iteraciones);
    p = n_cruzados/(float) iteraciones;
    //Infiere Pi desde la probabilidad, sabiendo P = 2*longitud/Pi*Distancia
    pi = 2.0/(p*l);
    clock_t fin = clock();
    float segundos = (float)(fin - inicio) / CLOCKS_PER_SEC;
    printf("Probabilidad: %f\n",p);
    printf("Pi: %f\n", pi);
    printf("La ejecucion ha tomado %.4f segundos\n", segundos);
    return 0;
}

int monte_carlo(float l, int iteraciones){
    float x, theta, n;
    int n_cruzados = 0;
    for(int i=0; i<iteraciones; i++){
        //Genera el estado (X, Theta)
        x = (float)rand()/(float)(RAND_MAX/l);
        theta = (float)rand()/(float)(RAND_MAX/M_PI);

        //Calcula si la aguja cruza
        n = sin(theta)/2.0;
        if(x+n >= l || x-n<= 0){
            n_cruzados++;
        }
    }
    return n_cruzados;
}