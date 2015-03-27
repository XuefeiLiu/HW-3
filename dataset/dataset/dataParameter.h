#ifndef DATAPARAMETER_H
#define DATAPARAMETER_H


#include <string>
#include <fstream>
#include <iostream>

class DataParams
{
public:
	std::string data_original;
	std::string data;
	long size;
	double sigma;

	DataParams();
};
DataParams::DataParams() {
	/* DataParams constructor */
	data_original = "data_original.csv";
	data = "data.csv";
	size = 450000;
	sigma = 1.96;
}
#endif 