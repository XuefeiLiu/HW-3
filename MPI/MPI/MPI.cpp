
#include <iostream>
#include <string>
#include "mylog.h"
#include "data_test.h"
#include "mpi.h"
#include <vector>
#include <sstream>
using namespace std;

int main(int argc, char *argv[]) {
	//log start
	log4cpp::Category& root = InitLogging::getRoot();
	std::ostringstream os_log;

	os_log << "MPI test start!";
	root.info(os_log.str());
	os_log.str("");
	os_log.clear();

	MPI::Init(argc, argv);
	os_log << "MPI initiate.......";
	root.info(os_log.str());
	os_log.str("");
	os_log.clear();

	string original_file = "data_original.csv";
	string test_file = "data.csv";
	vector<double> original_result;
	vector<double> result;

	os_log << "Read Original Data File:";
	root.info(os_log.str());
	os_log.str("");
	os_log.clear();
	clock_t time1 = clock();

	//calculating
	original_result = character(original_file);

	clock_t time2 = clock();
	os_log << "Calculating from original data  using time : "
		<< Utils::diffclock(time2, time1) << " seconds \n";
	os_log << "Mean:" << original_result[0] << ", " << "Variance:"
		<< original_result[1];
	root.info(os_log.str());
	os_log.str("");
	os_log.clear();

	os_log << "Read Generate Data File:";
	root.info(os_log.str());
	os_log.str("");
	os_log.clear();
	time1 = clock();

	//calculating
	result = character(test_file);

	time2 = clock();
	os_log << "Calculating from original data  using time : "
		<< Utils::diffclock(time2, time1) << " seconds \n";
	os_log << "Mean:" << result[0] << ", " << "Variance:" << result[1];
	root.info(os_log.str());
	os_log.str("");
	os_log.clear();

	MPI_Finalize();
	os_log << "MPI Finalize";
	root.info(os_log.str());

	if (test(original_result, result))
	{
		os_log << "The generate data has the same characteristic by statistical test!";
		root.info(os_log.str());
		os_log.str("");
		os_log.clear();
	}
	else
	{
		os_log << "The generate data does not have  the same characteristic by statistical test!";
		root.info(os_log.str());
		os_log.str("");
		os_log.clear();
	}

}

