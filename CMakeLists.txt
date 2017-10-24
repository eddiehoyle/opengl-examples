cmake_minimum_required(VERSION 3.8)
project(opengl_examples)

set(CMAKE_CXX_STANDARD 11)
set(OPENGL_EXAMPLES_ROOT_DIR ${CMAKE_SOURCE_DIR})
set(OPENGL_EXAMPLES_EXTERNAL_DIR ${OPENGL_EXAMPLES_ROOT_DIR}/ext)
set(CMAKE_MODULE_PATH ${OPENGL_EXAMPLES_ROOT_DIR}/cmake)

# Find packages
find_package(OpenGL REQUIRED)
find_package(GLEW REQUIRED)
find_package(GLM REQUIRED)

find_package(PkgConfig REQUIRED)
find_package(GLFW3 REQUIRED)

include_directories(
        ${OPENGL_EXAMPLES_EXTERNAL_DIR}
        ${GLFW_INCLUDE_DIRS}
        ${LRN_EXTERNAL_DIR}
        ${GLM_INCLUDE_DIRS}
        ${GLEW_INCLUDE_DIR}
)

add_subdirectory(src)
