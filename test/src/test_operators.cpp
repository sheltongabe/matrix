/**
 *  @file		test_operators.cpp
 *  @brief	  Entry for test-cases that test the operators for the matrix-code	
 *  
 * 	Test each operator as it is added
 *  
 *  @author		Gabriel Shelton	sheltongabe
 *  @date		  08-14-2018
 *  @version	0.1
 */

#include <iostream>

#include "matrix/matrix.h"
#include "json_util/json_file.h"

using matrix::Matrix;

/// Entry point into the code
int main() {

	// ----- Test Equalvalency -----
	{
		Matrix<3, 3, double> a(3);
		Matrix<3, 3, double> b(2);
		Matrix<2, 3, int> c(4);
		Matrix<3, 3, double> d(3);

		if(a == b)
			return 1;
		
		if(a != d)
			return 1;
	}

	// ----- Addition and Subtraction -----
	{
		if(Matrix<3, 3, int>(2) + Matrix<3, 3, int>(4) != Matrix<3, 3, int>(6))
			return 1;

		Matrix<2, 3, int> a(4);
		a += 3;
		if(a != Matrix<2, 3, int>(7))
			return 1;

		if(Matrix<3, 3, int>(2) - Matrix<3, 3, int>(4) != Matrix<3, 3, int>(-2))
			return 1;

		Matrix<2, 3, int> b(4);
		b -= 3;
		if(b != Matrix<2, 3, int>(1))
			return 1;
	}

	// ----- Multiplication-by-a-scalar Test -----
	{
		if(Matrix<3, 3, int>(3) * 2 != Matrix<3, 3, int>(6))
			return 1;
		
		Matrix<4, 100, int> a(5);
		a *= 3;
		if(a != Matrix<4, 100, int>(15))
			return 1;
	}

	// ----- Multiplication-by-a-matrix Test -----
	{
		Matrix<2, 2> A;
		A[0][0] = 1.0;
		A[0][1] = 2.0;
		A[1][0] = 3.0;
		A[1][1] = 4.0;
		Matrix<2, 2> B(3.5);

		Matrix<2, 2> C = A * B;

		std::cout << static_cast<std::string>(C) << std::endl;
	}

	// ----- Array subscript -----
	{
		Matrix A(5);
		A[0][1] = 4;
		std::cout << A[0][1] << std::endl;
	}

	// ----- getColumn() / getRow() -----
	{
		Matrix A(5);
		A[0][1] = 4;
		std::vector<int> col1 = A.getColumn(1);
		std::cout << col1[0] << std::endl;
	}

	return 0;
}