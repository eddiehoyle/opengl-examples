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

class Render {

public:

    explicit Render( StaticShader& shader );

    /// Prepare to render
    void prepare();

//    /// Render this model
//    void render( const Entity& entity, StaticShader& shader );

    /// TODO
    void render( const EntityMap& entityMap );

    /// TODO
    void createProjectionMatrix();

private:
    void prepareTexturedModel( const TexturedModel& texturedModel );
    void unbindTexturedModel();
    void prepareInstance( const Entity& entity );

private:
    glm::mat4 m_projectionMatrix;
    StaticShader m_shader;
};

class MasterRender {
public:
    explicit MasterRender( StaticShader& shader );
    void cleanup();
    void render( Light sun, common::Camera* camera );
    void processEntity( const Entity& entity );

private:
    StaticShader m_shader;
    Render m_render;
    EntityMap m_entities;


};


#endif //OPENGL_EXAMPLES_RENDER_HH
