#include <mpi.h>
#include <stdio.h>

int main(int argc, char ** argv ){
    MPI_Init(&argc, &argv);
    int rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    //Lee el valor local del proceso
    //El valor local mantendra un entero especifico para el proceso 0, y otro para el proceso 1
    int local_value;
    //local_value = atoi(argv[1]);
    local_value = (rank==0) ? 2 : 22;
    int other_value;
    if(rank==0){
        //Ingresar aqui el codigo del primer proceso:
        //1- Enviar el valor al proceso 1
        //MPI_Recv(&other_value, 1, MPI_INT, 1, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        MPI_Send(&local_value, 1, MPI_INT, 1, 0, MPI_COMM_WORLD);
        //2- Recibe el valor desde el proceso 1 (en other_value)
        MPI_Recv(&other_value, 1, MPI_INT, 1, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        //3- Imprime la suma de los dos valores en la salida estandar
        printf("%d\n",local_value+other_value);
    }
    else{
        //Ingresar aqui el codigo del segundo proceso
        //1- Recibe el valor desde el proceso 0 (en other_value)
        MPI_Recv(&other_value, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        //2- Envia el valor al proceso 0
        MPI_Send(&local_value, 1, MPI_INT, 0, 0, MPI_COMM_WORLD);
        //3- Imprime el producto de los dos valores en la salida estandar
        printf("%d\n",local_value*other_value);
    }
    MPI_Finalize();
    return 0;
}