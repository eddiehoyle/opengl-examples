//
// Created by Eddie Hoyle on 23/10/17.
//

#include <iostream>
#include <vector>

#include "shader.hh"
#include "../common/io.hh"
#include "../common/resources.hh"

StaticShader::StaticShader()
        : m_vertexShaderID( 0 ),
          m_fragmentShaderID( 0 ),
          m_programID( 0 ) {

    // File status result
    bool shader_file_exists;

    // Read in vertex shader
    const std::string vertex_path = common::getResource( "shaders/13_optimising/vertex.glsl", shader_file_exists );
    const std::string vertex_source = common::read_file( vertex_path );
    m_vertexShaderID = compile( vertex_source, GL_VERTEX_SHADER );

    // Read in fragment shader
    const std::string fragment_path = common::getResource( "shaders/13_optimising/fragment.glsl", shader_file_exists );
    const std::string fragment_source = common::read_file( fragment_path );
    m_fragmentShaderID = compile( fragment_source, GL_FRAGMENT_SHADER );

    // Create program
    m_programID = glCreateProgram();
    glAttachShader( m_programID, m_vertexShaderID );
    glAttachShader( m_programID, m_fragmentShaderID );

    // Bind attributes before linking to ensure order
    bindAttribute( 0, "position" );
    bindAttribute( 1, "textureCoords" );
    bindAttribute( 2, "normal" );

    // Link program
    glLinkProgram( m_programID );
    validateProgram( m_programID );

    // Must happen after program is linked
    getUniformLocations();
}

StaticShader::~StaticShader() {
    cleanup();
}

GLint StaticShader::getUniformLocation( const std::string& name ) {
    return glGetUniformLocation( m_programID, name.c_str() );
}

void StaticShader::getUniformLocations() {
    m_transformationMatrix = getUniformLocation( "transformationMatrix" );
    m_projectionMatrix = getUniformLocation( "projectionMatrix" );
    m_viewMatrix = getUniformLocation( "viewMatrix" );
    m_lightPosition = getUniformLocation( "lightPosition" );
    m_lightColour = getUniformLocation( "lightColour" );
    m_shineDamper = getUniformLocation( "shineDamper" );
    m_reflectivity = getUniformLocation( "reflectivity" );
}

void StaticShader::loadShineVariables( GLfloat damper, GLfloat reflectivity ) {
    loadFloat( m_shineDamper, damper );
    loadFloat( m_reflectivity, reflectivity );
}

void StaticShader::loadTransformationMatrix( const glm::mat4& mat ) {
    loadMatrix( m_transformationMatrix, mat );
}

void StaticShader::loadProjectionMatrix( const glm::mat4& mat ) {
    loadMatrix( m_projectionMatrix, mat );
}

void StaticShader::loadViewMatrix( const glm::mat4& mat ) {
    loadMatrix( m_viewMatrix, mat );
}

void StaticShader::loadLight( const Light& light ) {
    loadVector( m_lightPosition, light.getPosition() );
    loadVector( m_lightColour, light.getColour() );
}

void StaticShader::loadBoolean( GLint location, bool value ) {
    glUniform1f( location, value ? 1.0f : 0.0f );
}

void StaticShader::loadFloat( GLint location, GLfloat value ) {
    glUniform1f( location, value );
}

void StaticShader::loadVector( GLint location, const glm::vec3& vec ) {
    glUniform3fv( location, 1, glm::value_ptr( vec ) );
}

void StaticShader::loadMatrix( GLint location, const glm::mat4& mat ) {
    bool transpose = false;
    glUniformMatrix4fv( location, 1, transpose, glm::value_ptr( mat ) );
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

