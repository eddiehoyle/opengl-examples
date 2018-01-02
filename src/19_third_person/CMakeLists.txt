set(EXERCISE 19_third_person)
file(GLOB_RECURSE SOURCE_FILES "*.cc")
add_executable(${EXERCISE} ${SOURCE_FILES})
get_directory_property(COMMON_LIBRARY
        DIRECTORY ../common
        DEFINITION COMMON_LIBRARY)
target_link_libraries(${EXERCISE}
        ${OPENGL_LIBRARIES}
        ${GLEW_LIBRARIES}
        ${COMMON_LIBRARY}
        ${GLFW_LIBRARIES})
