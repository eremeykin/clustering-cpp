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
	Matrix<double, Dynamic, Dynamic> m(0, cols);
	this->data_points = m;
	this->label = label;
}

Cluster::Cluster(int label, MatrixXd data_points,
		std::list<int> points_indices) {
	this->label = label;
	this->data_points = data_points;
	this->points_indices = points_indices;
	this->centroid_changed = true;
}

Cluster Cluster::merge(Cluster c1, Cluster c2) {
	assert(c1.label != c2.label);
	int cols1 = c1.data_points.cols();
	int cols2 = c2.data_points.cols();
	assert(cols1 == cols2);
	int label = c1.label < c2.label ? c1.label : c2.label;
	MatrixXd cumulative_data(c1.data_points.rows() + c2.data_points.rows(),
			c1.data_points.cols());
	cumulative_data << c1.data_points, c2.data_points;
	c1.points_indices.splice(c1.points_indices.end(), c2.points_indices);
	Cluster result(label, cumulative_data, c1.points_indices);
	return result;
}

int Cluster::get_power() {
	return data_points.rows();
}

std::list<int> Cluster::get_points_indices() {
	return points_indices;
}

Matrix<double, 1, Dynamic> Cluster::get_centroid() {
	if (centroid_changed) {
		this->centroid = data_points.colwise().mean();
		centroid_changed = false;
	}
	return centroid;

}

void Cluster::add_point(int point_index, Eigen::MatrixXd::RowXpr point) {
	int cols = data_points.cols();
	data_points.conservativeResize(data_points.rows() + 1, cols);
	data_points.row(data_points.rows() - 1) = point;
	points_indices.push_front(point_index);
	centroid_changed = true;
}

void Cluster::print() {
	Eigen::IOFormat CleanFmt(8, 0, ", ", "\n", "[", "]");
	printf("\n%s #%d [%d] (", "[Cluster", label, this->get_power());
	std::list<int>::const_iterator iterator;
	std::list<int>::const_iterator end = points_indices.end();
	for (iterator = points_indices.begin(); iterator != end; ++iterator) {
		std::cout << " " << *iterator;
	}
	std::cout << "]";
	printf(" ]%s #%d\n", "Cluster", label);
}

Cluster::~Cluster() {
	// TODO Auto-generated destructor stub
}

