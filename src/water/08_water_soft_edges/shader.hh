//
// Created by Eddie Hoyle on 23/10/17.
//

#ifndef LEARNING_OPENGL_17_SHADER_HH
#define LEARNING_OPENGL_17_SHADER_HH

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

    /// Clipping plane
    void loadClipPlane( const glm::vec4& plane  );

    /// Texture atlas rows
    void loadNumberOfRows( GLint numberOfRows  );

    /// Texture atlas offset
    void loadOffset( const glm::vec2& offset  );

    /// TODO
    void loadSkyColour( GLfloat r, GLfloat g, GLfloat b );

    /// TODO
    void loadShineVariables( GLfloat damper, GLfloat reflectivity );

    /// TODO
    void loadTransformationMatrix( const glm::mat4& mat );

    /// TODO
    void loadProjectionMatrix( const glm::mat4& mat );

    /// TODO
    virtual void loadViewMatrix( const glm::mat4& mat );

    /// TODO
    void loadLights( const std::vector< Light >& light );

    /// Load a bool into a uniform
    void loadBoolean( GLint location, bool value );

    /// Load a bool into a uniform
    void loadInt( GLint location, GLint value );

    /// Load a float into a uniform
    void loadFloat( GLint location, GLfloat value );

    /// Load a vector 2 into a uniform
    void loadVector( GLint location, const glm::vec2& vec );

    /// Load a vector 3 into a uniform
    void loadVector( GLint location, const glm::vec3& vec );

    /// Load a vector 4 into a uniform
    void loadVector( GLint location, const glm::vec4& vec );

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
    GLint m_shineDamper;
    GLint m_reflectivity;
    GLint m_skyColour;
    GLint m_numberOfRows;
    GLint m_offset;
    GLint m_plane;
    std::vector< GLint > m_lightPosition;
    std::vector< GLint > m_lightColour;
    std::vector< GLint > m_attenuation;
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

class GuiShader : public ShaderProgram {
public:
    GuiShader();
    virtual void init();
    virtual void getUniformLocations();
};

class SkyboxShader : public ShaderProgram {
public:
    SkyboxShader();
    virtual void init();
    virtual void getUniformLocations();
    virtual void loadViewMatrix( const glm::mat4& mat );
    void loadFogColour( float r, float g, float b );
    void loadBlendFactor( float blend );
    void connectTextureUnits();

protected:
    GLint m_fogColour;
    GLint m_cubeMap;
    GLint m_cubeMap2;
    GLint m_blendFactor;

    float m_rotation;
};


class WaterShader : public ShaderProgram {

public:
    WaterShader();
    virtual void init();
    virtual void getUniformLocations();
    virtual void loadViewMatrix( const glm::mat4& matrix );
    void loadModelMatrix( const glm::mat4& matrix );
    void connectTextureUnits();
    void loadCameraPosition( const glm::vec3& pos );
    void loadMoveFactor( float value );
    void loadLightColour( const glm::vec3& vec );
    void loadLightPosition( const glm::vec3& vec );

protected:

    // Model is same as transformation atm
    GLint m_modelMatrix;

    GLint m_reflectionTexture;
    GLint m_refractionTexture;
    GLint m_dudvMapTexture;
    GLint m_moveFactor;
    GLint m_cameraPosition;
    GLint m_normalMap;
    GLint m_lightPosition;
    GLint m_lightColour;
    GLint m_depthMap;
};

#endif //OPENGL_EXAMPLES_17_SHADER_HH
