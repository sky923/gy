# cmake requirement
cmake_minimum_required(VERSION 3.0)

#project name
SET (PROJECT_NAME gy_test)
# version number
SET (PROJECT_VERSION_MAJOR 1)
SET (PROJECT_VERSION_MINOR 0)

#build type
SET(CMAKE_BUILD_TYPE Release)

# project information
project(${PROJECT_NAME} VERSION ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR})

# setter
SET(EXECUTABLE_OUTPUT_PATH ../bin)

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

# add for making executable
add_executable(${PROJECT_NAME} ${SOURCE_FILES})

# set start-up project
set_property(DIRECTORY PROPERTY VS_STARTUP_PROJECT ${PROJECT_NAME})

# make a group in an IDE
foreach(CUR_FILE in items ${SOURCE_FILES})
	get_filename_component(CUR_FILE_PATH ${CUR_FILE} PATH)
	string(REPLACE "/" "\\" GROUP_PATH "${CUR_FILE_PATH}")
	source_group(${GROUP_PATH} FILES ${CUR_FILE})
endforeach()

# compiler features
target_compile_features(${PROJECT_NAME} PRIVATE cxx_range_for)

#set(
#	RESOURCE_FILES
#	resourcefile.txt
#	appresourcedir/appres.txt
#)

if (APPLE)
	find_library(CARBON_LIB Carbon)
	find_library(IOKIT_LIB IOKit)
	find_library(FORCEFEEDBACK_LIB ForceFeedback)
	find_library(COCOA_LIB Cocoa)
	find_library(AUDIOUNIT_LIB AudioUnit)
	find_library(COREAUDIO_LIB CoreAudio)
	find_library(OPENGL_LIB OpenGL)
	find_library(COREFOUNDATION_LIB CoreFoundation)

	set(FRAMEWORKS
		${CARBON_LIB}
		${IOKIT_LIB}
		${FORCEFEEDBACK_LIB}
		${COCOA_LIB}
		${AUDIOUNIT_LIB}
		${COREAUDIO_LIB}
		${OPENGL_LIB}
		${COREFOUNDATION_LIB}
	)

# https://cmake.org/cmake/help/v3.5/prop_tgt/RESOURCE.html
	set_target_properties(
		${PROJECT_NAME}
		PROPERTIES
		MACOSX_BUNDLE TRUE
		MACOSX_FRAMEWORK_IDENTIFIER "org.gy.${PROJECT_NAME}"
		RESOURCE ""
#""${RESOURCE_FILES}"
	)

#	set_target_properties(
#	    ${PROJECT_NAME}
#	    PROPERTIES
#	    MACOSX_BUNDLE_INFO_PLIST
#	    "${PROJECT_NAME}/info.plist.in"
#	)
endif()

# link libraries
target_link_libraries(${PROJECT_NAME} LINK_PUBLIC ${FRAMEWORKS} gy)

# include
target_include_directories(
	${PROJECT_NAME}
	PUBLIC
	# Headers used from source/build location:
	"$<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/..>"
	"$<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/${PROJECT_NAME}>"
	# Headers used from installed location:
	# "$<INSTALL_INTERFACE:${PROJECT_NAME}>"     
)


# https://stackoverflow.com/questions/14148374/how-do-you-set-properties-in-a-vcproj-file-with-cmake
if (MSVC)
	SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /UMBCS /D_UNICODE /DUNICODE /utf-8")
	SET(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} /MT")
	SET(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} /MTd")
endif()

