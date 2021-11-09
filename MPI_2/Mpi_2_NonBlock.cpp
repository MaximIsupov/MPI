#include "mpi.h"
#include <stdio.h>
#include <iostream>
using namespace std;
int main(int argc, char* argv[])
{
	int myrank, size, message;
	int TAG = 0;
	MPI_Status status;
	MPI_Init(&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &myrank);
	MPI_Comm_size(MPI_COMM_WORLD, &size);
	message = myrank;
	MPI_Request request;
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
		MPI_Isend(&buf, 1, MPI_INT, myrank + 1, TAG, MPI_COMM_WORLD, &request);
		MPI_Irecv(&buf, 1, MPI_INT, size-1, TAG, MPI_COMM_WORLD, &request);
		if (MPI_Wait(&request, &status) == MPI_SUCCESS) {
			cout << "Process " << myrank << " sucessfuly done calculation with result: "  << buf << endl;
		}
	}
	else {
		if ((myrank + 1) != size)
		{
			MPI_Irecv(&buf, 1, MPI_INT, myrank - 1, TAG, MPI_COMM_WORLD, &request);
			if (MPI_Wait(&request, &status) == MPI_SUCCESS) {
				cout << "succesfuly received message process " << myrank << endl;
			}
			buf += myrank;
			MPI_Isend(&buf, 1, MPI_INT, myrank + 1, TAG, MPI_COMM_WORLD, &request);
		}
		else
		{
			MPI_Irecv(&buf, 1, MPI_INT, myrank - 1, TAG, MPI_COMM_WORLD, &request);
			if (MPI_Wait(&request, &status) == MPI_SUCCESS) {
				cout << "succesfuly received message process " << myrank << endl;
			}
			buf += myrank;
			MPI_Isend(&buf, 1, MPI_INT, 0, TAG, MPI_COMM_WORLD, &request);
		}
	}
	MPI_Finalize();
	return 0;
}
