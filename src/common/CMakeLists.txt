set(COMMON_LIBRARY common)
file(GLOB_RECURSE SOURCE_FILES "*.cc")
add_library(${COMMON_LIBRARY} SHARED ${SOURCE_FILES} obj/parser.cc obj/parser.hh input/input.cc input/input.hh event/observer.cc event/observer.hh input/defs.hh command/command.cc command/command.hh components/component.cc components/component.hh controllers.cc controllers.hh scene/scene.cc scene/scene.hh controllers/controller.cc controllers/controller.hh scene/defs.hh device/device.cc device/device.hh transform.hh)
target_compile_definitions(${COMMON_LIBRARY} PRIVATE -DPROJECT_ROOT_DIR="${OPENGL_EXAMPLES_ROOT_DIR}")
target_link_libraries(${COMMON_LIBRARY}
        ${OPENGL_LIBRARIES}
        ${GLEW_LIBRARIES}
        ${GLFW_LIBRARIES})
