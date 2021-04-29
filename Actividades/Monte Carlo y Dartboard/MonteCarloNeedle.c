#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

#include <error.h>
#include <pthread.h>

//Funciones prototipo
int monte_carlo();
//Se asume una longitud de aguja de 1, y una distancia entre las l�neas de 2
#define L 2.0
#define ITERACIONES 100000
#ifndef MPI
#define M_PI 3.14159265358979323846
#endif

int main(){
    float p, pi;
    int n_cruzados;
    //Define la semilla usando el reloj del sistema
    srand(time(NULL));

    
    //Calcula la probabilidad de que las agujas se crucen
    n_cruzados = monte_carlo();
    p = n_cruzados/(float) ITERACIONES;
    //Infiere Pi desde la probabilidad, sabiendo P = 2*longitud/Pi*Distancia
    pi = 2.0/(p*L);
    printf("Probabilidad: %f\n",p);
    printf("Pi: %f\n", pi);
    return 0;
}

int monte_carlo(){
    float x, theta, n, p, pi;
    int n_cruzados = 0;
    for(int i=0; i<ITERACIONES; i++){
        //Genera el estado (X, Theta)
        x = (float)rand()/(float)(RAND_MAX/L);
        theta = (float)rand()/(float)(RAND_MAX/M_PI);

        //Calcula si la aguja cruza
        n = sin(theta)/2.0;
        if(x+n >= L || x-n<= 0){
            n_cruzados++;
        }
    }
    return n_cruzados;
}