//
// Created by Eddie Hoyle on 22/10/17.
//

#ifndef OPENGL_EXAMPLES_17_RENDER_HH
#define OPENGL_EXAMPLES_17_RENDER_HH

#include <map>
#include <vector>
#include "model.hh"
#include "entity.hh"
#include "shader.hh"
#include "terrain.hh"
#include "camera.hh"
#include "guis.hh"

const GLfloat kSkyRed = 0.54f;
const GLfloat kSkyGreen = 0.62f;
const GLfloat kSkyBlue = 0.69f;

typedef std::pair< TexturedModel, std::vector< Entity > > EntityPair;
typedef std::map< EntityPair::first_type, EntityPair::second_type > EntityMap;

class EntityRenderer {

public:
    explicit EntityRenderer( StaticShader& shader, const glm::mat4& projectionMatrix );
    void render( const EntityMap& entityMap );

private:
    void prepareTexturedModel( const TexturedModel& texturedModel );
    void unbindTexturedModel();
    void prepareInstance( const Entity& entity );

private:
    StaticShader m_shader;
    glm::mat4 m_projectionMatrix;
};

// ------------------------------------------------------------------------------------

class TerrainRenderer {

public:
    explicit TerrainRenderer( TerrainShader& shader, const glm::mat4& projectionMatrix );
    void render( const std::vector< Terrain >& terrains );
    void setProjectionMatrix( const glm::mat4& matrix ) {
        m_projectionMatrix = matrix;
    }

private:
    void prepareTerrain( const Terrain& terrain );
    void unbindTexturedModel();
    void loadModelMatrix( const Terrain& terrain );
    void bindTextures( const Terrain& terrain );

private:
    TerrainShader m_shader;
    glm::mat4 m_projectionMatrix;
};

// ------------------------------------------------------------------------------------

class GuiRenderer {

public:
    GuiRenderer( GuiShader& shader, const RawModel& quad );
    void render( const std::vector< GuiTexture >& guis );
    void cleanup();

private:
    RawModel m_quad;
    GuiShader m_shader;
};

// ------------------------------------------------------------------------------------

class SkyboxRenderer {

public:
    SkyboxRenderer( SkyboxShader& shader, const glm::mat4& projectionMatrix );
    void render( const Camera& camera, float r, float g, float b );
    void bindTextures();
    void cleanup();

private:
    SkyboxShader m_shader;
    RawModel m_cube;
    GLuint m_texture;
    GLuint m_nightTexture;

    float m_time;
};

// ------------------------------------------------------------------------------------

class MasterRenderer {
public:

    static void enableCulling();
    static void disableCulling();

public:

    explicit MasterRenderer( StaticShader& entityshader,
                             TerrainShader& terrainShader,
                             SkyboxShader& skyboxShader );

    void cleanup();
    void prepare();
    void render( const std::vector< Light >& lights, const Camera& camera );
    void processEntity( const Entity& entity );
    void processTerrain( const Terrain& terrain );
    void createProjectionMatrix();

    glm::mat4 getProjectionMatrix() const;

private:

    /// Entities
    StaticShader m_entityShader;
    EntityRenderer m_entityRenderer;
    EntityMap m_entities;

    /// Terrain
    TerrainShader m_terrainShader;
    TerrainRenderer m_terrainRenderer;
    std::vector< Terrain > m_terrains;

    /// Skybox
    SkyboxShader m_skyboxShader;
    SkyboxRenderer m_skyboxRenderer;

    glm::mat4 m_projectionMatrix;

};


#endif //OPENGL_EXAMPLES_17_RENDER_HH
