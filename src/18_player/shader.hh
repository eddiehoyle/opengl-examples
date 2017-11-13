//
// Created by Eddie Hoyle on 23/10/17.
//

#ifndef LEARNING_OPENGL_18_SHADER_HH
#define LEARNING_OPENGL_18_SHADER_HH

#include <GL/glew.h>
#include <string>

#include <glm/glm.hpp>
#include <glm/ext.hpp>
#include "light.hh"

class ShaderProgram {

public:

    /// Constructor
    ShaderProgram();

    /// Destructor
    ~ShaderProgram();

    /// Compiles shader
    virtual void init() {}

    /// Collect all the uniform locations in the shader
    virtual void getUniformLocations() {}

    /// TODO
    GLint getUniformLocation( const std::string& name );

    /// TODO
    void loadSkyColour( GLfloat r, GLfloat g, GLfloat b );

    /// TODO
    void loadShineVariables( GLfloat damper, GLfloat reflectivity );

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

    /// Load a bool into a uniform
    void loadInt( GLint location, GLint value );

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

    /// TODO
    GLuint getProgram() const;

protected:

    void bindAttribute( GLint attribute, const std::string& name );

    bool validateShader( GLuint shader );

    bool validateProgram( GLuint program );

    GLuint compile( const std::string& shader, GLenum type );

protected:
    GLuint m_programID;
    GLuint m_vertexShaderID;
    GLuint m_fragmentShaderID;

    // Uniform locations
    GLint m_transformationMatrix;
    GLint m_projectionMatrix;
    GLint m_viewMatrix;
    GLint m_lightPosition;
    GLint m_lightColour;
    GLint m_shineDamper;
    GLint m_reflectivity;
    GLint m_skyColour;

};

class StaticShader : public ShaderProgram {
public:
    StaticShader();
    virtual void init();
    virtual void getUniformLocations();

    void loadFakeLighting( bool state );

protected:
    GLint m_useFakeLighting;
};

class TerrainShader : public ShaderProgram {
public:
    TerrainShader();
    virtual void init();
    virtual void getUniformLocations();
    void connectTextureUnits();

protected:
    GLint m_backgroundTexture;
    GLint m_rTexture;
    GLint m_gTexture;
    GLint m_bTexture;
    GLint m_blendMapTexture;
};

#endif //OPENGL_EXAMPLES_18_SHADER_HH
