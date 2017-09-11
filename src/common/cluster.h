/*
 * cluster.h
 *
 *  Created on: Aug 29, 2017
 *      Author: eremeykin
 */

#ifndef COMMON_CLUSTER_H_
#define COMMON_CLUSTER_H_
#include <Eigen/Core>
#include <Eigen/Dense>
#include <list>
using namespace Eigen;

class Cluster {
public:
	Cluster(int cols, int label);
	virtual ~Cluster();

	void add_point(int point_index, Eigen::MatrixXd::RowXpr point);
	void print();
	int get_power();
	Matrix<double, 1, Dynamic> get_centroid();
	Matrix<double, 1, Dynamic> get_centroid(RowVectorXd def);
	std::list<int> get_points_indices();
	static Cluster merge(Cluster c1, Cluster c2);

private:
	MatrixXd data_points;
	std::list<int> points_indices;
	int label;
	int actual_rows;
	bool centroid_changed = true;
	Matrix<double, 1, Dynamic> centroid;
	Cluster(int label, MatrixXd data_points, std::list<int> points_indices);
};

#endif /* COMMON_CLUSTER_H_ */
