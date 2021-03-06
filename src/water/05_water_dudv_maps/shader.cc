#include <iostream>
#include <vector>
#include <sstream>

#include "shader.hh"
#include <common/io.hh>
#include <common/resources.hh>
#include <common/display.hh>

static const int MAX_LIGHTS = 4;

ShaderProgram::ShaderProgram()
        : m_vertexShaderID( 0 ),
          m_fragmentShaderID( 0 ),
          m_programID( 0 ),
          m_lightPosition( MAX_LIGHTS ),
          m_lightColour( MAX_LIGHTS ),
          m_attenuation( MAX_LIGHTS ) {
}

ShaderProgram::~ShaderProgram() {
    cleanup();
}

GLuint ShaderProgram::getProgram() const {
    return m_programID;
}

GLint ShaderProgram::getUniformLocation( const std::string& name ) {
    return glGetUniformLocation( m_programID, name.c_str() );
}

void ShaderProgram::loadClipPlane( const glm::vec4& plane  ) {
    loadVector( m_plane, plane );
}

void ShaderProgram::loadNumberOfRows( GLint numberOfRows  ) {
    loadFloat( m_numberOfRows, numberOfRows );
}

void ShaderProgram::loadOffset( const glm::vec2& offset  ) {
    loadVector( m_offset, offset );
}

void ShaderProgram::loadSkyColour( GLfloat r, GLfloat g, GLfloat b ) {
    loadVector( m_skyColour, glm::vec3( r, g, b ) );
}

void ShaderProgram::loadShineVariables( GLfloat damper, GLfloat reflectivity ) {
    loadFloat( m_shineDamper, damper );
    loadFloat( m_reflectivity, reflectivity );
}

void ShaderProgram::loadTransformationMatrix( const glm::mat4& mat ) {
    loadMatrix( m_transformationMatrix, mat );
}

void ShaderProgram::loadProjectionMatrix( const glm::mat4& mat ) {
    loadMatrix( m_projectionMatrix, mat );
}

void ShaderProgram::loadViewMatrix( const glm::mat4& mat ) {
    loadMatrix( m_viewMatrix, mat );
}

void ShaderProgram::loadLights( const std::vector< Light >& lights ) {
    for ( int i = 0; i < MAX_LIGHTS; ++i ) {
        if ( i < lights.size() ) {
            loadVector( m_lightPosition[i], lights[i].getPosition() );
            loadVector( m_lightColour[i], lights[i].getColour() );
            loadVector( m_attenuation[i], lights[i].getAttenuation() );
        } else {
            loadVector( m_lightPosition[i], glm::vec3( 0, 0, 0 ) );
            loadVector( m_lightColour[i], glm::vec3( 0, 0, 0 ) );
            loadVector( m_attenuation[i], glm::vec3( 1, 0, 0 ) );
        }
    }
}

void ShaderProgram::loadBoolean( GLint location, bool value ) {
    glUniform1f( location, value ? 1.0f : 0.0f );
}

void ShaderProgram::loadInt( GLint location, GLint value ) {
    glUniform1i( location, value );
}

void ShaderProgram::loadFloat( GLint location, GLfloat value ) {
    glUniform1f( location, value );
}

void ShaderProgram::loadVector( GLint location, const glm::vec2& vec ) {
    glUniform2fv( location, 1, glm::value_ptr( vec ) );
}

void ShaderProgram::loadVector( GLint location, const glm::vec3& vec ) {
    glUniform3fv( location, 1, glm::value_ptr( vec ) );
}

void ShaderProgram::loadVector( GLint location, const glm::vec4& vec ) {
    glUniform4fv( location, 1, glm::value_ptr( vec ) );
}

void ShaderProgram::loadMatrix( GLint location, const glm::mat4& mat ) {
    bool transpose = false;
    glUniformMatrix4fv( location, 1, transpose, glm::value_ptr( mat ) );
}

GLuint ShaderProgram::compile( const std::string& shader, GLenum type ) {

    // Compile vertex shader
    GLuint id = glCreateShader( type );
    const char *source = shader.c_str();
    glShaderSource( id, 1, &source, nullptr );
    glCompileShader( id );
    validateShader( id );
    return id;
}

