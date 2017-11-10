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

EntityRenderer::EntityRenderer( StaticShader& shader,
                                const glm::mat4& projectionMatrix )
        : m_shader( shader ) {
}


void EntityRenderer::render( const EntityMap& entityMap ) {

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

void EntityRenderer::prepareTexturedModel( const TexturedModel& texturedModel ) {
    Model model = texturedModel.getModel();
    glBindVertexArray( model.getVaoID() );
    glEnableVertexAttribArray( 0 );
    glEnableVertexAttribArray( 1 );
    glEnableVertexAttribArray( 2 );

    ModelTexture texture = texturedModel.getTexture();
    m_shader.loadShineVariables( texture.getShineDamper(), texture.getReflectivity() );
    glActiveTexture( GL_TEXTURE0 );
    glBindTexture( GL_TEXTURE_2D, texture.getID() );

}

void EntityRenderer::unbindTexturedModel() {
    glDisableVertexAttribArray( 0 );
    glDisableVertexAttribArray( 1 );
    glDisableVertexAttribArray( 2 );
    glBindVertexArray( 0 );
}

void EntityRenderer::prepareInstance( const Entity& entity ) {
    glm::mat4 transformationMatrix = common::createTransformationMatrix(
            entity.getPosition(),
            entity.getRotation(),
            entity.getScale() );
    m_shader.loadTransformationMatrix( transformationMatrix );
}

// ------------------------------------------------------------------------------------------

TerrainRenderer::TerrainRenderer( TerrainShader& shader,
                                const glm::mat4& projectionMatrix )
        : m_shader( shader ) {
}

void TerrainRenderer::render( const std::vector< Terrain >& terrains ) {

    for ( const Terrain& terrain : terrains ) {

        prepareTerrain( terrain );
        loadModelMatrix( terrain );

        glDrawElements( GL_TRIANGLES,
                        terrain.getModel().getVertexCount(),
                        GL_UNSIGNED_INT,
                        0 );

        unbindTexturedModel();
    }
}

void TerrainRenderer::prepareTerrain( const Terrain& terrain ) {

    Model model = terrain.getModel();

    glBindVertexArray( model.getVaoID() );
    glEnableVertexAttribArray( 0 );
    glEnableVertexAttribArray( 1 );
    glEnableVertexAttribArray( 2 );

    ModelTexture texture = terrain.getTexture();
    m_shader.loadShineVariables( texture.getShineDamper(), texture.getReflectivity() );

    glActiveTexture( GL_TEXTURE0 );
    glBindTexture( GL_TEXTURE_2D, texture.getID() );

}

void TerrainRenderer::unbindTexturedModel() {
    glDisableVertexAttribArray( 0 );
    glDisableVertexAttribArray( 1 );
    glDisableVertexAttribArray( 2 );
    glBindVertexArray( 0 );
}

void TerrainRenderer::loadModelMatrix( const Terrain& terrain ) {
    glm::mat4 transformationMatrix = common::createTransformationMatrix(
            glm::vec3( terrain.getX(), 0.0, terrain.getZ() ),
            glm::vec3( 0, 0, 0 ),
            1 );
    m_shader.loadTransformationMatrix( transformationMatrix );
}


// ------------------------------------------------------------------------------------------

MasterRenderer::MasterRenderer( StaticShader& shader, TerrainShader& terrainShader )
        : m_shader( shader ),
          m_terrainShader( terrainShader ),
          m_entities(),
          m_renderer( m_shader, glm::mat4() ),
          m_terrainRenderer( m_terrainShader, glm::mat4() ) {

    // Note
    // 'm_shader' is initialised above and added to the renderer immediately
    // Do not re-init the shader after this otherwise things break. This
    // should be looked into

    createProjectionMatrix();

    glEnable( GL_CULL_FACE );
    glCullFace( GL_BACK );

    m_shader.start();
    m_shader.loadProjectionMatrix( m_projectionMatrix );
    m_shader.stop();

    m_terrainShader.start();
    m_terrainShader.loadProjectionMatrix( m_projectionMatrix );
    m_terrainShader.stop();

}

void MasterRenderer::createProjectionMatrix() {
    unsigned int width = common::DisplayManager::instance()->width();
    unsigned int height = common::DisplayManager::instance()->height();
    m_projectionMatrix = common::createProjectionMatrix(
            kFov,
            width,
            height,
            kNearPlane,
            kFarPlane );
}

void MasterRenderer::cleanup() {
    m_shader.cleanup();
    m_terrainShader.cleanup();
}

void MasterRenderer::processEntity( const Entity& entity ) {

    TexturedModel texturedModel = entity.getTexturedModel();

    if ( m_entities.find( texturedModel ) == m_entities.end() ) {
        std::vector< Entity > entities;
        m_entities.insert( EntityPair( texturedModel, entities ) );
    }

    m_entities[texturedModel].push_back( entity );
}

void MasterRenderer::processTerrain( const Terrain& terrain ) {
    m_terrains.push_back( terrain );
}

void MasterRenderer::prepare() {
    glEnable( GL_DEPTH_TEST );
    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
    glClearColor( 0.7, 0.1, 0.1, 1 );
}

void MasterRenderer::render( Light sun, common::Camera *camera ) {

    prepare();

    m_shader.start();
    m_shader.loadLight( sun );
    m_shader.loadViewMatrix( camera->matrix() );
    m_renderer.render( m_entities );
    m_shader.stop();

    m_terrainShader.start();
    m_terrainShader.loadLight( sun );
    m_terrainShader.loadViewMatrix( camera->matrix() );
    m_terrainRenderer.render( m_terrains );
    m_terrainShader.stop();

    m_terrains.clear();
    m_entities.clear();
}