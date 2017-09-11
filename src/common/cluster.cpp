/*
 * cluster.cpp
 *
 *  Created on: Aug 29, 2017
 *      Author: eremeykin
 */

#include "cluster.h"
#include <Eigen/Core>
#include <stdio.h>
#include <iostream>
#include <list>

using namespace Eigen;

Cluster::Cluster(int cols, int label) {
	Matrix<double, Dynamic, Dynamic> m(1, cols);
	this->data_points = m;
	this->label = label;
	this->actual_rows = 0;
}

Cluster::Cluster(int label, MatrixXd data_points,
		std::list<int> points_indices) {
	this->label = label;
	this->data_points = data_points;
	this->points_indices = points_indices;
	this->centroid_changed = true;
	this->actual_rows = data_points.rows();
}

Cluster Cluster::merge(Cluster c1, Cluster c2) {
	assert(c1.label != c2.label);
	int cols1 = c1.data_points.cols();
	int cols2 = c2.data_points.cols();
	assert(cols1 == cols2);
	int label = c1.label < c2.label ? c1.label : c2.label;
	MatrixXd cumulative_data(c1.actual_rows + c2.actual_rows,
			c1.data_points.cols());
	cumulative_data << c1.data_points.block(0, 0, c1.actual_rows, cols1), c2.data_points.block(
			0, 0, c2.actual_rows, cols2);
	c1.points_indices.splice(c1.points_indices.end(), c2.points_indices);
	Cluster result(label, cumulative_data, c1.points_indices);
	return result;
}

int Cluster::get_power() {
	return actual_rows;
//	return data_points.rows();
}

std::list<int> Cluster::get_points_indices() {
	return points_indices;
}

Matrix<double, 1, Dynamic> Cluster::get_centroid() {
	assert(actual_rows > 0);
	if (centroid_changed) {
		this->centroid = data_points.block(0, 0, actual_rows,
				data_points.cols()).colwise().mean();
		centroid_changed = false;
	}
	return centroid;

}

Matrix<double, 1, Dynamic> Cluster::get_centroid(RowVectorXd def) {
	if (actual_rows == 0){
		return def;
	}
		return this->get_centroid();
//	}
//	if (centroid_changed) {
//		this->centroid = data_points.block(0, 0, actual_rows,
//				data_points.cols()).colwise().mean();
//		centroid_changed = false;
//	}
	return centroid;

}

void Cluster::add_point(int point_index, Eigen::MatrixXd::RowXpr point) {
	int data_rows = data_points.rows();
	int cols = data_points.cols();
	if (actual_rows + 1 > data_rows) {
		data_points.conservativeResize(data_rows * 2, cols);
	}
	data_points.row(actual_rows) = point;
	actual_rows++;
	points_indices.push_front(point_index);
	centroid_changed = true;
}

void Cluster::print() {
	Eigen::IOFormat CleanFmt(5, 0, ", ", "\n", "[", "]");
	if (actual_rows==0){
		printf("empty");
		return;
	}
	std::cout
			<< data_points.block(0, 0, actual_rows, data_points.cols()).format(
					CleanFmt) << std::endl;
//	printf("\n%s #%d [%d] (", "[Cluster", label, this->get_power());
//	std::list<int>::const_iterator iterator;
//	std::list<int>::const_iterator end = points_indices.end();
//	for (iterator = points_indices.begin(); iterator != end; ++iterator) {
//		std::cout << " " << *iterator;
//	}
//	std::cout << "]";
//	printf(" ]%s #%d\n", "Cluster", label);
}

Cluster::~Cluster() {
	// TODO Auto-generated destructor stub
}

