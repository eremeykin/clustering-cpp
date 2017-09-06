/*
 * AWard.h
 *
 *  Created on: Aug 25, 2017
 *      Author: eremeykin
 */

#ifndef A_WARD_H_
#define A_WARD_H_
#include "Eigen/Core"
#include "cluster.h"
#include <vector>
using namespace Eigen;

class AWard {
public:
	AWard(Matrix<double, Dynamic, Dynamic> data, int* labels, int kstar);
	virtual ~AWard();

public:
	int * run();

private:
	Matrix<double, Dynamic, Dynamic> data;
	Matrix<double, Dynamic, Dynamic> distance_matrix;
	int * labels;
	int kstar;
	int dim_cols;
	int dim_rows;
	bool distance_matrix_init;
	std::vector<Cluster> clusters;
	void calculate_distance_matrix();
	double ward_distanse();
	double award_distance(Cluster c1, Cluster c2);
	void find_nearest(std::ptrdiff_t * c1, std::ptrdiff_t * c2);
	void update_cluster(int at_index, Cluster cluster);
	void delete_cluster(int c);
	void print_distance_matrix();
	void remove_row(Eigen::MatrixXd& matrix, unsigned int row);
	void remove_column(Eigen::MatrixXd& matrix, unsigned int col);
	void print_trace();
};

#endif /* A_WARD_H_ */
