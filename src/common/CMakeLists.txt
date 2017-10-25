set(COMMON_LIBRARY common)
include_directories(
        ${GLEW_INCLUDE_DIR}
        ${GLFW_INCLUDE_DIRS})
add_library(${COMMON_LIBRARY} SHARED
        io.cc)
target_link_libraries(${COMMON_LIBRARY}
        ${OPENGL_LIBRARIES}
        ${GLEW_LIBRARIES}
        ${GLFW_LIBRARIES})
