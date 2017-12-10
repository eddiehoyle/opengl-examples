set(EXERCISE 18_player)
file(GLOB_RECURSE SOURCE_FILES "*.cc")
add_executable(${EXERCISE} ${SOURCE_FILES} bunny.cc bunny.hh)
get_directory_property(COMMON_LIBRARY
        DIRECTORY ../common
        DEFINITION COMMON_LIBRARY)
target_link_libraries(${EXERCISE}
        ${OPENGL_LIBRARIES}
        ${GLEW_LIBRARIES}
        ${GLFW_LIBRARIES}
        ${COMMON_LIBRARY})
