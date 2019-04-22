cmake_minimum_required (VERSION 3.0.2)
set(PROJECT_NAME ricardo-graphics)

project (${PROJECT_NAME})

#Set the version number of this build
set (VERSION_MAJOR 1)
set (VERSION_MINOR 0) 

# Add source files
# GLOB_RECURSE goes through directories recursively
file(GLOB_RECURSE SOURCE_FILES
	${CMAKE_SOURCE_DIR}/src/*.cpp)

# Add header files
file(GLOB_RECURSE HEADER_FILES
	${CMAKE_SOURCE_DIR}/src/*.h)

# Add libraries
link_directories(${CMAKE_SOURCE_DIR}/lib)

# Define the executable
add_executable(${PROJECT_NAME} ${HEADER_FILES} ${SOURCE_FILES})

# Finding external dependencies
set (CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/")

#find_package(OpenGL REQUIRED)

find_package(GLM REQUIRED)
message(STATUS "GLM included at ${GLM_INCLUDE_DIR}")

find_package(GLEW REQUIRED)
message(STATUS "GLEW included at ${GLEW_INCLUDE_DIR}")

find_package(GLFW3 REQUIRED)
message(STATUS "GLFW included at ${GLFW3_INCLUDE_DIR}")

set(LIBS glfw3 opengl32 glew32 glew32s)

# Define include directory
include_directories(
	"${CMAKE_SOURCE_DIR}/src"
	"${CMAKE_SOURCE_DIR}/include")

target_link_libraries(${PROJECT_NAME} ${LIBS})





