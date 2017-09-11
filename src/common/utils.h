/*
 * utils.h
 *
 *  Created on: Sep 7, 2017
 *      Author: eremeykin
 */

#ifndef COMMON_UTILS_H_
#define COMMON_UTILS_H_
#include "Eigen/Core"

class Utils {
public:
	Utils();
	virtual ~Utils();
	static void remove_row(Eigen::MatrixXd& matrix, unsigned int row);
	static void remove_row(Eigen::Matrix<int, Eigen::Dynamic, 1> matrix,
			unsigned int row);
	static void remove_row(Eigen::Matrix<double, Eigen::Dynamic, 1> matrix,
			unsigned int rowToRemove);
	static void remove_column(Eigen::MatrixXd& matrix, unsigned int col);
	static void print_matrix(Eigen::MatrixXd& matrix);
};

#endif /* COMMON_UTILS_H_ */
