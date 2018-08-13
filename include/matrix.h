/**
 *  @file		matrix.h
 *  @brief	  Define a class that holds things in a 2D mathmatical structure	
 *  
 * 	The things that are stored in the matrix are expected to have reasonable
 * 	definitions for matrix addition, multiplication by a scalor, or multiplication
 * 	by a matrix which follows the size rules.
 *  
 *  @author		Gabriel Shelton	sheltongabe
 *  @date		  08-13-2018
 *  @version	0.1
 */

#ifndef MATRIX_H
#define MATRIX_H

#include <vector>
#include <functional>
#include <stdexcept>

#include "json_util/jsonable.h"

namespace matrix {

	/**
	 * 	@class		Matrix
	 * 	@brief		Define the template for a matrix
	 * 
	 * 	Must be well formed for operators to function correctly
	 * 
	 * 	Stores things in a 2D math structure, that follow those three math rules
	 * 
	 */
	template <int M = 3, int N = 3, typename T = double>
	class Matrix : public json::JSONAble {
		public:
			/**
			 * 	@brief	Default Constructor
			 * 
			 * 	Details
			 * 
			 * 	@version	0.1
			 */
			Matrix();

			/**
			 * 	@brief	Fill Constructor
			 * 
			 * 	Fills the matrix with the value provided
			 * 
			 * 	@version	0.1
			 */
			Matrix(T value);

			/**
			 * 	@brief	Copy Constructor
			 * 
			 * 	Details
			 * 
			 * 	@version	0.1
			 */
			Matrix(const Matrix& copy);

			/**
			 * 	@brief	Move Constructor
			 * 
			 * 	Details
			 * 
			 * 	@version	0.1
			 */
			Matrix(Matrix&& copy);

			/**
			 * 	@brief 	Build the vector from a JSON object
			 * 
			 * 	Details
			 * 
			 * 	@version 0.1
			 */
			Matrix(json::JSON j);

			/**
			 * 	@brief 	Add a row to the matrix
			 * 
			 * 	Ensure that the vector length is equal to N
			 * 
			 * @param 	std::vector<T>	Values to add to the matrix
			 * 
			 * 	@version 0.1
			 */
			inline void addRow(std::vector<T> row) {
				this->matrix.push_back(row);
			}

			/**
			 * 	@brief 	Add a column to the matrix
			 * 
			 * 	Ensure that the vector length is equal to M
			 * 
			 * @param 	std::vector<T>	Values to add to the matrix
			 * 
			 * 	@version 0.1
			 */
			void addColumn(std::vector<T> column) {
				for(int i = 0; i < M; ++i)
					this->matrix[i].push_back(column[i]);
			}

			// ----- Operator overloads -----
			/**
			 * 	@brief  Compare two Matrices for in-equalivalency
			 * 
			 * 	Will use the previously declared operator== to compare
			 * 	then invert the value
			 * 
			 * 	@param	const Matrix&		Right side of the comparison
			 * 	@return	  bool						 Result of the comparison
			 * 
			 * 	@version 0.1
			 */
			inline bool operator!=(const Matrix<M, N, T>& rhs) const { 
					return !(*this == rhs); }

			/**
			 * 	@brief  Compare two Matrices for equalivalency
			 * 
			 * 	Will first check for self comparision
			 * 	Then compare contents using operator==
			 * 
			 * 	@param	const Matrix&		 Right side of the comparison
			 * 	@return	  bool						  Result of the comparison
			 * 
			 * 	@version 0.1
			 */
			bool operator==(const Matrix<M, N, T>& rhs) const;

			/**
			 * 	@brief 	Implement for when a Matrix of equivalent dimension is added to this one
			 * 
			 * @param const Matrix&			Reference to rhs of operation
			 * @return Matrix<M, N, T>&	  Reference to this
			 */
			Matrix<M, N, T>& operator += (const Matrix<M, N, T>& rhs);

			/**
			 * 	@brief  Add two Matrices of equal dimensions
			 * 
			 * 	Use the already implemented += operator
			 * 	and return a copy of this
			 * 
			 * 	@param	const Matrix&		Right side of the addition
			 * 	@return	  Matrix<M, N, T>	result of addition
			 * 
			 * 	@version 0.1
			 */
			Matrix<M, N, T> operator + (const Matrix<M, N, T>& rhs);

