/*
 * utils.cpp
 *
 *  Created on: Sep 7, 2017
 *      Author: eremeykin
 */

#include "utils.h"
#include <iostream>

Utils::Utils() {
	// TODO Auto-generated constructor stub

}

void Utils::remove_row(Eigen::MatrixXd& matrix, unsigned int rowToRemove) {
	unsigned int numRows = matrix.rows() - 1;
	unsigned int numCols = matrix.cols();

	if (rowToRemove < numRows)
		matrix.block(rowToRemove, 0, numRows - rowToRemove, numCols) =
				matrix.block(rowToRemove + 1, 0, numRows - rowToRemove,
						numCols);

	matrix.conservativeResize(numRows, numCols);
}

void Utils::remove_row(Eigen::Matrix<double, Eigen::Dynamic, 1> matrix,
		unsigned int rowToRemove) {
	unsigned int numRows = matrix.rows() - 1;
	unsigned int numCols = matrix.cols();

	if (rowToRemove < numRows)
		matrix.block(rowToRemove, 0, numRows - rowToRemove, numCols) =
				matrix.block(rowToRemove + 1, 0, numRows - rowToRemove,
						numCols);

	matrix.conservativeResize(numRows, numCols);
}

void Utils::remove_row(Eigen::Matrix<int, Eigen::Dynamic, 1> matrix,
		unsigned int rowToRemove) {
	unsigned int numRows = matrix.rows() - 1;
	unsigned int numCols = matrix.cols();

	if (rowToRemove < numRows)
		matrix.block(rowToRemove, 0, numRows - rowToRemove, numCols) =
				matrix.block(rowToRemove + 1, 0, numRows - rowToRemove,
						numCols);

	matrix.conservativeResize(numRows, numCols);
}

void Utils::remove_column(Eigen::MatrixXd& matrix, unsigned int colToRemove) {
	unsigned int numRows = matrix.rows();
	unsigned int numCols = matrix.cols() - 1;

	if (colToRemove < numCols)
		matrix.block(0, colToRemove, numRows, numCols - colToRemove) =
				matrix.block(0, colToRemove + 1, numRows,
						numCols - colToRemove);

	matrix.conservativeResize(numRows, numCols);
}

void Utils::print_matrix(Eigen::MatrixXd& matrix){
	Eigen::IOFormat CleanFmt(8, 0, ", ", "\n", "[", "]");
	std::cout << matrix.format(CleanFmt) << std::endl;
}

Utils::~Utils() {
	// TODO Auto-generated destructor stub
}

