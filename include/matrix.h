/**
 *  @file		matrix.h
 *  @brief	  Define a class that holds things in a 2D mathmatical structure	
 *  
 * 	The things that are stored in the matrix are expected to have reasonable
 * 	definitions for matrix addition, multiplication by a scalor, or multiplication
 * 	by a matrix which follows the size rules.
 *  
 *  @author		Gabriel Shelton	sheltongabe
 *  @date		  08-05-2018
 *  @version	0.1
 */

#ifndef MATRIX_H
#define MATRIX_H

#include <vector>

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

			// ----- Operator overloads -----
			/**
			 * 	@brief  Compare two Matrices for equalivalency
			 * 
			 * 	Will first check for self comparision, then the dimensions, then the T
			 * 	Then compare contents using operator==
			 * 
			 * 	@param	const Matrix&		Right side of the comparison
			 * 	@return	  bool						  Result of the comparison
			 * 
			 * 	@version 0.1
			 */
			template <typename O>
			bool operator==(const Matrix<M, N, O>& rhs) const;

			/**
			 * 	@brief  Compare two Matrices for in-equalivalency
			 * 
			 * 	Will use the previously declared operator== to compare
			 * 	then invert the value
			 * 
			 * 	@param	const Matrix&		Right side of the comparison
			 * 	@return	  bool						  Result of the comparison
			 * 
			 * 	@version 0.1
			 */
			template <typename O>
			inline bool operator!=(const Matrix<M, N, O>& rhs) const { 
					return !(*this == rhs); }

			/**
			 * 	@brief  Add two Matrices of equal dimensions
			 * 
			 * 	Navigate and add the two matrices index-by-index
			 * 	Result is stored as a type T
			 * 
			 * 	@param	const Matrix&		Right side of the addition
			 * 	@return	  Matrix<M, N, T>	result of addition
			 * 
			 * 	@version 0.1
			 */
			template <typename O>
			Matrix<M, N, T> operator+(const Matrix<M, N, O>& rhs) const;

			// ----- Inline Methods -----
			/// Get the width of the Matrix
			inline int getWidth() const { return N; }

			/// Get the number of rows in the matrix
			inline int getHeight() const { return M; }

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

		private:

	};
}

#include "matrix.cpp"
#endif