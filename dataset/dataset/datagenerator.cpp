#include "dataParameter.h"
#include "datagenerator.h"
#include <random>
#include <iostream>
#include<string>
using namespace std;


int main()
{
	
	generate_data();
	return 0;
}

void generate_data() {

	DataParams params;

	// track size

	ifstream ifs(params.data_original, ifstream::binary);
	ifs.seekg(0, ifs.end);
	int i_inputSize = ifs.tellg();
	ifs.close();

	int i_numPoints = params.size / i_inputSize;
	double d_delta = sqrt(1.0 / i_numPoints) * params.sigma;

	// open input and output file

	string str_prevLine;
	string str_currLine;

	ifstream in(params.data_original);
	getline(in, str_prevLine);
	ofstream out;
	out.open(params.data, ios::app);

	// random number generator
	
	std::random_device rd;
	std::mt19937 gen(rd());
	std::normal_distribution<float> standardNormal(0, 1);

	// read and write data

	while (getline(in, str_currLine))
	{
		if (str_currLine == "ND")
			str_currLine = str_prevLine;//Make data not found the same as previous data.
		float f_prev = stof(str_prevLine);
		float f_curr = stof(str_currLine);
		float driftPerPoint = (f_curr - f_prev) / i_numPoints;

		out << to_string(f_prev) << endl;
		for (int i = 0; i < i_numPoints; i++) {
			f_prev += driftPerPoint + d_delta * standardNormal(gen);
			out << to_string(f_prev) << endl;
		}
		out << to_string(f_curr) << endl;
		str_prevLine = str_currLine;

	}

	// close files

	in.close();
	out.close();
}