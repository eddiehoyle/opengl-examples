#ifndef OPENGL_EXAMPLES_COMMON_IO_HH
#define OPENGL_EXAMPLES_COMMON_IO_HH

#include <iostream>
#include <vector>

#include <glm/glm.hpp>
#include <GL/glew.h>

namespace common {

/// Open a text file and return it's contents.
/// @param path A text file.
/// @returns The contents of the file.
std::string read_file( const std::string& path );

} // namespace common

#endif // OPENGL_EXAMPLES_COMMON_IO_HH
