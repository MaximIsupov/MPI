#include "mpi.h"
#include <stdio.h>
#include <iostream>
using namespace std;

/*

int main(int argc, char* argv[])
{
	int myrank, size, message;
	int TAG = 0;
	const int SIZE = 4;
	int mass[SIZE];
	mass[0] = 3;
	mass[1] = 5;
	mass[2] = 2;
	mass[3] = 1;
	MPI_Status status;
	MPI_Init(&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &myrank);
	MPI_Comm_size(MPI_COMM_WORLD, &size);
	message = myrank;
	int buf = 0;
	MPI_Request request;
	MPI_Request reqs[4];
	MPI_Status stats[2];
/*	if (myrank == 0)
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
	

	if (myrank != 0 && myrank < SIZE) {
		if (myrank <= SIZE / 2) {
			int numtosend = mass[myrank - 1];
			MPI_Isend(&numtosend, 1, MPI_INT, SIZE / 2 + 1, myrank, MPI_COMM_WORLD, &reqs[myrank-1]);
			cout << "Process " << myrank << " send number " << numtosend << endl;
		}
		if (myrank == SIZE / 2 + 1) {
			int buf[SIZE / 2];
			int num1, num2;
			MPI_Irecv(&num1, 1, MPI_INT, 1, 1, MPI_COMM_WORLD, &reqs[2]);
			MPI_Irecv(&num2, 1, MPI_INT, 2, 2, MPI_COMM_WORLD, &reqs[3]);
			cout << "Process " << myrank << " received numbers " << num1 << " and " << num2 << endl;
			
		}
	}
				MPI_Waitall(4, reqs, stats);
	MPI_Finalize();
	return 0;
}

*/

int main(int argc, char** argv) {
	int rank, size, prev, next; int buf[2];
	MPI_Request reqs[4],reqs2[8],reqs3[4]; MPI_Request reqs1[4]; MPI_Status stats[4]; MPI_Status stats2[8];
	MPI_Init(&argc, &argv);
	MPI_Comm_size(MPI_COMM_WORLD, &size);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	if (rank == 1) {
		int numtosend = 5;
		MPI_Isend(&numtosend, 1, MPI_INT, 3, 6, MPI_COMM_WORLD, &reqs[2]);
		cout << "Process " << rank << " send number " << numtosend << " to process " << 3 << endl;
	}
	if (rank == 2) {
		int numtosend = 3;
		MPI_Isend(&numtosend, 1, MPI_INT, 3, 5, MPI_COMM_WORLD, &reqs[3]);
		cout << "Process " << rank << " send number " << numtosend << " to process " << 3 << endl;
	}
	if (rank == 3) {
		int num1, num2, max, min;
		MPI_Irecv(&num1, 1, MPI_INT, 2, 5, MPI_COMM_WORLD, &reqs[0]);
		MPI_Irecv(&num2, 1, MPI_INT, 1, 6, MPI_COMM_WORLD, &reqs[1]);
		MPI_Waitall(4, reqs, stats);
		if (num1 > num2) {
			max = num1;
			min = num2;
		}
		else {
			max = num2;
			min = num1;
		}
		MPI_Isend(&max, 1, MPI_INT, 0, 8, MPI_COMM_WORLD, &reqs2[4]);
		MPI_Isend(&min, 1, MPI_INT, 0, 9, MPI_COMM_WORLD, &reqs2[5]);
		cout << "Process " << rank << " received numbers " << num1 << " and "  << num2 << " and sent min " << min << " and max " << max << endl;
	}
	if (rank == 4) {
		int numtosend = 2;
		MPI_Isend(&numtosend, 1, MPI_INT, 6, 4, MPI_COMM_WORLD, &reqs1[2]);
		cout << "Process " << rank << " send number " << numtosend << " to process " << 6 << endl;
	}
	if (rank == 5) {
		int numtosend = 4;
		MPI_Isend(&numtosend, 1, MPI_INT, 6, 3, MPI_COMM_WORLD, &reqs1[3]);
		cout << "Process " << rank << " send number " << numtosend << " to process " << 6 << endl;
	}
	if (rank == 6) {
		int num1, num2, max, min;
		MPI_Irecv(&num1, 1, MPI_INT, 5, 3, MPI_COMM_WORLD, &reqs1[0]);
		MPI_Irecv(&num2, 1, MPI_INT, 4, 4, MPI_COMM_WORLD, &reqs1[1]);
		MPI_Waitall(4, reqs1, stats);
		if (num1 > num2) {
			max = num1;
			min = num2;
		}
		else {
			max = num2;
			min = num1;
		}
		MPI_Isend(&max, 1, MPI_INT, 0, 1, MPI_COMM_WORLD, &reqs2[7]);
		MPI_Isend(&min, 1, MPI_INT, 0, 2, MPI_COMM_WORLD, &reqs2[6]);
		cout << "Process " << rank << " received numbers " << num1 << " and " << num2 << " and sent min " << min << " and max " << max << endl;
	}
	if (rank == 0) {
		cout << "rank 0 is ready!" << endl;
		int num1, num2, max, min;
		MPI_Irecv(&max, 1, MPI_INT, 6, 1, MPI_COMM_WORLD, &reqs2[3]);
		MPI_Irecv(&min, 1, MPI_INT, 6, 2, MPI_COMM_WORLD, &reqs2[2]);
		MPI_Irecv(&num2, 1, MPI_INT, 3, 8, MPI_COMM_WORLD, &reqs2[0]);
		MPI_Irecv(&num1, 1, MPI_INT, 3, 9, MPI_COMM_WORLD, &reqs2[1]);
		MPI_Waitall(4, reqs2, stats2);
		cout << "Process " << rank << " received message.\nResult = ";
		if (min < num1) cout << min << " " << num1;
		else cout << num1 << " " << min;
		if (max < num2) cout << " " << max << " " << num2;
		else cout << " " << num2 << " " << max;
	}
	MPI_Finalize();
}
