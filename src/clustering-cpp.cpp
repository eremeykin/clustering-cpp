//============================================================================
// Name        : clustering-cpp.cpp
// Author      : Eremeykin Petr
// Version     :
// Copyright   : Eremeykin Petr for HSE
//============================================================================

#include <iostream>
#include <stdio.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <iterator>
#include <algorithm>
#include <string>
#include "file_reader.h"
#include "Eigen/Core"
#include "a_ward.h"
#include <ctime>
using namespace std;

void read_labels(int* labels, int rows, string name) {
	ifstream input_file;
	const char* file_name_char = name.c_str();
	string line;
	input_file.open(file_name_char, ios::in);
	if (input_file.is_open()) {
		int N = 0;
		while (input_file.good()) {
			getline(input_file, line);
			labels[N] = stoi(line);
			N++;
		}
		input_file.close();
	}
}

int main(int argc, char *argv[]) {
	string points_file = argv[1];
	string labels_file = argv[2];
	int kstar;
	try {
		kstar = stoi(argv[3]);
	} catch (std::logic_error e) {
		std::cout << "Do not forget number of clusters in arguments!";
		return -1;
	}
	FileReader file_reader(points_file);
	if (file_reader.read()) {
		MatrixXd data = file_reader.get_data();
		int rows = file_reader.get_dim_rows();
		int cols = file_reader.get_dim_cols();
		int * l = new int[rows];
		read_labels(l, rows, labels_file);
		int * result = new int[rows];

		clock_t begin = clock();
		AWard award(data, l, kstar);
		result = award.run();
		clock_t end = clock();

		for (int i = 0; i < rows; i++) {
			printf("%d ", result[i]);
		}
		double elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;
		printf("\ntime:%f\n", elapsed_secs);
	} else {
		printf("Unable to read the file:");
		printf(points_file.c_str());
		return -1;
	}
	return 0;
}

