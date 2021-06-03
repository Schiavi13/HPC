#include <mpi.h>
#include <stdio.h>

int main(int argc, char ** argv){
    //Inicia el ambiente MPI
    MPI_Init(NULL,NULL);

    //Recibe el numero de procesos
    int world_size;
    MPI_Comm_size(MPI_COMM_WORLD, &world_size);

    //Recibe el ranking del proceso
    int world_rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);

    //Recibe el nombre del procesador
    char processor_name[MPI_MAX_PROCESSOR_NAME];
    int name_len;
    MPI_Get_processor_name(processor_name, &name_len);

    //Imprime mensaje de hola mundo
    printf("¡Hola Mundo! desde el procesador %s, rank %d de %d procesadores\n",processor_name, world_rank, world_size);

    //Finaliza el ambiente MPI
    MPI_Finalize();
    return 0;
}