/**
 *  @file		matrix.cpp
 *  @brief	  Implement the template code for a matrix	
 *  
 * 	Details
 *  
 *  @author		Gabriel Shelton	sheltongabe
 *  @date		  08-05-2018
 *  @version	0.1
 */

#include <algorithm>
#include <stdexcept>

#include "matrix.h"

namespace matrix {
	//
	// Default Constructor
	//
	template <int M, int N, typename T>
	Matrix<M, N, T>::Matrix() : 
			matrix(std::vector<std::vector<T>>()),
			JSONAble() {
		// Resize the number of rows to M, then resize each column to N
		for(int i = 0; i < M; ++i) {
			// Add a row and fill it with default
			this->matrix.push_back(std::vector<T>(N));
		}
	}

	//
	// Fill Constructor
	//
	template <int M, int N, typename T>
	Matrix<M, N, T>::Matrix(T value) : 
			Matrix() {
		for(auto row = this->matrix.begin(); row != this->matrix.end(); ++row)
			std::fill(row->begin(), row->end(), value);
	}

	//
	// Copy Constructor
	//
	template<int M, int N, typename T>
	Matrix<M, N, T>::Matrix(const Matrix<M, N, T>& copy) : 
			matrix(copy.matrix),
			JSONAble(copy) {

	}

	//
	// Move Constructor
	//
	template<int M, int N, typename T>
	Matrix<M, N, T>::Matrix(Matrix<M, N, T>&& copy) : 
			matrix(std::move(copy.matrix)),
			JSONAble(copy) {

	}

	//
	// JSON Constructor
	//
	template <int M, int N, typename T>
	Matrix<M, N, T>::Matrix(json::JSON j) : 
			Matrix() {
		// Check to make sure the stored dimensions are right
		if(M != std::get<int>(j["height"]) ||
				N != std::get<int>(j["width"]))
			throw std::out_of_range("width and height don't match M x N matrix");
		
		//	Pull matrix data from JSON, and fill  this->matrix
		json::JSONArray rows = std::get<json::JSONArray>(j["matrix"]);
		int y = 0, x = 0;
		for(auto row = rows.begin(); row != rows.end(); ++row) {
			x = 0;
			// Grab the value from (row, column) and store it to matrix
			for(auto value = std::get<json::JSONArray>(*row).begin(); 
					value != std::get<json::JSONArray>(*row).end();
					++value) {
				// Store it to the matrix, may throw a bad_variant_access exception
				this->matrix[y][x] = std::get<T>(*value);
				++x;
			}
			++y;
		}
	}

	// ----- Operator overloading -----

	//
	// operator== (const Matrix<M, N, O>&) -> bool
	//
	template <int M, int N, typename T>
	template <typename O>
	bool Matrix<M, N, T>::operator==(const Matrix<M, N, O>& rhs) const {
		// Compare value by value, cannot check for self comparison because
		// of the ability to compare different types
		auto rhsRow = rhs.getMatrix().begin();
		for(auto thisRow = this->matrix.begin();
				thisRow != this->matrix.end();
				++thisRow, ++rhsRow) {
			auto rhsValue = rhsRow->begin();
			for(auto thisValue = thisRow->begin();
					thisValue != thisRow->end();
					++thisValue, ++rhsValue) {
				if(*thisValue != *rhsValue)
					return false;
			}
		}

		// If we get through the array, return true
		return true;
	}

	//
	// operator+ (const Matrix<M, N, O>&) -> Matrix<M, N, T>
	//
	template <int M, int N, typename T>
	template <typename O>
	Matrix<M, N, T> Matrix<M, N, T>::
			operator+(const Matrix<M, N, O>& rhs) const {
		// Matrix storing result, copied from *this
		Matrix<M, N, T> result(*this);

		// Navigate the rhs and add to result index-by-index
		auto thisRow = result.matrix.begin();
		for(auto rhsRow = rhs.getMatrix().begin();
				rhsRow != rhs.getMatrix().end(); 
				++rhsRow, ++thisRow) {
			auto thisValue = thisRow->begin();
			for(auto rhsValue = rhsRow->begin();
					rhsValue != rhsRow->end();
					++rhsValue, ++thisValue) {
				*thisValue += *rhsValue;
			}
		}

		return std::move(result);
	}

	//
	// getJSON () -> json::JSON
	//
	template <int M, int N, typename T>
	json::JSON Matrix<M, N, T>::getJSON() const {
		json::JSON j;

		// Store the witdh and height
		j["height"] = M;
		j["width"] = N;

		// Build the jsonMatrix
		json::JSONArray arr;

		// Store the values
		for(auto row = this->matrix.begin(); row != this->matrix.end(); ++row) {
			// Build another JSONArray to the json matrix rows
			json::JSONArray rowArr;

			// store the values in the current row to the jsonArray
			for(auto value = row->begin(); value != row->end(); ++value) {
				rowArr.push_back(*value);
			}

			// Move the row to the jsonMatrix
			arr.push_back(std::move(rowArr));
		}

		// Store the jsonMatrix
		j["matrix"] = std::move(arr);

		return std::move(j);
	}

	//
	// Destructor 
	//
	template <int M, int N, typename T>
	Matrix<M, N, T>::~Matrix() {

	}

}