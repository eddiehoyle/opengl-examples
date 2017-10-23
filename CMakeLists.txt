cmake_minimum_required(VERSION 3.8)
project(learning_opengl)

set(CMAKE_CXX_STANDARD 11)

# Find packages
find_package(OpenGL REQUIRED)
find_package(GLEW REQUIRED)
find_package(glm REQUIRED)

find_package(PkgConfig REQUIRED)
pkg_search_module(GLFW REQUIRED glfw3)

set(LRN_ROOT_DIR ${CMAKE_CURRENT_SOURCE_DIR})
set(LRN_EXTERNAL_DIR ${BTGFX_ROOT_DIR}/ext)

include_directories(
        ${GLFW_INCLUDE_DIRS}
        ${LRN_EXTERNAL_DIR}
        ${GLM_INCLUDE_DIRS}
        ${GLEW_INCLUDE_DIR}
)

add_subdirectory(src)
