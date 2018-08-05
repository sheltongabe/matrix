#include <iostream>

#include "json_util/json_file.h"
#include "matrix/matrix.h"

int main() {
	// Test Default Constructor
	matrix::Matrix<2, 2, int> test;

	// Test Fill Constructor
	matrix::Matrix<3, 3, double> fill_test(4.1);
	json::JSONFile::writeJSON(std::move("test_fill.json"), fill_test);

	// Test Copy Constructor
	matrix::Matrix<2, 2, int> copy(test);

	// Test getWidth(), getHeight()
	if(copy.getWidth() != 2 || copy.getHeight() != 2)
		return 1;

	// Test JSON Constructor
	json::JSONFile::writeJSON(std::move("test.json"), test);
	json::JSONFile::writeJSON(std::move("test_copy.json"), copy);
	matrix::Matrix<2, 2, int> jsonMatrix(std::move(
			json::JSONFile::readJSON(std::move("test.json"))));
	
	return 0;
}