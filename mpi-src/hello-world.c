#include <stdio.h>
#include <mpi.h>

int main(int argc, char** argv) {

    // Create variables
    int processor_rank, processor_count, processor_name_len;
    char processor_name[MPI_MAX_PROCESSOR_NAME];

    // Initialise MPI environment
    MPI_Init(&argc, &argv);

    // Get number of processors
    MPI_Comm_size(MPI_COMM_WORLD, &processor_count);

    // Get processor rank
    MPI_Comm_rank(MPI_COMM_WORLD, &processor_rank);

    // Get processor name
    MPI_Get_processor_name(processor_name, &processor_name_len);

    // Print a message
    printf("Hello from %s - process %d of %d.\n",
        processor_name, processor_rank + 1, processor_count);

    // Finalise MPI environment
    MPI_Finalize();

    return 0;
}
