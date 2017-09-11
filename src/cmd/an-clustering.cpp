//============================================================================
// Name        : clustering-cpp.cpp
// Author      : Eremeykin Petr
// Version     :
// Copyright   : Eremeykin Petr for HSE
//============================================================================

#include <iostream>
#include <stdio.h>
#include <fstream>
#include <sstream>
#include <iterator>
#include <algorithm>
#include <string>
#include "Eigen/Core"
#include <ctime>
#include "../an_clustering/an_clustering.h"
#include "../common/file_reader.h"
#include "run.h"
using namespace std;


void run_an_clustering(char *argv[]) {
	string points_file = argv[1];
	FileReader file_reader(points_file);
	if (file_reader.read()) {
		MatrixXd data = file_reader.get_data();
		int rows = file_reader.get_dim_rows();
		int * result = new int[rows];

		ANClustering an_clustering(data, 0.00001);
		result = an_clustering.run();
		for (int i = 0; i < rows; i++) {
			printf("%d\n", result[i]);
		}
	} else {
		printf("Unable to read the file:");
		printf(points_file.c_str());
	}
}
