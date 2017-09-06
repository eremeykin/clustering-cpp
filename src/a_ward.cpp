/*
 * AWard.cpp
 *
 *  Created on: Aug 25, 2017
 *      Author: eremeykin
 */

#include "a_ward.h"
#include <limits.h>
#include <assert.h>
#include <iostream>
#include <map>
using namespace Eigen;

AWard::AWard(Matrix<double, Dynamic, Dynamic> data, int* labels, int kstar) {
	this->data = data;
	this->labels = labels;
	this->kstar = kstar;
	distance_matrix_init = false;
	dim_cols = data.cols();
	dim_rows = data.rows();
	int curr_label;
	for (int i = 0; i < dim_rows; i++) {
		curr_label = labels[i];
		for (int c = clusters.size(); c <= curr_label; c++) {
			Cluster newcluster = Cluster(dim_cols, c);
			clusters.push_back(newcluster);
		}
		MatrixXd::RowXpr point = data.row(i);
		clusters.at(curr_label).add_point(i, point);
	}
}

double AWard::award_distance(Cluster c1, Cluster c2) {
	double na = (double) c1.get_power();
	double nb = (double) c2.get_power();
	Matrix<double, 1, Dynamic> centroid1, centroid2;
	centroid1 = c1.get_centroid();
	centroid2 = c2.get_centroid();
	Matrix<double, 1, Dynamic> delta = centroid2 - centroid1;
	double distance = ((na * nb) / (na + nb)) * delta.squaredNorm();
	return distance;
}

void AWard::calculate_distance_matrix() {
	int cnum = clusters.size();
	distance_matrix = Matrix<double, Dynamic, Dynamic>::Constant(cnum, cnum, 0);
	for (int i = 0; i < cnum; i++) {
		for (int j = i + 1; j < cnum; j++) {
			distance_matrix(i, j) = award_distance(clusters.at(i),
					clusters.at(j));
		}
	}
	this->distance_matrix = distance_matrix;
	distance_matrix_init = true;
}

void AWard::find_nearest(std::ptrdiff_t * c1, std::ptrdiff_t * c2) {
	if (!distance_matrix_init) {
		calculate_distance_matrix();
	}
	int cnum = clusters.size();
	double min = distance_matrix(0, 1);
	*c1 = 0;
	*c2 = 1;

	for (int i = 0; i < cnum; i++) {
		for (int j = i + 1; j < cnum; j++) {
			if (distance_matrix(i, j) < min) {
				min = distance_matrix(i, j);
				*c1 = i;
				*c2 = j;
			}
		}
	}
}

void AWard::print_distance_matrix() {
	std::cout << std::endl << "DM:" << std::endl;
	for (int i = 0; i < distance_matrix.rows(); i++) {
		for (int j = 0; j < distance_matrix.cols(); j++) {
			printf("%6.3f ", distance_matrix(i, j));
		}
		printf("\n");
	}
}

void AWard::print_trace() {
	std::cout << "Clusters:";
	for (int k = 0; k < clusters.size(); k++) {
		clusters.at(k).print();
	}
	print_distance_matrix();
	std::cout << "\n\n\n";
}

int * AWard::run() {
	for (int k = clusters.size(); k > kstar; k--) {
		std::ptrdiff_t c1 = -1, c2 = -1;
		find_nearest(&c1, &c2);
		Cluster new_cluster = Cluster::merge(clusters.at(c1), clusters.at(c2));
		delete_cluster(c2);
		update_cluster(c1, new_cluster);
	}
	int * result = new int[dim_rows];
	for (int c = 0; c < clusters.size(); c++) {
		Cluster clst = clusters.at(c);
		std::list<int> lst = clst.get_points_indices();
		std::list<int>::const_iterator iterator;
		for (iterator = lst.begin(); iterator != lst.end(); ++iterator) {
			result[*iterator] = c;
		}
	}
	return result;
}

void AWard::remove_row(Eigen::MatrixXd& matrix, unsigned int rowToRemove) {
	unsigned int numRows = matrix.rows() - 1;
	unsigned int numCols = matrix.cols();

	if (rowToRemove < numRows)
		matrix.block(rowToRemove, 0, numRows - rowToRemove, numCols) =
				matrix.block(rowToRemove + 1, 0, numRows - rowToRemove,
						numCols);

	matrix.conservativeResize(numRows, numCols);
}

void AWard::remove_column(Eigen::MatrixXd& matrix, unsigned int colToRemove) {
	unsigned int numRows = matrix.rows();
	unsigned int numCols = matrix.cols() - 1;

	if (colToRemove < numCols)
		matrix.block(0, colToRemove, numRows, numCols - colToRemove) =
				matrix.block(0, colToRemove + 1, numRows,
						numCols - colToRemove);

	matrix.conservativeResize(numRows, numCols);
}

void AWard::delete_cluster(int c) {
	clusters.erase(clusters.begin() + c);
	remove_column(distance_matrix, c);
	remove_row(distance_matrix, c);
}

void AWard::update_cluster(int at_index, Cluster new_cluster) {
	clusters.at(at_index) = new_cluster;
	for (int i = 0; i < clusters.size(); i++) {
		if (i < at_index) {
			distance_matrix(i, at_index) = award_distance(new_cluster,
					clusters.at(i));
		}
		if (i > at_index) {
			distance_matrix(at_index, i) = award_distance(new_cluster,
					clusters.at(i));
		}
	}
}

AWard::~AWard() {
// TODO Auto-generated destructor stub
}

