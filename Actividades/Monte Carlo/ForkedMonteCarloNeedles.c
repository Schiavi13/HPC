#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <sys/mman.h>
#include <time.h>
#include <math.h>

long long monte_carlo(pid_t*,double*, double, long long );
void needles(double*, double, long long, long long, int);

#define MAX_PROCESS 8
#ifndef MPI
#define M_PI 3.14159265358979323846
#endif

int main(int argc, char *argv[]){
    srand(time(NULL));
    double l = atof(argv[1]);
    long long iteraciones = atoll(argv[2]); 
    double p, pi;
    long long n_cruzados;
    double *sumas = NULL;
    sumas = (double*)mmap(NULL,sizeof(double*)*MAX_PROCESS,PROT_READ | PROT_WRITE,MAP_SHARED | MAP_ANONYMOUS,1,0);
    
    pid_t *forks = (pid_t*) malloc(MAX_PROCESS*sizeof(pid_t));
    //Define la semilla usando el reloj del sistema
    

    //Calcula la probabilidad de que las agujas se crucen
    clock_t inicio = clock();
    n_cruzados = monte_carlo(forks,sumas,l,iteraciones);
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

long long monte_carlo(pid_t * forks,double * sumas, double l, long long iteraciones){
    long long suma=0;
    long long iter_per_process = iteraciones/MAX_PROCESS;
    for(int i=0;i<MAX_PROCESS;i++){
        if((forks[i]=fork()) < 0){
            perror("fork");
            abort();
        }
        else if(forks[i] == 0){
            needles(sumas, l, iteraciones,iter_per_process,i);
            exit(0);
        }
    }
    int status;
    int n = MAX_PROCESS;
    pid_t pid;
    while(n>0){
        pid = wait(&status);
        //printf("Hijo con PID %ld salio con estatus 0x%x. \n", (long)pid, status);
        --n;
    }
    for(int i=0;i<MAX_PROCESS;i++){
        suma = suma + sumas[i];
    }
    return suma;
}

void needles(double*sumas, double l, long long iteraciones,long long iter_per_process,int proceso){
    double x, theta, n;
    long long n_cruzados = 0;
    sumas[proceso] = 0;
    for(long long i=0; i<iter_per_process; i++){
        //Genera el estado (X, Theta)
        x = (double)rand()/(double)(RAND_MAX/l);
        theta = (double)rand()/(double)(RAND_MAX/M_PI);

        //Calcula si la aguja cruza
        n = sin(theta)/2.0;
        if(x+n >= l || x-n<= 0){
            sumas[proceso] = sumas[proceso] + 1;
        }
    }
    if(proceso == 0){
        double resto =iteraciones%MAX_PROCESS;
        for(int i=0;i<resto;i++){
            x = (double)rand()/(double)(RAND_MAX/l);
            theta = (double)rand()/(double)(RAND_MAX/M_PI);

            //Calcula si la aguja cruza
            n = sin(theta)/2.0;
            if(x+n >= l || x-n<= 0){
                sumas[proceso] = sumas[proceso] + 1;
            }
        }
    }
}