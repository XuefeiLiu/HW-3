#ifndef MPI_C_
#define MPI_C_
#include <math.h>
#include "mpi.h"
#include <iostream>
#include <fstream>
#include "mylog.h"
#include <string>
#include <vector>
using namespace std;


bool test(vector<double> original_result, vector<double> result)
{
	if (fabs(original_result[0] - result[0]) / original_result[1]<1.96)
	{
		if (fabs(original_result[1] - result[1]) / original_result[1]<0.103)
			return true;
		else
			return false;
	}
	else
		return false;
}

vector<double> character(string filename) {
	//MPI initialize
	MPI_Status mpi_status;
	int rank, size;
	size = MPI::COMM_WORLD.Get_size();
	rank = MPI::COMM_WORLD.Get_rank();

	//Spilit and read  the file according to size and rank
	ifstream file(filename);
	file.seekg(0, file.end);
	long file_length = file.tellg();
	long each_file_length = file_length / size;
	long position = each_file_length * rank;
	ifstream inputfile;
	inputfile.open(filename);
	inputfile.seekg(position);

	double MEAN = 0; //first order mean
	double MEAN_SQUARE = 0; //second order average of square sum
	string temp_time;
	string temp_string;
	double value;
	int index = 0;
	long position_ = each_file_length * (rank + 1) - 2;
	while (inputfile.tellg() <= position_) {
		getline(inputfile, temp_time, ',');
		inputfile >> value;
		getline(inputfile, temp_string);
		MEAN = (index * MEAN + value) / (index + 1);
		MEAN_SQUARE = (index * MEAN_SQUARE + value * value) / (index + 1);
		index++;
	}

	vector<double> arr(2);
	vector<double> temp_arr(2);
	arr[0] = MEAN;
	arr[1] = MEAN_SQUARE;

	//Calculate Mean and Var
	if (rank == 0) {
		for (int i = 1; i < size; i++) {
			MPI_Recv(&temp_arr, 2, MPI_DOUBLE, i, 0, MPI_COMM_WORLD,
				&mpi_status);
			MEAN += temp_arr[0];
			MEAN_SQUARE += temp_arr[1];
		}
		MEAN = MEAN / size;
		MEAN_SQUARE = MEAN_SQUARE / size;
	}
	else {
		MPI_Send(&arr, 2, MPI_DOUBLE, 0, 0, MPI_COMM_WORLD);
	}

	double Var = sqrt(MEAN_SQUARE - MEAN * MEAN);
	arr[0] = MEAN;
	arr[1] = Var;

	return arr; //return the mean with [0] : Mean [1] : Var

}



#endif 
