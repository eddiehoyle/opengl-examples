set(EXERCISE 27_skybox)
file(GLOB_RECURSE SOURCE_FILES "*.cc")
add_executable(${EXERCISE} ${SOURCE_FILES})
get_directory_property(COMMON_LIBRARY
        DIRECTORY ../common
        DEFINITION COMMON_LIBRARY)
target_compile_definitions(${EXERCISE} PRIVATE -DEXERCISE_NAME="${EXERCISE}")
target_link_libraries(${EXERCISE}
        ${OPENGL_LIBRARIES}
        ${GLEW_LIBRARIES}
        ${COMMON_LIBRARY}
        ${GLFW_LIBRARIES})
