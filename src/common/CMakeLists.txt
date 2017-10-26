set(COMMON_LIBRARY common)
add_library(${COMMON_LIBRARY} SHARED
        io.cc
        resources.cc)
target_compile_definitions(${COMMON_LIBRARY} PRIVATE -DPROJECT_ROOT_DIR="${OPENGL_EXAMPLES_ROOT_DIR}")
target_link_libraries(${COMMON_LIBRARY}
        ${OPENGL_LIBRARIES}
        ${GLEW_LIBRARIES}
        ${GLFW_LIBRARIES})