			/**
			 * 	@brief 	Implement for when a Matrix of equivalent dimension is subtracted from this one
			 * 
			 * @param const Matrix&			Reference to rhs of operation
			 * @return Matrix<M, N, T>&	  Reference to this
			 */
			Matrix<M, N, T>& operator -= (const Matrix<M, N, T>& rhs);

			/**
			 * 	@brief  Subtract two Matrices of equal dimensions
			 * 
			 * 	Use the already implemented -= operator,
			 * 	and return a copy of this
			 * 
			 * 	@param	const Matrix&		Right side of the subtraction
			 * 	@return	  Matrix<M, N, T>	result of subtraction
			 * 
			 * 	@version 0.1
			 */
			Matrix<M, N, T> operator - (const Matrix<M, N, T>& rhs);

			/**
			 * 	@brief 	Implement for when the matrix is multiplied by a scalar
			 * 
			 * @param const T&					Reference to rhs of operation
			 * @return Matrix<M, N, T>&	  Reference to this
			 */
			Matrix<M, N, T>& operator *= (const T& scalar);

			/**
			 * 	@brief  Multiply a Matrix by a scalor T
			 * 
			 * 	Use the already implemented *= code to implement it
			 * 
			 * 	@param	const T&			   Right side of the multiplication
			 * 	@return	  Matrix<M, N, T>	result of multiplication
			 * 
			 * 	@version 0.1
			 */
			Matrix<M, N, T> operator * (const T& scalar);

			/**
			 * 	@brief 	Overload for an l-value of the array-subscript operator
			 * 
			 * 	Check that the index less than the number of rows, and if so:
			 * 	return the std::vector<T>&
			 * 
			 * 	@param	int							Index of row
			 * 	@return   std::vector<T>&	row
			 */
			inline std::vector<T>& operator [] (unsigned int index) {
				if(index < M)
					return this->matrix[index];
				else
					throw std::out_of_range("Index must be within number of rows");
			}

			/**
			 * 	@brief 	Overload for an r-value of the array-subscript operator
			 * 
			 * 	Check that the index less than the number of rows, and if so:
			 * 	return the std::vector<T>&
			 * 
			 * 	@param				int							Index of row
			 * 	@return   const std::vector<T>&		row
			 */
			inline const std::vector<T>& operator [] (unsigned int index) const {
				if(index < M)
					return this->matrix[index];
				else
					throw std::out_of_range("Index must be within number of rows");
			}

			/// Get a column in vector form from the matrix
			std::vector<T> getColumn(unsigned int index) const;

			/// Get a row in vector form from the matrix
			std::vector<T> getRow(unsigned int index) const {
				// Check for invalid index
				if(index >= M)
					throw std::out_of_range("Index must be within number of rows");

				std::vector<T> vec;
				for(int i = 0; i < N; ++i)
					vec.push_back(this->matrix[index][i]);

				return std::move(vec);
			}

			// ----- Inline Methods -----
			/// Get the width of the Matrix
			inline int getWidth() const { return N; }

			/// Get the number of rows in the matrix
			inline int getHeight() const { return M; }

			/// Get the number of indises in the matrix
			inline int size() const { return M * N; }

			/// Get the matrix stored as a const&
			inline const std::vector<std::vector<T>>& getMatrix() const { 
					return this->matrix; }

			/**
			 * 	@brief 	Get the json form of the Matrix
			 * 
			 * 	Convert the matrix to a JSON map, overloading the getJSON()
			 * 
			 * 	@version 0.1
			 */
			virtual json::JSON getJSON() const;

			/**
			 * 	@brief	Destructor
			 * 
			 * 	Details
			 * 
			 * 	@version	0.1
			 */
			~Matrix();

		protected:
			/// Where the matrix is actually stored
			std::vector<std::vector<T>> matrix;

			/**
			 * 	@brief 	Navigate through the left and through the other matrix, applying the function
			 * 
			 *  Operation is a lambda / function to be applied to each index
			 * 	The first paramater of Operation is from this matrix, the other: rhs
			 *	Addition, Subtraction, and Multiplication, good examples
			 * 	Navigate by index and apply the function provided
			 * 
			 * 	@param	const Matrix<M, N, T>&						Matrix on the right of the operation
			 * 	@param	std::function<T(const T&, constT&)>	Operation to apply to each index
			 * 	@return	  Matrix<N, R, T>									Matrix built
			 * 
			 */
			template <typename Operation>
			void forEachIndex(const Matrix<M, N, T>& rhs,
					Operation operation);

		private:

	};
}

#include "matrix/matrix.cpp"

#endif