bool ShaderProgram::validateShader( GLuint shader_id ) {

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

bool ShaderProgram::validateProgram( GLuint program_id ) {

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

void ShaderProgram::bindAttribute( GLint attribute, const std::string& name ) {
    glBindAttribLocation( m_programID, attribute, name.c_str() );
}

void ShaderProgram::start() {
    glUseProgram( m_programID );
}

void ShaderProgram::stop() {
    glUseProgram( 0 );
}

void ShaderProgram::cleanup() {

    glDetachShader( m_programID, m_vertexShaderID );
    glDetachShader( m_programID, m_fragmentShaderID );
    glDeleteShader( m_vertexShaderID );
    glDeleteShader( m_fragmentShaderID );
    glDeleteProgram( m_programID );
}

// ---------------------------------------------------------------------------------

StaticShader::StaticShader() : ShaderProgram() {
}

void StaticShader::init() {

    // File status result
    bool shader_file_exists;

    // Read in vertex shader
    std::string vertex_resource_path;
    vertex_resource_path += "shaders/water/";
    vertex_resource_path += EXERCISE_NAME;
    vertex_resource_path += "/staticVertex.glsl";
    const std::string vertex_path = common::getResource( vertex_resource_path, shader_file_exists );
    const std::string vertex_source = common::read_file( vertex_path );
    m_vertexShaderID = compile( vertex_source, GL_VERTEX_SHADER );

    // Read in fragment shader
    std::string fragment_resource_path;
    fragment_resource_path += "shaders/water/";
    fragment_resource_path += EXERCISE_NAME;
    fragment_resource_path += "/staticFragment.glsl";
    const std::string fragment_path = common::getResource( fragment_resource_path, shader_file_exists );
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

void StaticShader::loadFakeLighting( bool state ) {
    loadBoolean( m_useFakeLighting, state );
}

void StaticShader::getUniformLocations() {
    m_transformationMatrix = getUniformLocation( "transformationMatrix" );
    m_projectionMatrix = getUniformLocation( "projectionMatrix" );
    m_viewMatrix = getUniformLocation( "viewMatrix" );
    m_shineDamper = getUniformLocation( "shineDamper" );
    m_reflectivity = getUniformLocation( "reflectivity" );
    m_useFakeLighting = getUniformLocation( "useFakeLighting" );
    m_skyColour = getUniformLocation( "skyColour" );
    m_numberOfRows = getUniformLocation( "numberOfRows" );
    m_offset = getUniformLocation( "offset" );
    m_plane = getUniformLocation( "plane" );

    for ( int i = 0; i < MAX_LIGHTS; ++i ) {

        std::stringstream positionStream;
        positionStream << "lightPosition[";
        positionStream << i;
        positionStream << "]";
        m_lightPosition[i] = getUniformLocation( positionStream.str() );

        std::stringstream colourStream;
        colourStream << "lightColour[";
        colourStream << i;
        colourStream << "]";
        m_lightColour[i] = getUniformLocation( colourStream.str() );

        std::stringstream attenuationStream;
        attenuationStream << "attenuation[";
        attenuationStream << i;
        attenuationStream << "]";
        m_attenuation[i] = getUniformLocation( attenuationStream.str() );
    }
}

// ------------------------------------------------------------------

TerrainShader::TerrainShader() : ShaderProgram() {
}

void TerrainShader::init() {

    // File status result
    bool shader_file_exists;

    // Read in vertex shader
    std::string vertex_resource_path;
    vertex_resource_path += "shaders/water/";
    vertex_resource_path += EXERCISE_NAME;
    vertex_resource_path += "/terrainVertex.glsl";
    const std::string vertex_path = common::getResource( vertex_resource_path,
                                                         shader_file_exists );
    const std::string vertex_source = common::read_file( vertex_path );
    m_vertexShaderID = compile( vertex_source, GL_VERTEX_SHADER );
    assert( shader_file_exists );

    // Read in fragment shader
    std::string fragment_resource_path;
    fragment_resource_path += "shaders/water/";
    fragment_resource_path += EXERCISE_NAME;
    fragment_resource_path += "/terrainFragment.glsl";
    const std::string fragment_path = common::getResource( fragment_resource_path,
                                                           shader_file_exists );
    const std::string fragment_source = common::read_file( fragment_path );
    m_fragmentShaderID = compile( fragment_source, GL_FRAGMENT_SHADER );
    assert( shader_file_exists );

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

void TerrainShader::connectTextureUnits() {
    loadInt( m_backgroundTexture, 0 );
    loadInt( m_rTexture, 1 );
    loadInt( m_gTexture, 2 );
    loadInt( m_bTexture, 3 );
    loadInt( m_blendMapTexture, 4 );
}

void TerrainShader::getUniformLocations() {
    m_transformationMatrix = getUniformLocation( "transformationMatrix" );
    m_projectionMatrix = getUniformLocation( "projectionMatrix" );
    m_viewMatrix = getUniformLocation( "viewMatrix" );
    m_shineDamper = getUniformLocation( "shineDamper" );
    m_reflectivity = getUniformLocation( "reflectivity" );
    m_skyColour = getUniformLocation( "skyColour" );
    m_plane = getUniformLocation( "plane" );

    // Custom
    m_backgroundTexture = getUniformLocation( "backgroundTexture" );
    m_rTexture = getUniformLocation( "rTexture" );
    m_gTexture = getUniformLocation( "gTexture" );
    m_bTexture = getUniformLocation( "bTexture" );
    m_blendMapTexture = getUniformLocation( "blendMapTexture" );

    for ( int i = 0; i < MAX_LIGHTS; ++i ) {

        std::stringstream positionStream;
        positionStream << "lightPosition[";
        positionStream << i;
        positionStream << "]";
        m_lightPosition[i] = getUniformLocation( positionStream.str() );

        std::stringstream colourStream;
        colourStream << "lightColour[";
        colourStream << i;
        colourStream << "]";
        m_lightColour[i] = getUniformLocation( colourStream.str() );

        std::stringstream attenuationStream;
        attenuationStream << "attenuation[";
        attenuationStream << i;
        attenuationStream << "]";
        m_attenuation[i] = getUniformLocation( attenuationStream.str() );
    }
}

// ------------------------------------------------------------------

GuiShader::GuiShader() : ShaderProgram() {
}

void GuiShader::init() {

    // File status result
    bool shader_file_exists;

    // Read in vertex shader
    std::string vertex_resource_path;
    vertex_resource_path += "shaders/water/";
    vertex_resource_path += EXERCISE_NAME;
    vertex_resource_path += "/guiVertex.glsl";
    const std::string vertex_path = common::getResource( vertex_resource_path, shader_file_exists );
    const std::string vertex_source = common::read_file( vertex_path );
    m_vertexShaderID = compile( vertex_source, GL_VERTEX_SHADER );

    // Read in fragment shader
    std::string fragment_resource_path;
    fragment_resource_path += "shaders/water/";
    fragment_resource_path += EXERCISE_NAME;
    fragment_resource_path += "/guiFragment.glsl";
    const std::string fragment_path = common::getResource( fragment_resource_path, shader_file_exists );
    const std::string fragment_source = common::read_file( fragment_path );
    m_fragmentShaderID = compile( fragment_source, GL_FRAGMENT_SHADER );

    // Create program
    m_programID = glCreateProgram();
    glAttachShader( m_programID, m_vertexShaderID );
    glAttachShader( m_programID, m_fragmentShaderID );

    // Bind attributes before linking to ensure order
    bindAttribute( 0, "position" );

    // Link program
    glLinkProgram( m_programID );
    validateProgram( m_programID );

    // Must happen after program is linked
    getUniformLocations();
}

void GuiShader::getUniformLocations() {
    m_transformationMatrix = getUniformLocation( "transformationMatrix" );
}


// ------------------------------------------------------------------

SkyboxShader::SkyboxShader()
        : ShaderProgram(),
          m_rotation( 0 ),
          m_fogColour( 0 ) {
}

void SkyboxShader::init() {

    // File status result
    bool shader_file_exists;

    // Read in vertex shader
    std::string vertex_resource_path;
    vertex_resource_path += "shaders/water/";
    vertex_resource_path += EXERCISE_NAME;
    vertex_resource_path += "/skyboxVertex.glsl";
    const std::string vertex_path = common::getResource( vertex_resource_path, shader_file_exists );
    const std::string vertex_source = common::read_file( vertex_path );
    m_vertexShaderID = compile( vertex_source, GL_VERTEX_SHADER );

    // Read in fragment shader
    std::string fragment_resource_path;
    fragment_resource_path += "shaders/water/";
    fragment_resource_path += EXERCISE_NAME;
    fragment_resource_path += "/skyboxFragment.glsl";
    const std::string fragment_path = common::getResource( fragment_resource_path, shader_file_exists );
    const std::string fragment_source = common::read_file( fragment_path );
    m_fragmentShaderID = compile( fragment_source, GL_FRAGMENT_SHADER );

    // Create program
    m_programID = glCreateProgram();
    glAttachShader( m_programID, m_vertexShaderID );
    glAttachShader( m_programID, m_fragmentShaderID );

    // Bind attributes before linking to ensure order
    bindAttribute( 0, "position" );

    // Link program
    glLinkProgram( m_programID );
    validateProgram( m_programID );

    // Must happen after program is linked
    getUniformLocations();
}

void SkyboxShader::loadFogColour( float r, float g, float b ) {
    loadVector( m_fogColour, glm::vec3( r, g, b ) );
}

void SkyboxShader::connectTextureUnits() {
    loadInt( m_cubeMap, 0 );
    loadInt( m_cubeMap2, 1 );
}

void SkyboxShader::loadBlendFactor( float blend ) {
    loadFloat( m_blendFactor, blend );
}

void SkyboxShader::getUniformLocations() {
    m_projectionMatrix = getUniformLocation( "projectionMatrix" );
    m_viewMatrix = getUniformLocation( "viewMatrix" );
    m_fogColour = getUniformLocation( "fogColour" );
    m_blendFactor = getUniformLocation( "blendFactor" );
    m_cubeMap = getUniformLocation( "cubeMap" );
    m_cubeMap2 = getUniformLocation( "cubeMap2" );
}

void SkyboxShader::loadViewMatrix( const glm::mat4& mat ) {

    // Copy matrix and remove translation
    glm::mat4 view = mat;
    view[3][0] = 0.0;
    view[3][1] = 0.0;
    view[3][2] = 0.0;

    float rotationSpeed = 2.0f;
    m_rotation += rotationSpeed * common::DisplayManager::instance()->getFrameTimeSeconds();
    view = glm::rotate( view, glm::radians( m_rotation ), glm::vec3( 0, 1, 0 ) );

    loadMatrix( m_viewMatrix, view );
}

// ------------------------------------------------------------------

WaterShader::WaterShader() : ShaderProgram() {
}

void WaterShader::init() {

    // File status result
    bool shader_file_exists;

    // Read in vertex shader
    std::string vertex_resource_path;
    vertex_resource_path += "shaders/water/";
    vertex_resource_path += EXERCISE_NAME;
    vertex_resource_path += "/waterVertex.glsl";
    const std::string vertex_path = common::getResource( vertex_resource_path, shader_file_exists );
    assert( shader_file_exists );
    const std::string vertex_source = common::read_file( vertex_path );
    m_vertexShaderID = compile( vertex_source, GL_VERTEX_SHADER );

    // Read in fragment shader
    std::string fragment_resource_path;
    fragment_resource_path += "shaders/water/";
    fragment_resource_path += EXERCISE_NAME;
    fragment_resource_path += "/waterFragment.glsl";
    const std::string fragment_path = common::getResource( fragment_resource_path, shader_file_exists );
    assert( shader_file_exists );
    const std::string fragment_source = common::read_file( fragment_path );
    m_fragmentShaderID = compile( fragment_source, GL_FRAGMENT_SHADER );

    // Create program
    m_programID = glCreateProgram();
    glAttachShader( m_programID, m_vertexShaderID );
    glAttachShader( m_programID, m_fragmentShaderID );

    // Bind attributes before linking to ensure order
    bindAttribute( 0, "position" );

    // Link program
    glLinkProgram( m_programID );
    validateProgram( m_programID );

    // Must happen after program is linked
    getUniformLocations();
}

void WaterShader::getUniformLocations() {
    m_projectionMatrix = getUniformLocation( "projectionMatrix" );
    m_viewMatrix = getUniformLocation( "viewMatrix" );
    m_modelMatrix = getUniformLocation( "modelMatrix" );
    m_reflectionTexture = getUniformLocation( "reflectionTexture" );
    m_refractionTexture = getUniformLocation( "refractionTexture" );
    m_dudvMapTexture = getUniformLocation( "dudvMap" );
    m_moveFactor = getUniformLocation( "moveFactor" );

    printf( "%d, %d\n", m_reflectionTexture, m_refractionTexture );
}

void WaterShader::connectTextureUnits() {
    loadInt( m_reflectionTexture, 0 );
    loadInt( m_refractionTexture, 1 );
    loadInt( m_dudvMapTexture, 2 );
}

void WaterShader::loadModelMatrix( const glm::mat4& matrix ) {
    loadMatrix( m_modelMatrix, matrix );
}

void WaterShader::loadMoveFactor( float value ) {
    loadFloat( m_moveFactor, value );
}

// ------------------------------------------------------------------

