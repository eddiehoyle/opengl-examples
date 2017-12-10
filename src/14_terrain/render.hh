//
// Created by Eddie Hoyle on 22/10/17.
//

#ifndef OPENGL_EXAMPLES_RENDER_HH
#define OPENGL_EXAMPLES_RENDER_HH

#include <map>
#include <vector>
#include "model.hh"
#include "entity.hh"
#include "shader.hh"
#include "../common/scene/camera.hh"
#include "terrain.hh"

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
};

// ------------------------------------------------------------------------------------

class TerrainRenderer {

public:
    explicit TerrainRenderer( TerrainShader& shader, const glm::mat4& projectionMatrix );
    void render( const std::vector< Terrain >& terrains );

private:
    void prepareTerrain( const Terrain& terrain );
    void unbindTexturedModel();
    void loadModelMatrix( const Terrain& terrain );

private:
    TerrainShader m_shader;
};

// ------------------------------------------------------------------------------------

class MasterRenderer {

public:

    explicit MasterRenderer();

    void cleanup();
    void prepare();
    void render( Light sun, common::Camera* camera );
    void processEntity( const Entity& entity );
    void processTerrain( const Terrain& terrain );
    void createProjectionMatrix();

private:

    /// Entities
    StaticShader m_shader;
    EntityRenderer m_renderer;
    EntityMap m_entities;

    /// Terrain
    TerrainShader m_terrainShader;
    TerrainRenderer m_terrainRenderer;
    std::vector< Terrain > m_terrains;

    glm::mat4 m_projectionMatrix;
};


#endif //OPENGL_EXAMPLES_RENDER_HH
