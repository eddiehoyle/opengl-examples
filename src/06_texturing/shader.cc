//
// Created by Eddie Hoyle on 23/10/17.
//

#include "shader.hh"
#include "../common/shaders.hh"

AbstractShader::AbstractShader( const std::string& vertex_path,
                                const std::string& fragment_path )
        : m_vertexShaderID( 0 ),
          m_fragmentShaderID( 0 ),
          m_programID( 0 ) {
    m_vertexShaderID = common::load_shader( vertex_path, GL_VERTEX_SHADER );
    m_fragmentShaderID = common::load_shader( fragment_path, GL_FRAGMENT_SHADER );
    m_programID = common::create_program( m_vertexShaderID, m_fragmentShaderID );
    bindAttributes();
}

void AbstractShader::bindAttribute( GLint attribute, const std::string& name ) {
    glBindAttribLocation( m_programID, attribute, name.c_str() );
}

void AbstractShader::start() {
    glUseProgram( m_programID );
}

void AbstractShader::stop() {
    glUseProgram( 0 );
}

void AbstractShader::cleanup() {

    glDetachShader( m_programID, m_vertexShaderID );
    glDetachShader( m_programID, m_fragmentShaderID );
    glDeleteShader( m_vertexShaderID );
    glDeleteShader( m_fragmentShaderID );
    glDeleteProgram( m_programID );
}

// ------------------------------------------------------------------------------------------ //

static const std::string kVertexPath = "/Users/eddiehoyle/Code/cpp/opengl-examples/src/05_colouring/shaders/vertex.glsl";
static const std::string kFragmentPath = "/Users/eddiehoyle/Code/cpp/opengl-examples/src/05_colouring/shaders/fragment.glsl";

StaticShader::StaticShader()
        : AbstractShader( kVertexPath, kFragmentPath ) {
}

void StaticShader::bindAttributes() {
    bindAttribute( 0 , "position" );
}

