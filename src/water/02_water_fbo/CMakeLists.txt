set(EXERCISE 02_water_fbo)
file(GLOB_RECURSE SOURCE_FILES "*.cc")
add_executable(${EXERCISE} ${SOURCE_FILES} buffer.cc buffer.hh)
get_directory_property(COMMON_LIBRARY
        DIRECTORY ../../common
        DEFINITION COMMON_LIBRARY)
target_compile_definitions(${EXERCISE} PRIVATE -DEXERCISE_NAME="${EXERCISE}")
target_include_directories(${EXERCISE} PRIVATE ${OPENGL_EXAMPLES_SOURCE_DIR})
target_link_libraries(${EXERCISE}
        ${OPENGL_LIBRARIES}
        ${GLEW_LIBRARIES}
        ${COMMON_LIBRARY}
        ${GLFW_LIBRARIES})
