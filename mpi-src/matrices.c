#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>


#define m_size    2 // Matrix size
#define rand_mod 10 // Max random number


int main(int argc, char** argv) {

    int i, j, k, x, c,
    processor_rank, processor_count, nrpe,

    matrix_a[m_size][m_size],
    matrix_b[m_size][m_size],
    matrix_c[m_size][m_size];

    double start, end;

    // Initialise MPI environment
    MPI_Init(&argc, &argv);

    // Get number of processors
    MPI_Comm_size(MPI_COMM_WORLD, &processor_count);

    // Get processor rank
    MPI_Comm_rank(MPI_COMM_WORLD, &processor_rank);

    MPI_Status status;

    nrpe = m_size / processor_count;


    // Populate and print matrix A
    printf("MATRIX A \n");
    for (i = 0; i < m_size; ++i) {
        for (j = 0; j < m_size; ++j) {
            matrix_a[i][j] = rand() % rand_mod;
            printf("%3d", matrix_a[i][j]);
        }
        printf("\n");
    }
    printf("\n");

    // Populate and print matrix B
    printf("MATRIX B \n");
    for (i = 0; i < m_size; ++i) {
        for (j = 0; j < m_size; ++j) {
            matrix_b[i][j] = rand() % rand_mod;
            printf("%3d", matrix_b[i][j]);
        }
        printf("\n");
    }
    printf("\n");

    // Populate and print matrix C
    printf("MATRIX C \n");
    for (i = 0; i < m_size; ++i) {
        for (j = 0; j < m_size; ++j) {
            matrix_c[i][j] = rand() % rand_mod;
            printf("%3d", matrix_c[i][j]);
        }
        printf("\n");
    }
    printf("\n");


    printf("\n");


    for (i = 0; i < m_size; i++) {
        MPI_Bcast(matrix_b[i], m_size * m_size, MPI_INT, 0, MPI_COMM_WORLD);
    }
    printf("\n Matrix B, process %d: \n", processor_rank);
    for (i = 0; i < m_size; ++i) {
        for (j = 0; j < m_size; j++) {
            printf("%3d", matrix_b[i][j]);
        }
        printf("\n");
    }
    printf("\n");


    for (i = 0; i < m_size; ++i) {
        for (j = 0; j < m_size; j++) {
            MPI_Send(&matrix_a[j], m_size * nrpe, MPI_INT, i, 0, MPI_COMM_WORLD);
            nrpe++;
        }
    }


    MPI_Recv(matrix_a, m_size * nrpe, MPI_INT, 0, 0, MPI_COMM_WORLD, &status);


    start = MPI_Wtime();
    for (k = 0; k < m_size; k++) {
        for (i = 0; i < m_size; i++) {
            matrix_c[i][k] = 0;
            for (j = 0; j < m_size; j++) {
                matrix_c[i][k] = matrix_c[i][k] + matrix_a[i][j] * matrix_b[j][k];
            }
            end = MPI_Wtime();
        }
    }
    MPI_Send(&matrix_c[i][k], m_size * m_size, MPI_INT, 0, 0, MPI_COMM_WORLD);


    if (processor_rank == 0) {
        printf("Result \n");
        for (i = 0; i < m_size; i++) {
            printf("\n");
            for (j = 0; j < m_size; j++) {
                printf("%3d", matrix_c[i][k]);
            }
        }
        printf("\nTime: %f seconds", end - start);
    }


    // Finalise MPI environment
    MPI_Finalize();

    return 0;
}
