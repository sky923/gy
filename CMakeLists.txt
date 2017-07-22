# cmake requirement
cmake_minimum_required(VERSION 3.0)

#project name
SET (PROJECT_NAME gy)
# version number
SET (PROJECT_VERSION_MAJOR 1)
SET (PROJECT_VERSION_MINOR 0)

#build type
SET(CMAKE_BUILD_TYPE Release)

# project information
project(${PROJECT_NAME} VERSION ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR})

# configurations
configure_file(
	"${PROJECT_NAME}/config/config.h.in"
	"${PROJECT_NAME}/config/config.h"
)

# setter
SET(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)
SET(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/lib)

# add sources and headers
file(
	GLOB_RECURSE SOURCE_FILES
	LIST_DIRECTORIES false
	RELATIVE "${CMAKE_CURRENT_SOURCE_DIR}"
	"${PROJECT_NAME}/*.h"
	"${PROJECT_NAME}/*.hpp"
	"${PROJECT_NAME}/*.c"
	"${PROJECT_NAME}/*.cpp"
	"${PROJECT_NAME}/*.m"
	"${PROJECT_NAME}/*.mm"
	"${PROJECT_NAME}/*.inl"
)

# add subdirectory
add_subdirectory(test)

# add for making libraries
add_library(${PROJECT_NAME} STATIC ${SOURCE_FILES})

# make a group in an IDE
foreach(CUR_FILE in items ${SOURCE_FILES})
	get_filename_component(CUR_FILE_PATH ${CUR_FILE} PATH)
	string(REPLACE "/" "\\" GROUP_PATH "${CUR_FILE_PATH}")
	source_group(${GROUP_PATH} FILES ${CUR_FILE})
endforeach()

# compiler features
target_compile_features(${PROJECT_NAME} PRIVATE cxx_range_for)

# include
target_include_directories(
	${PROJECT_NAME}
	PUBLIC
	# Headers used from source/build location:
	"$<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/${PROJECT_NAME}>"
	# Headers used from installed location:
	# "$<INSTALL_INTERFACE:${PROJECT_NAME}>"     
)
