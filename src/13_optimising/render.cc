//
// Created by Eddie Hoyle on 22/10/17.
//

#include "render.hh"
#include "model.hh"
#include "entity.hh"
#include "shader.hh"
#include "../common/math.hh"
#include "../common/display.hh"
#include <GL/glew.h>
#include <iostream>

static const float kFov = 70;
static const float kNearPlane = 0.01f;
static const float kFarPlane = 1000.0f;

Render::Render( StaticShader& shader )
: m_shader( shader ) {
    glEnable( GL_CULL_FACE );
    glCullFace( GL_BACK );
    createProjectionMatrix();
    m_shader.start();
    m_shader.loadProjectionMatrix( m_projectionMatrix );
    m_shader.stop();
}

void Render::prepare() {
    glEnable( GL_DEPTH_TEST );
    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
    glClearColor( 0.7, 0.1, 0.1, 1 );
}

void Render::render( const EntityMap& entityMap ) {

    for ( auto entityPair : entityMap ) {

        TexturedModel texturedModel = entityPair.first;
        prepareTexturedModel( texturedModel );

        std::vector< Entity > entities = entityPair.second;
        for ( auto entity : entities ) {
            prepareInstance( entity );
            glDrawElements( GL_TRIANGLES, texturedModel.getModel().getVertexCount(), GL_UNSIGNED_INT, 0 );
        }
        unbindTexturedModel();
    }
}

void Render::prepareTexturedModel( const TexturedModel& texturedModel ) {
    RawModel model = texturedModel.getModel();
    glBindVertexArray( model.getVaoID() );
    glEnableVertexAttribArray( 0 );
    glEnableVertexAttribArray( 1 );
    glEnableVertexAttribArray( 2 );

    ModelTexture texture = texturedModel.getTexture();
    m_shader.loadShineVariables( texture.getShineDamper(), texture.getReflectivity() );
    glActiveTexture( GL_TEXTURE0 );
    glBindTexture( GL_TEXTURE_2D, texture.getID() );

}

void Render::unbindTexturedModel() {
    glDisableVertexAttribArray( 0 );
    glDisableVertexAttribArray( 1 );
    glDisableVertexAttribArray( 2 );
    glBindVertexArray( 0 );
}
void Render::prepareInstance( const Entity& entity ) {
    glm::mat4 transformationMatrix = common::createTransformationMatrix(
            entity.getPosition(),
            entity.getRotation(),
            entity.getScale() );
    m_shader.loadTransformationMatrix( transformationMatrix );
}

void Render::createProjectionMatrix() {

    unsigned int width = common::DisplayManager::instance()->width();
    unsigned int height = common::DisplayManager::instance()->height();
    m_projectionMatrix = common::createProjectionMatrix(
            kFov,
            width,
            height,
            kNearPlane,
            kFarPlane );
}

// ------------------------------------------------------------------------------------------

MasterRender::MasterRender( StaticShader& shader )
        : m_shader( shader ),
          m_entities(),
          m_render( shader ) {}

void MasterRender::cleanup() {
    m_shader.cleanup();
}

void MasterRender::processEntity( const Entity& entity ) {

    TexturedModel texturedModel = entity.getTexturedModel();

    if ( m_entities.find( texturedModel ) == m_entities.end() ) {
        std::vector< Entity > entities;
        m_entities.insert( EntityPair( texturedModel, entities ) ) ;
    }

    m_entities[texturedModel].push_back( entity );
}

void MasterRender::render( Light sun, common::Camera* camera ) {
    m_render.prepare();
    m_shader.start();
    m_shader.loadLight( sun );
    m_shader.loadViewMatrix( camera->matrix() );
    m_render.render( m_entities );
    m_shader.stop();
    m_entities.clear();
}