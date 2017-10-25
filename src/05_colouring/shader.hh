//
// Created by Eddie Hoyle on 23/10/17.
//

#ifndef LEARNING_OPENGL_05_COLOURING_SHADER_HH
#define LEARNING_OPENGL_05_COLOURING_SHADER_HH

#include <GL/glew.h>
#include <string>

class StaticShader {

public:

    /// Constructor
    StaticShader();

    /// Destructor
    ~StaticShader();

    /// Bind this shader
    void start();

    /// Unbind this shader
    void stop();

    /// Delete this shader
    void cleanup();

private:
    void bindAttribute( GLint attribute, const std::string& name );
    bool validateShader( GLuint shader );
    bool validateProgram( GLuint program );
    GLuint compile( const std::string& shader, GLenum type );

    GLuint m_programID;
    GLuint m_vertexShaderID;
    GLuint m_fragmentShaderID;
};

#endif //LEARNING_OPENGL_05_COLOURING_SHADER_HH
