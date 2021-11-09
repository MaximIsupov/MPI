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
	int data[1];
	int buf[] = { 1,3,5 };
	int count, TAG = 0;
	int rank, size;
	MPI_Status st;

	MPI_Request req;
	data[0] = 2016;
	MPI_Init(&argc, &argv);;
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm_size(MPI_COMM_WORLD, &size);
	if (rank == 0)
	{
		MPI_Send(&data, 1, MPI_INT, 2, TAG, MPI_COMM_WORLD);
		cout << "Hello";
	}
	else if (rank == 1) {
		MPI_Send(&buf, 3, MPI_INT, 2, TAG, MPI_COMM_WORLD);
	}
	else if (rank == 2) {
		int count;
		MPI_Status status;
		MPI_Probe(0, TAG, MPI_COMM_WORLD, &status);
		MPI_Get_count(&status, MPI_INT, &count);
		int* back_buf = new int[count];
		MPI_Get_count(&status, MPI_INT, &count);
		MPI_Recv(back_buf, count, MPI_INT, 0, TAG, MPI_COMM_WORLD, &status);
		cout << "Rank = 0, count = " << count << "\n" << back_buf[0] << endl;
		int count2;
		MPI_Status status2;
		MPI_Probe(1, TAG, MPI_COMM_WORLD, &status2);
		MPI_Get_count(&status2, MPI_INT, &count2);
		int* back_buf2 = new int[count2];
		MPI_Recv(back_buf2, count2, MPI_INT, 1, TAG, MPI_COMM_WORLD, &status2);
		cout << "Rank = 1, count = " << count2 << endl;
		for (int i = 0; i < count2; i++) {
			cout << back_buf2[i] << endl;
		}
	}
	MPI_Finalize();
	return 0;
}
