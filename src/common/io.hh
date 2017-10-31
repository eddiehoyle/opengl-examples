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

bool loadOBJ( const char * path,
              std::vector<glm::vec3>& out_vertices,
              std::vector<glm::vec2>& out_uvs,
              std::vector<glm::vec3>& out_normals,
              std::vector< GLuint >& out_indices );

bool read_obj( const std::string& path,
               std::vector< GLfloat >& out_vertices,
               std::vector< GLfloat >& out_uvs,
               std::vector< GLfloat >& out_normals,
               std::vector< GLuint >& out_indices );

} // namespace common

#endif // OPENGL_EXAMPLES_COMMON_IO_HH
