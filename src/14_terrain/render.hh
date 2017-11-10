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
#include "../common/camera.hh"

typedef std::pair< TexturedModel, std::vector< Entity > > EntityPair;
typedef std::map< EntityPair::first_type, EntityPair::second_type > EntityMap;

class EntityRenderer {

public:

    explicit EntityRenderer( StaticShader& shader, const glm::mat4& projectionMatrix );

    /// TODO
    void render( const EntityMap& entityMap );

    /// TODO

private:
    void prepareTexturedModel( const TexturedModel& texturedModel );
    void unbindTexturedModel();
    void prepareInstance( const Entity& entity );

private:
    StaticShader m_shader;
};

class MasterRenderer {

public:

    explicit MasterRenderer();

    void cleanup();

    /// Prepare to render
    void prepare();

    void render( Light sun, common::Camera* camera );

    void processEntity( const Entity& entity );

    void createProjectionMatrix();

private:
    StaticShader m_shader;
    EntityRenderer m_render;
    EntityMap m_entities;

    glm::mat4 m_projectionMatrix;
};


#endif //OPENGL_EXAMPLES_RENDER_HH
