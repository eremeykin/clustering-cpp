/*
 * file_reader.h
 *
 *  Created on: Aug 25, 2017
 *      Author: eremeykin
 */

#ifndef FILE_READER_H_
#define FILE_READER_H_
#include <string>
#include <Eigen/Core>

using namespace std;

class FileReader {
public:
	FileReader(string name);
	virtual ~FileReader();
	double get_array();
	int get_dim_rows();
	int get_dim_cols();
	bool read();
	void print();
	Eigen::Matrix<double, Eigen::Dynamic, Eigen::Dynamic> get_data();
private:
	string name;
	int dim_rows = 0;
	int dim_cols = 0;
	bool ready = false;
	Eigen::Matrix<double, Eigen::Dynamic, Eigen::Dynamic> data;
	void parse_line(string line, double * result);
	int count_dimension(string sample);
	void get_dim();
};

#endif /* FILE_READER_H_ */
