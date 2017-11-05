//
// Created by Eddie Hoyle on 23/10/17.
//

#ifndef LEARNING_OPENGL_11_SHADER_HH
#define LEARNING_OPENGL_11_SHADER_HH

#include <GL/glew.h>
#include <string>

#include <glm/glm.hpp>
#include <glm/ext.hpp>
#include "light.hh"

class StaticShader {

public:

    /// Constructor
    StaticShader();

    /// Destructor
    ~StaticShader();

    /// TODO
    GLint getUniformLocation( const std::string& name );

    /// Collect all the uniform locations in the shader
    void getUniformLocations();

    /// TODO
    void loadTransformationMatrix( const glm::mat4& mat );

    /// TODO
    void loadProjectionMatrix( const glm::mat4& mat );

    /// TODO
    void loadViewMatrix( const glm::mat4& mat );

    /// TODO
    void loadLight( const Light& light );

    /// Load a bool into a uniform
    void loadBoolean( GLint location, bool value );

    /// Load a float into a uniform
    void loadFloat( GLint location, GLfloat value );

    /// Load a vector 3 into a uniform
    void loadVector( GLint location, const glm::vec3& vec );

    /// Load a 4x4 matrix into a uniform
    void loadMatrix( GLint location, const glm::mat4& mat );

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

    // Uniform locations
    GLint m_transformationMatrix;
    GLint m_projectionMatrix;
    GLint m_viewMatrix;
    GLint m_lightPosition;
    GLint m_lightColour;
};

#endif //OPENGL_EXAMPLES_11_SHADER_HH
