##
#	@file	  CMakeLists.txt
#	@brief	Matrix test CMakeFile
#
#	Builds the test executable, and adds the tests 
#
#	@author		Gabriel Shelton		sheltongabe
#	@date		  08-04-2018
#	@version	0.5
#

cmake_minimum_required(VERSION 2.8)

project("{$MATRIX_LIB_NAME}_test")

# Configure executable settings
set(CONSTRUCTOR_EXE_NAME "${MATRIX_LIB_NAME}_constructor_test")
set(OPERATOR_EXE_NAME "${MATRIX_LIB_NAME}_operator_test")

# Configure headers
set(HEADERS_DIR ${PROJECT_SOURCE_DIR}/../include)
set(JSON_HEADERS_DIR ${CMAKE_SOURCE_DIR}/include/${JSON_LIB_NAME})
set(MATRIX_HEADERS_DIR ${CMAKE_SOURCE_DIR}/include/${MATRIX_LIB_NAME})

# Configure Test settings
set(NUM_TESTS 100)
set(TEST_OUTPUT_DIR ${PROJECT_SOURCE_DIR}/../results)
file(REMOVE ${TEST_OUTPUT_DIR})
file(MAKE_DIRECTORY ${TEST_OUTPUT_DIR})

# Include neccassary headers from the include file, and json include
include_directories(${HEADERS_DIR} ${CMAKE_SOURCE_DIR}/include)

# ----- Add ${CONSTRUCTOR_EXE_NAME} executable -----
add_executable(${CONSTRUCTOR_EXE_NAME}
	test_constructor.cpp
)
# Link the executable with the json, and matrix library
target_link_libraries(${CONSTRUCTOR_EXE_NAME} "${JSON_LIB_NAME}_static")
target_link_libraries(${CONSTRUCTOR_EXE_NAME} "${MATRIX_LIB_NAME}_static")
# Add tests
foreach(iteration RANGE 1 ${NUM_TESTS})
	add_test(
		NAME "${MATRIX_LIB_NAME}_static_constructor_test_${iteration}"
		COMMAND ${CONSTRUCTOR_EXE_NAME} ${iteration}
		WORKING_DIRECTORY ${TEST_OUTPUT_DIR}
	)
endforeach(iteration RANGE ${NUM_TESTS})

# ----- Add ${OPERATOR_EXE_NAME} executable -----
add_executable(${OPERATOR_EXE_NAME}
	test_operators.cpp
)
# Link the executable with the json, and matrix library
target_link_libraries(${OPERATOR_EXE_NAME} "${JSON_LIB_NAME}_static")
target_link_libraries(${OPERATOR_EXE_NAME} "${MATRIX_LIB_NAME}_static")
# Add tests
foreach(iteration RANGE 1 ${NUM_TESTS})
	add_test(
		NAME "${MATRIX_LIB_NAME}_static_operator_test_${iteration}"
		COMMAND ${OPERATOR_EXE_NAME} ${iteration}
		WORKING_DIRECTORY ${TEST_OUTPUT_DIR}
	)
endforeach(iteration RANGE ${NUM_TESTS})