#include <iostream>
#include <random>
#include <chrono>
#include <math.h>

//Se asume una longitud de aguja de 1, y una distancia entre las líneas de 2
#define L 2.0
#define ITERACIONES 100000

using namespace std;

int main(){
    float x, theta, n, p, pi;
    int i, n_cruzados=0;
    //Define la semilla usando el reloj del sistema
    unsigned seed = chrono::system_clock::now().time_since_epoch().count();

    //Inicializa el generador de numeros
    default_random_engine rd(seed);
    uniform_real_distribution<float> xDis(0,L);
    uniform_real_distribution<float> thDis(0,M_PI);

    for(i=0; i<ITERACIONES; i++){
        //Genera el estado (X, Theta)
        x = xDis(rd);
        theta = thDis(rd);

        //Calcula si la aguja cruza
        n = sin(theta)/2.0;
        if(x+n >= L || x-n<=0){
            n_cruzados++;
        }
    }
    //Calcula la probabilidad de que las agujas se crucen
    p = n_cruzados/(float) ITERACIONES;
    //Infiere Pi desde la probabilidad, sabiendo P = 2*longitud/Pi*Distancia
    pi = 2.0/(p*L);
    cout << fixed << "Probabilidad: " << p << "\n" << "Pi: " << pi << "\n";
    return 0;
}
