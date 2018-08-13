/**
 *  @file		matrix.cpp
 *  @brief	  Implement the template code for a matrix	
 *  
 * 	Details
 *  
 *  @author		Gabriel Shelton	sheltongabe
 *  @date		  08-13-2018
 *  @version	0.1
 */

#include <algorithm>
#include <type_traits>

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
	// operator == (const Matrix<M, N, T>&) -> bool
	//
	template <int M, int N, typename T>
	bool Matrix<M, N, T>::operator ==(const Matrix<M, N, T>& rhs) const {
		// Check for self comparison
		if(this == &rhs)
			return true;

		// Move over the matrix and check for any inequalities
		for(int row = 0; row < M; ++row) {
			for(int col = 0; col < N; ++col) {
				if(this->matrix[row][col] != rhs.matrix[row][col])
					return false;
			}
		}

		// If we get through the array, return true
		return true;
	}


	//
	// operator += (const Matrix<M, N, T>&) -> Matrix<M, N, T>&
	//
	template <int M, int N, typename T>
	Matrix<M, N, T>& Matrix<M, N, T>::operator += (const Matrix<M, N, T>& rhs) {
		// Do the addition to each index of this
		this->forEachIndex(rhs, [] (const T& left, const T& right) {
			return left + right;
		});

		return *this;
	}

	//
	// operator + (const Matrix<M, N, T>&) -> Matrix<M, N, T>
	//
	template <int M, int N, typename T>
	Matrix<M, N, T> Matrix<M, N, T>::operator + (const Matrix<M, N, T>& rhs) {
		// perform the addition, and copy this to result
		(*this) += rhs;

		// Return a copy of this, for chaining
		return *this;
	}

	//
	// operator -= (const Matrix<M, N, T>&) -> Matrix<M, N, T>&
	//
	template<int M, int N, typename T>
	Matrix<M, N, T>& Matrix<M, N, T>::operator -= (const Matrix<M, N, T>& rhs) {
		// Subtract from each index of this, using rhs as an input
		this->forEachIndex(rhs, [] (const T& left, const T& right) {
			return left - right;
		});

		return *this;
	}

	//
	// operator - (const Matrix<M, N, O>&) -> Matrix<M, N, T>
	//
	template <int M, int N, typename T>
	Matrix<M, N, T> Matrix<M, N, T>::operator - (const Matrix<M, N, T>& rhs) {
		// Use the already implemented -= operator
		(*this) -= rhs;

		return *this;
	}

	//
	// operator *= (const T& scalar) -> Matrix<M, N, T>
	//
	template <int M, int N, typename T>
	Matrix<M, N, T>& Matrix<M, N, T>::operator *= (const T& scalar) {
		// Take each element in this and multiply it by scalar
		this->forEachIndex(*this, [=, &scalar] (const T& left, const T& right) {
			return scalar * right;
		});

		return *this;
	}


	//
	// operator* (const O&) -> Matrix<M, N, T>
	//
	template <int M, int N, typename T>
	Matrix<M, N, T> Matrix<M, N, T>::operator * (const T& scalar) {
		// Use the existing *= operator
		(*this) *= scalar;

		return *this;
	}

	// 
	// getColumn (unsigned int) -> ColumnVector<M, T>
	//
	template <int M, int N, typename T>
	std::vector<T> Matrix<M, N, T>::getColumn(unsigned int index) const {
		// Check for invalid index
		if(index >= N)
			throw std::out_of_range("Index must be within number of columns");

		std::vector<T> vec;
		for(int i = 0; i < M; ++i)
			vec.push_back(this->matrix[i][index]);

		return std::move(vec);
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
	// forEachRhs (const Matrix<M, N, T>&, 
	// std::function<T(const T&, const T&)) -> void
	//
	template <int M, int N, typename T>
	template <typename Operation>
	void Matrix<M, N, T>::forEachIndex(const Matrix<M, N, T>& rhs,
			Operation operation) {
		// Navigate the 2D Matrix
		for(int row = 0; row < M; ++row) {
			for(int col = 0; col < N; ++col) {
				// Apply the operation and store the returned value to the matrix
				this->matrix[row][col] = operation(this->matrix[row][col], rhs.matrix[row][col]);
			}
		}
	}


	//
	// Destructor 
	//
	template <int M, int N, typename T>
	Matrix<M, N, T>::~Matrix() {

	}

}