//============================================================================
// Name        : clustering-cpp.cpp
// Author      : Eremeykin Petr
// Version     :
// Copyright   : Eremeykin Petr for HSE
//============================================================================

#include <stdio.h>
#include <string>
#include <iostream>
//#include "an-clustering.h"
#include "run.h"
using namespace std;

int main(int argc, char *argv[]) {
	std::string cmd = argv[1];
	argv++;
	if (!cmd.compare(string("anomal"))) {
		run_an_clustering(argv);
	} else if (!cmd.compare(string("award"))) {
		run_award(argv);
	} else {
		printf("Unknown command:%s", argv);
	}
	return 0;
}

