/* Design a broadcast solution by using send and receive calls. What we expect:
 * a process “p” wants to share the content of a variable “a” with all the other
 * processes.
 */

#include <mpi.h>
#include <stdio.h>
#include <string.h>

const int MAX_STRING = 100;

void my_bcast(void *buffer, int count, MPI_Datatype datatype, int root,
              MPI_Comm comm) {
    int comm_sz, my_rank;
    MPI_Comm_size(comm, &comm_sz);
    MPI_Comm_rank(comm, &my_rank);

    if (my_rank == root) {
        for (int i = 0; i < comm_sz; i++) {
            if (i == my_rank)
                continue;
            MPI_Send(buffer, count, datatype, i, 0, comm);
        }
    } else {
        MPI_Recv(buffer, count, datatype, root, 0, comm, MPI_STATUS_IGNORE);
    }
}

int main(void) {
    char data[MAX_STRING];
    int comm_sz;
    int my_rank;

    MPI_Init(NULL, NULL);
    MPI_Comm_size(MPI_COMM_WORLD, &comm_sz);
    MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);

    if (my_rank == 0) {
        fgets(data, MAX_STRING, stdin);
    }

    my_bcast(data, MAX_STRING, MPI_CHAR, 0, MPI_COMM_WORLD);

    printf("I'm rank %d, received: %s", my_rank, data);

    MPI_Finalize();
    return 0;
}
