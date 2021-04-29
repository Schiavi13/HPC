#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

int monte_carlo();
#define ITERACIONES 100000



int main(){
    float x, y, d, pi;
    int i, p_circulo=0;

    //Define la semilla usando el reloj del sistema
    srand(time(NULL));
    
    p_circulo = monte_carlo();
    //Calcula el valor de Pi
    pi = 4.0*p_circulo/(float) ITERACIONES;
    printf("Pi: %f\n",pi);
}

int monte_carlo(){
    float x, y, d, pi;
    int p_circulo=0;

    for(int i=0; i<ITERACIONES; i++){
        //Genera una coordenada (x,y)
        x = (float)rand()/(float)(RAND_MAX/2);
        x = x - 1;
        y = (float)rand()/(float)(RAND_MAX/2);
        y = y - 1;

        //Calcula si el dardo cae en el circulo
        d = (x*x) + (y*y);
        if(d<=1){
            p_circulo++;
        }
    }
    return p_circulo;
}