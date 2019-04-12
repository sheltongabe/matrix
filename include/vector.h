/**
 *  @file		vector.h
 *  @brief	  Define the base definition of a Vector (a list of things, ...)	
 *  
 * 	Only requires the base operations such as + by another vector, * a scalar, and indexing into
 *  
 *  @author		Gabriel Shelton	sheltongabe
 *  @date		  08-11-2018
 *  @version	0.1
 */

#ifndef VECTOR_H
#define VECTOR_H



namespace matrix {

	/**
	 * 	@class		Vector
	 * 	@brief		Provide the base definition of a vector that contains type T and has the basic operations
	 * 
	 * 	Basic operations will be pure virtual
	 * 	Vector + Vector, Vector * scalar<=>, []
	 * 
	 */
	template <typename T>
	class Vector {
		public:
			/**
			 * 	@brief	Default Constructor
			 * 
			 * 	Details
			 * 
			 * 	@version	0.1
			 */
			Vector() { }

			// ----- Operator Overloading

			/**
			 * 	@brief	Pure virtual definition for l-value index operator
			 * 
			 * 	Overload to provide implementation in sub-classes of Vector
			 * 
			 * 	@param	unsigned int		index
			 * 	@return	  T&		 			    Item at index l-value
			 * 	@throws   std::out_of_range
			 * 
			 * 	@version	0.1
			 */
			virtual T& operator [] (unsigned int index) = 0;

			/**
			 * 	@brief	Pure virtual definition for r-value index operator
			 * 
			 * 	Overload to provide implementation in sub-classes of Vector
			 * 
			 * 	@param	unsigned int		index
			 * 	@return	  const T&		 	    Item at index r-value
			 * 	@throws   std::out_of_range
			 * 
			 * 	@version	0.1
			 */
			virtual const T& operator [] (unsigned int index) const = 0;

			/**
			 * 	@brief	Destructor
			 * 
			 * 	Details
			 * 
			 * 	@version	0.0
			 */
			~Vector() { }

		private:

	};
}

#endif