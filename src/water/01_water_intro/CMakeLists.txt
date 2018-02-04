set(EXERCISE 01_water_intro)
file(GLOB_RECURSE SOURCE_FILES "*.cc")
add_executable(${EXERCISE} ${SOURCE_FILES} water.cc water.hh)
get_directory_property(COMMON_LIBRARY
        DIRECTORY ../../common
        DEFINITION COMMON_LIBRARY)
target_compile_definitions(${EXERCISE} PRIVATE -DEXERCISE_NAME="${EXERCISE}")
target_include_directories(${EXERCISE} PUBLIC ${OPENGL_EXAMPLES_SOURCE_DIR})
target_link_libraries(${EXERCISE}
        ${OPENGL_LIBRARIES}
        ${GLEW_LIBRARIES}
        ${COMMON_LIBRARY}
        ${GLFW_LIBRARIES})
