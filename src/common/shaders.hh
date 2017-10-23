#ifndef LEARNING_OPENGL_SHADER_HH
#define LEARNING_OPENGL_SHADER_HH

#include <GL/glew.h>
#include <string>


namespace common {

/// Parse vertex and fragment shader files, create
/// shaders, link and return a shader program.
/// @param vertex_path A vertex shader file.
/// @param vertex_path A fragment shader file.
/// @returns A linked shader program.
GLuint create_shader( const std::string& vertex_path,
                      const std::string& fragment_path );

/// TODO
GLint load_shader( const std::string& path, GLenum type );

/// TODO
GLuint create_program( GLint vertex, GLint fragment );

}

#endif // LEARNING_OPENGL_SHADER_HH
