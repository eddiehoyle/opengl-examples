set(COMMON_LIBRARY common)
set(CMAKE_VERBOSE_MAKEFILE ON)
file(GLOB_RECURSE SOURCE_FILES "*.cc")
add_library(${COMMON_LIBRARY} SHARED ${SOURCE_FILES} logging.cc logging.hh)
target_compile_definitions(${COMMON_LIBRARY} PRIVATE -DPROJECT_ROOT_DIR="${OPENGL_EXAMPLES_ROOT_DIR}")
target_link_libraries(${COMMON_LIBRARY}
        ${OPENGL_LIBRARIES}
        ${GLEW_LIBRARIES}
        ${GLFW_LIBRARIES})

