/* Implement a ring by using send and receives. Write a program that takes data
 * from process zero and sends it to all of the other processes by sending it in
 * a ring. That is, process i should receive the data and send it to process
 * i+1, until the last process is reached.
 */

#include <mpi.h> /* For MPI functions, etc */
#include <stdio.h>
#include <string.h> /* For strlen            */

const int MAX_STRING = 100;

int main(void) {
    char data[MAX_STRING];
    int comm_sz; /* Number of processes */
    int my_rank; /* My process rank     */

    MPI_Init(NULL, NULL);
    MPI_Comm_size(MPI_COMM_WORLD, &comm_sz);
    MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);

    if (my_rank == 0) {
        fgets(data, MAX_STRING, stdin);
    } else {
        MPI_Recv(data, MAX_STRING, MPI_CHAR, my_rank - 1, 0, MPI_COMM_WORLD,
                 MPI_STATUS_IGNORE);
    }

    printf("I'm rank %d, received: %s", my_rank, data);

    if (my_rank + 1 < comm_sz) {
        MPI_Send(data, strlen(data) + 1, MPI_CHAR, my_rank + 1, 0,
                 MPI_COMM_WORLD);
    }

    MPI_Finalize();
    return 0;
} /* main */
