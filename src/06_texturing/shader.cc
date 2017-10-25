//
// Created by Eddie Hoyle on 23/10/17.
//

#include <iostream>
#include <vector>
#include "shader.hh"
#include "../common/io.hh"

StaticShader::StaticShader()
        : m_vertexShaderID( 0 ),
          m_fragmentShaderID( 0 ),
          m_programID( 0 ) {

    // Read in vertex shader
    const std::string vertex_path = "/Users/eddiehoyle/Code/cpp/opengl-examples/src/06_texturing/shaders/vertex.glsl";
    const std::string vertex_source = common::read_file( vertex_path );
    m_vertexShaderID = compile( vertex_source, GL_VERTEX_SHADER );

    // Read in fragment shader
    const std::string fragment_path = "/Users/eddiehoyle/Code/cpp/opengl-examples/src/06_texturing/shaders/fragment.glsl";
    const std::string fragment_source = common::read_file( fragment_path );
    m_fragmentShaderID = compile( fragment_source, GL_FRAGMENT_SHADER );

    // Create program
    m_programID = glCreateProgram();
    glAttachShader( m_programID, m_vertexShaderID );
    glAttachShader( m_programID, m_fragmentShaderID );

    // Bind attributes before linking to ensure order
    bindAttribute( 0, "position" );
    bindAttribute( 1, "textureCoords" );

    // Link program
    glLinkProgram( m_programID );
    validateProgram( m_programID );
}

StaticShader::~StaticShader() {
    cleanup();
}

GLuint StaticShader::compile( const std::string& shader, GLenum type ) {

    // Compile vertex shader
    GLuint id = glCreateShader( type );
    const char* source = shader.c_str();
    glShaderSource( id, 1, &source, nullptr );
    glCompileShader( id );
    validateShader( id );
    return id;
}

bool StaticShader::validateShader( GLuint shader_id ) {

    GLint result = GL_FALSE;
    int log_length;

    // Check Vertex Shader
    glGetShaderiv( shader_id, GL_COMPILE_STATUS, &result );
    glGetShaderiv( shader_id, GL_INFO_LOG_LENGTH, &log_length );
    if ( log_length > 0 ) {
        std::vector< char > error( log_length + 1 );
        glGetShaderInfoLog( shader_id, log_length, nullptr, &error[0] );
        printf( "%s : %s\n", __func__, &error[0] );
    }
    return static_cast< bool >( result );
}

bool StaticShader::validateProgram( GLuint program_id ) {

    GLint result = GL_FALSE;
    int log_length;

    // Check the program
    glGetProgramiv( program_id, GL_LINK_STATUS, &result );
    glGetProgramiv( program_id, GL_INFO_LOG_LENGTH, &log_length );
    if ( log_length > 0 ) {
        std::vector< char > error( log_length + 1 );
        glGetProgramInfoLog( program_id, log_length, nullptr, &error[0] );
        printf( "%s : %s\n", __func__, &error[0] );
    }
    return static_cast< bool >( result );
}

void StaticShader::bindAttribute( GLint attribute, const std::string& name ) {
    glBindAttribLocation( m_programID, attribute, name.c_str() );
}

void StaticShader::start() {
    glUseProgram( m_programID );
}

void StaticShader::stop() {
    glUseProgram( 0 );
}

void StaticShader::cleanup() {

    glDetachShader( m_programID, m_vertexShaderID );
    glDetachShader( m_programID, m_fragmentShaderID );
    glDeleteShader( m_vertexShaderID );
    glDeleteShader( m_fragmentShaderID );
    glDeleteProgram( m_programID );
}

