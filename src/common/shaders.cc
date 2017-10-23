#include "io.hh"
#include "shaders.hh"

#include <vector>

namespace common {

GLint validateShader( GLuint id ) {

    GLint result = GL_FALSE;
    int log_length;

    // Check Vertex Shader
    glGetShaderiv( id, GL_COMPILE_STATUS, &result );
    glGetShaderiv( id, GL_INFO_LOG_LENGTH, &log_length );
    if ( log_length > 0 ) {
        std::vector< char > error( log_length + 1 );
        glGetShaderInfoLog( id, log_length, nullptr, &error[0] );
        printf( "%s\n", &error[0] );
    }
    return result;
}

GLint validateProgram( GLuint id ) {

    GLint result = GL_FALSE;
    int log_length;

    // Check the program
    glGetProgramiv( id, GL_LINK_STATUS, &result );
    glGetProgramiv( id, GL_INFO_LOG_LENGTH, &log_length );
    if ( log_length > 0 ) {
        std::vector< char > error( log_length + 1 );
        glGetProgramInfoLog( id, log_length, nullptr, &error[0] );
        printf( "%s\n", &error[0] );
    }
    return result;
}

GLint load_shader( const std::string& path, GLenum type ) {

    const std::string vertex_data = read_file( path );

    // Compile vertex shader
    GLuint id = glCreateShader( type );
    const char* source = vertex_data.c_str();
    glShaderSource( id, 1, &source, nullptr );
    glCompileShader( id );
    validateShader( id );
    return id;
}

GLuint create_program( GLint vertex, GLint fragment ) {

    // Link program
    GLuint program = glCreateProgram();
    glAttachShader( program, vertex );
    glAttachShader( program, fragment );
    glLinkProgram( program );
    validateProgram( program );

    // Tidy up
//    glDetachShader( program, vertex );
//    glDetachShader( program, fragment );
//    glDeleteShader( vertex );
//    glDeleteShader( fragment );

    return program;
}

GLuint create_shader( const std::string& vertex_path, const std::string& fragment_path ) {

    // Read data
    std::string vertex_data = read_file( vertex_path );
    std::string fragment_data = read_file( fragment_path );

    // Compile vertex shader
    GLuint vertex_id = glCreateShader( GL_VERTEX_SHADER );
    const char* vertex_source = vertex_data.c_str();
    glShaderSource( vertex_id, 1, &vertex_source, nullptr );
    glCompileShader( vertex_id );
    validateShader( vertex_id );

    // Compile fragment shader
    GLuint fragment_id = glCreateShader( GL_FRAGMENT_SHADER );
    const char* fragment_source = fragment_data.c_str();
    glShaderSource( fragment_id, 1, &fragment_source, nullptr );
    glCompileShader( fragment_id );
    validateShader( fragment_id );

    // Link program
    GLuint program_id = glCreateProgram();
    glAttachShader( program_id, vertex_id );
    glAttachShader( program_id, fragment_id );
    glLinkProgram( program_id );
    validateProgram( program_id );

    // Tidy up
    glDetachShader( program_id, vertex_id );
    glDetachShader( program_id, fragment_id );
    glDeleteShader( vertex_id );
    glDeleteShader( fragment_id );

    return program_id;
}

} // namespace common