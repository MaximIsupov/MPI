#include "mpi.h"
#include <stdio.h>
int main(int argc, char* argv[])
{
	int myrank, size, message;
	int TAG = 0;
	MPI_Status status;
	MPI_Init(&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &myrank);
	MPI_Comm_size(MPI_COMM_WORLD, &size);
	message = myrank;
	/*	if ((myrank % 2) == 0)
				{
					if ((myrank + 1) != size)
						MPI_Send(&message, 1, MPI_INT, myrank+1, TAG, MPI_COMM_WORLD);
				}
				else
				{
					if (myrank != 0)
						MPI_Recv(&message, 1, MPI_INT, myrank-1, TAG, MPI_COMM_WORLD, &status);
					printf("received :%i\n", message);
				}
				*/
	int buf = 0;
	if (myrank == 0)
	{
		buf += myrank;
		MPI_Send(&buf, 1, MPI_INT, myrank + 1, TAG, MPI_COMM_WORLD);
		MPI_Recv(&buf, 1, MPI_INT, size-1, TAG, MPI_COMM_WORLD, &status);
		printf("received :%i\n", buf);
	}
	else {
		if ((myrank + 1) != size)
		{
			MPI_Recv(&buf, 1, MPI_INT, myrank - 1, TAG, MPI_COMM_WORLD, &status);
			buf += myrank;
			MPI_Send(&buf, 1, MPI_INT, myrank + 1, TAG, MPI_COMM_WORLD);
		}
		else
		{
			MPI_Recv(&buf, 1, MPI_INT, myrank - 1, TAG, MPI_COMM_WORLD, &status);
			buf += myrank;
			MPI_Send(&buf, 1, MPI_INT, 0, TAG, MPI_COMM_WORLD);
		}
	}
	MPI_Finalize();
	return 0;
}
