#include <iostream>
#include <random>
#include <chrono>
#include <math.h>

#define ITERACIONES 100000000

using namespace std;

int main(){
    float x, y, d, pi;
    int i, p_circulo=0;
    //Define la semilla usando el reloj del sistema
    unsigned seed = chrono::system_clock::now().time_since_epoch().count();

    //Inicializa el generador de numeros
    default_random_engine rd(seed);
    uniform_real_distribution<float> dis(-1,1);

    for(i=0; i<ITERACIONES; i++){
        //Genera una coordenada (x,y)
        x = dis(rd);
        y = dis(rd);

        //Calcula si el dardo cae en el circulo
        d = (x*x) + (y*y);
        if(d <= 1){
            p_circulo++;
        }
    }
    //Calcula el valor de Pi
    pi = 4.0*p_circulo/(float) ITERACIONES;
    cout << "Pi: " << pi << "\n";
    return 0;
}
