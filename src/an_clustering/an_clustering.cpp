/*
 * an_clustering.cpp
 *
 *  Created on: Sep 6, 2017
 *      Author: eremeykin
 */

#include "../an_clustering/an_clustering.h"
#include "Eigen/Core"
#include "../common/utils.h"
#include <iostream>
#include <ctime>
#include <iomanip>
using namespace Eigen;

ANClustering::ANClustering(MatrixXd data, double epsilon) {
	this->data = data;
	this->epsilon = epsilon;
	dim_cols = data.cols();
	dim_rows = data.rows();
}

double ANClustering::calculate_distance(Matrix<double, 1, Dynamic> point1,
		Matrix<double, 1, Dynamic> point2) {
	return (point2 - point1).squaredNorm();
}

int * ANClustering::run() {
	Matrix<double, 1, Dynamic> origin;
	origin = data.colwise().mean();
	Matrix<double, Dynamic, 1> x_to_origin(dim_rows, 1);
	for (int i = 0; i < dim_rows; i++) {
		Matrix<double, 1, Dynamic> row = data.row(i);
		x_to_origin(i, 0) = calculate_distance(row, origin);
	}
	Matrix<int, Dynamic, 1> indices(dim_rows, 1);
	for (int i = 0; i < dim_rows; i++) {
		indices(i, 0) = i;
	}

	for (int c = 0; data.rows() > 0; c++) {
		int ct_index_row, ct_index_col;
		x_to_origin.maxCoeff(&ct_index_row, &ct_index_col);
		Matrix<double, 1, Dynamic> ct, ct_old;
		std::list<int> * anomaly;
		ct = data.row(ct_index_row);
		Cluster * anomaly_cluster;
		Matrix<double, Dynamic, 1> x_to_c(data.rows(), 1);
		int max_iter = 300;
		do {
			max_iter--;
			ct_old = ct;
			anomaly_cluster = new Cluster(data.cols(), c);
			anomaly = new std::list<int>();
			for (int r = 0; r < data.rows(); r++) {
				double x_to_ct = calculate_distance(ct, data.row(r));
				if (x_to_ct <= x_to_origin(r, 0)) {
					(*anomaly_cluster).add_point(indices(r, 0), data.row(r));
					(*anomaly).push_back(r);
				}
			}
			ct = (*anomaly_cluster).get_centroid();
		} while ((ct - ct_old).squaredNorm() > epsilon);
		centroids.push_back((*anomaly_cluster).get_centroid());
		clusters.push_back(*anomaly_cluster);
		std::list<int>::const_iterator iterator;
		iterator = (*anomaly).begin();
		int new_row_count = data.rows() - (*anomaly).size();
		MatrixXd new_data(new_row_count, data.cols());
		Matrix<double, Dynamic, 1> new_x_to_origin(new_row_count, 1);
		Matrix<int, Dynamic, 1> new_indices(new_row_count, 1);
		for (int i = 0, j = 0; i < new_row_count; i++, j++) {
			while (j == *iterator && iterator != (*anomaly).end()) {
				j++;
				++iterator;
			}
			new_data.row(i) = data.row(j);
			new_x_to_origin(i, 0) = x_to_origin(j, 0);
			new_indices(i, 0) = indices(j, 0);
		}
		data = new_data;
		x_to_origin = new_x_to_origin;
		indices = new_indices;
		delete anomaly;
	}
	int * result = new int[dim_rows];
	for (unsigned int c = 0; c < clusters.size(); c++) {
		Cluster clst = clusters.at(c);
		std::list<int> lst = clst.get_points_indices();
		std::list<int>::const_iterator iterator;
		for (iterator = lst.begin(); iterator != lst.end(); ++iterator) {
			result[*iterator] = c;
		}
	}
	return result;
}


std::vector<RowVectorXd> ANClustering::get_centroids(){
	return centroids;
}

ANClustering::~ANClustering() {
// TODO Auto-generated destructor stub
}

