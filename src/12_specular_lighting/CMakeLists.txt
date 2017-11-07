set(EXERCISE 12_specular_lighting)
file(GLOB_RECURSE SOURCE_FILES "*.cc")
add_executable(${EXERCISE} ${SOURCE_FILES} OBJLoader.cc OBJLoader.hh light.cc light.hh)
get_directory_property(COMMON_LIBRARY
        DIRECTORY ../common
        DEFINITION COMMON_LIBRARY)
target_link_libraries(${EXERCISE}
        ${OPENGL_LIBRARIES}
        ${GLEW_LIBRARIES}
        ${GLFW_LIBRARIES}
        ${COMMON_LIBRARY})
