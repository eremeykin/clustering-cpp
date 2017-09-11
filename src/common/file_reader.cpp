/*
 * file_reader.cpp
 *
 *  Created on: Aug 25, 2017
 *      Author: eremeykin
 */

#include "file_reader.h"

#include <string>
#include <stdio.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <iterator>
#include <algorithm>
#include <string>
#include <Eigen/Core>

FileReader::FileReader(std::string name) {
	this->name = name;
}

int FileReader::count_dimension(string sample) {
	istringstream iss(sample);
	istream_iterator<string> itr = istream_iterator<string>(iss);
	istream_iterator<string> eos = istream_iterator<string>();
	int i = 0;
	while (itr != eos) {
		i++;
		itr++;
	}
	return i;
}

void FileReader::get_dim() {
	ifstream input_file;
	const char* file_name_char = this->name.c_str();
	string line;
	input_file.open(file_name_char, ios::in);
	if (input_file.is_open()) {
		int V = 0;
		int N = 0;
		if (input_file.good()) {
			getline(input_file, line);
			V = this->count_dimension(line);
			N++;
		}
		while (input_file.good()) {
			getline(input_file, line);
			N++;
		}
		input_file.close();
		this->dim_cols = V;
		this->dim_rows = N;
	} else {
		cout << "Unable to open file to get dimension:" << this->name;
	}
}

bool FileReader::read() {
	if (this->ready) {
		return 0;
	}
	ifstream input_file;
	const char* file_name_char = name.c_str();
	string line;
	double * pdata = NULL;
	this->get_dim();

	input_file.open(file_name_char, ios::in);
	if (input_file.is_open()) {
		Eigen::Matrix<double, Eigen::Dynamic, Eigen::Dynamic> m(dim_rows,
				dim_cols);
		int row = 0;
		while (input_file.good()) {
			getline(input_file, line);
			double * result = new double[this->dim_cols];
			this->parse_line(line, result);
			for (int col = 0; col < this->dim_cols; col++) {
				m(row, col) = result[col];
			}
			delete result;
			row++;
		}
		input_file.close();
		this->data = m;
		this->ready = true;
		return true;
	} else {
		cout << "Unable to open file to load data";
		return 1;
	}
}

void FileReader::print() {
	cout << "-----------------\n";
	Eigen::IOFormat CleanFmt(8, 0, ", ", "\n", "[", "]");
	cout << this->data.format(CleanFmt) << endl;
	cout << "-----------------\n";
}

int FileReader::get_dim_rows() {
	return this->dim_rows;
}

int FileReader::get_dim_cols() {
	return this->dim_cols;
}

void FileReader::parse_line(string line, double * result) {
	istringstream iss(line);
	istream_iterator<double> itr = istream_iterator<double>(iss);
	istream_iterator<double> eos = istream_iterator<double>();
	int i = 0;
	while (itr != eos) {
		result[i++] = *itr++;
	}
}

Eigen::Matrix<double, Eigen::Dynamic, Eigen::Dynamic> FileReader::get_data() {
	return this->data;
}

FileReader::~FileReader() {
}

