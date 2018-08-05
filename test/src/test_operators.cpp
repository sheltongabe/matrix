/**
 *  @file		test_operators.cpp
 *  @brief	  Entry for test-cases that test the operators for the matrix-code	
 *  
 * 	Test each operator as it is added
 *  
 *  @author		Gabriel Shelton	sheltongabe
 *  @date	08-05-2018
 *  @version	0.1
 */

#include <iostream>

#include "matrix/matrix.h"

/// Entry point into the code
int main() {
	// Create some test matrices
	matrix::Matrix<3, 3, int> int3_3(5);
	matrix::Matrix<3, 3, int> int3_3_diff(4);
	matrix::Matrix<3, 3, int> int3_3_copy(int3_3);
	matrix::Matrix<3, 3, double> double3_3(5);
	matrix::Matrix<3, 2, int> int3_2(2);
	matrix::Matrix<2, 3, double> double2_3(5);

	// comparison of int 3 x 3 and copy -> should be equal
	if(int3_3 != int3_3_copy)
		return 1;

	// compare 3 x 3 type wit different values
	if(int3_3 == int3_3_diff)
		return 1;

	// // Compare cross types
	// if(int3_3 != double3_3)
	// 	return 1;

	// // Compare cross size
	// if(int3_3 == int3_2)
	// 	return 1;

	// if(int3_2 == double2_3)
	// 	return 1;

	return 0;
}