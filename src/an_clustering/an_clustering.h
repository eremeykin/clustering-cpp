/*
 * an_clustering.h
 *
 *  Created on: Sep 6, 2017
 *      Author: eremeykin
 */

#ifndef AN_CLUSTERING_AN_CLUSTERING_H_
#define AN_CLUSTERING_AN_CLUSTERING_H_
#include <vector>
#include "Eigen/Core"
#include "../common/cluster.h"

using namespace Eigen;

class ANClustering {
public:
	ANClustering(MatrixXd data, double epsilon);
	virtual ~ANClustering();
	int * run();

private:
	MatrixXd data;
	std::vector<Cluster> clusters;
	int dim_cols;
	int dim_rows;
	double epsilon;
	std::vector<RowVectorXd> centroids;
	double calculate_distance(Matrix<double, 1, Dynamic> point1, Matrix<double, 1, Dynamic> point2);
	std::vector<RowVectorXd> get_centroids();
};

#endif /* AN_CLUSTERING_AN_CLUSTERING_H_ */
