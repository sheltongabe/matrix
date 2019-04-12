##
#	@file		CMakeLists.txt
#	@brief	  matrix src CMakeFile
#
#	Builds the matrix library
#
#	@author		Gabriel Shelton		sheltongabe
#	@date		  08_04-2018
#	@version	0.5
#

cmake_minimum_required(VERSION 2.8)

project("${MATRIX_LIB_NAME}_src")

# Configure headers
set(HEADERS_DIR ${PROJECT_SOURCE_DIR}/../include)
include_directories(${HEADERS_DIR})

# Gather matrix library headers and move them to the root include file
set(DIR_NAME ${CMAKE_SOURCE_DIR}/include/${MATRIX_LIB_NAME})
file(MAKE_DIRECTORY ${DIR_NAME})
file(GLOB LIB_HEADERS ${HEADERS_DIR}/*.h ${HEADERS_DIR}/*.cpp)
file(COPY ${LIB_HEADERS} DESTINATION ${DIR_NAME})

# Set a list of sources for the library
set(LIB_SOURCES
	"matrix_factory.cpp"
)

# Compile the static library
add_library("${MATRIX_LIB_NAME}_static" STATIC
	${LIB_SOURCES}
)