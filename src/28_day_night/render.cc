//
// Created by Eddie Hoyle on 22/10/17.
//

#include "render.hh"
#include "model.hh"
#include "entity.hh"
#include "shader.hh"
#include "../common/math.hh"
#include "../common/display.hh"
#include "../common/resources.hh"
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
    RawModel model = texturedModel.getModel();
    glBindVertexArray( model.getVaoID() );
    glEnableVertexAttribArray( 0 );
    glEnableVertexAttribArray( 1 );
    glEnableVertexAttribArray( 2 );

    ModelTexture texture = texturedModel.getTexture();
    m_shader.loadNumberOfRows( texture.getNumberOfRows() );

    if ( texture.isHasTransparency() ) {
        MasterRenderer::disableCulling();
    }

    m_shader.loadFakeLighting( texture.isUseFakeLighting() );
    m_shader.loadShineVariables( texture.getShineDamper(), texture.getReflectivity() );

    glActiveTexture( GL_TEXTURE0 );
    glBindTexture( GL_TEXTURE_2D, texture.getID() );

}

void EntityRenderer::unbindTexturedModel() {

    MasterRenderer::enableCulling();

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
    m_shader.loadOffset( glm::vec2( entity.getTextureXOffset(), entity.getTextureYOffset() ) );
}

// ------------------------------------------------------------------------------------------

TerrainRenderer::TerrainRenderer( TerrainShader& shader,
                                  const glm::mat4& projectionMatrix )
        : m_shader( shader ) {
    m_shader.start();
    m_shader.loadProjectionMatrix( projectionMatrix );
    m_shader.connectTextureUnits();
    m_shader.stop();
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

    RawModel model = terrain.getModel();

    glBindVertexArray( model.getVaoID() );
    glEnableVertexAttribArray( 0 );
    glEnableVertexAttribArray( 1 );
    glEnableVertexAttribArray( 2 );
    bindTextures( terrain );
    m_shader.loadShineVariables( 1, 0 );
}

void TerrainRenderer::bindTextures( const Terrain& terrain ) {
    TerrainTexturePack texturePak = terrain.getTexturePack();
    glActiveTexture( GL_TEXTURE0 );
    glBindTexture( GL_TEXTURE_2D, texturePak.getBackgroundTexture().getTextureID() );
    glActiveTexture( GL_TEXTURE1 );
    glBindTexture( GL_TEXTURE_2D, texturePak.getRTexture().getTextureID() );
    glActiveTexture( GL_TEXTURE2 );
    glBindTexture( GL_TEXTURE_2D, texturePak.getGTexture().getTextureID() );
    glActiveTexture( GL_TEXTURE3 );
    glBindTexture( GL_TEXTURE_2D, texturePak.getBTexture().getTextureID() );
    glActiveTexture( GL_TEXTURE4 );
    glBindTexture( GL_TEXTURE_2D, terrain.getBlendMap().getTextureID() );
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

GuiRenderer::GuiRenderer( GuiShader& shader, const RawModel& quad )
        : m_quad( quad ),
          m_shader( shader ) {

    // Note
    // 'm_entityShader' is initialised before added to this renderer.
    // Do not re-init the shader after this otherwise things break.
    // This is stupid and should be fixed
}

void GuiRenderer::render( const std::vector< GuiTexture >& guis ) {
    m_shader.start();
    glBindVertexArray( m_quad.getVaoID() );
    glEnableVertexAttribArray( 0 );
    glEnable( GL_BLEND );
    glBlendFunc( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA );
    glDisable( GL_DEPTH_TEST );
    for ( const GuiTexture& gui : guis ) {
        glActiveTexture( GL_TEXTURE0 );
        glBindTexture( GL_TEXTURE_2D, gui.getTextureID() );
        glm::mat4 matrix = common::createTransformationMatrix( gui.getPosition(), gui.getScale() );
        m_shader.loadTransformationMatrix( matrix );
        glDrawArrays( GL_TRIANGLE_STRIP, 0, m_quad.getVertexCount() );
    }
    glEnable( GL_DEPTH_TEST );
    glDisable( GL_BLEND );
    glDisableVertexAttribArray( 0 );
    glBindVertexArray( 0 );
    m_shader.stop();
}

void GuiRenderer::cleanup() {
    m_shader.cleanup();
}

// ------------------------------------------------------------------------------------------

SkyboxRenderer::SkyboxRenderer( SkyboxShader& shader,
                                const glm::mat4& projectionMatrix )
        : m_shader( shader ),
          m_cube( 0, 0 ) {

    // Note
    // 'm_entityShader' is initialised before added to this renderer.
    // Do not re-init the shader after this otherwise things break.
    // This is stupid and should be fixed

    GLfloat size = 500.0f;

    std::vector< GLfloat > vertices = {
            -size, size, -size,
            -size, -size, -size,
            size, -size, -size,
            size, -size, -size,
            size, size, -size,
            -size, size, -size,

            -size, -size, size,
            -size, -size, -size,
            -size, size, -size,
            -size, size, -size,
            -size, size, size,
            -size, -size, size,

            size, -size, -size,
            size, -size, size,
            size, size, size,
            size, size, size,
            size, size, -size,
            size, -size, -size,

            -size, -size, size,
            -size, size, size,
            size, size, size,
            size, size, size,
            size, -size, size,
            -size, -size, size,

            -size, size, -size,
            size, size, -size,
            size, size, size,
            size, size, size,
            -size, size, size,
            -size, size, -size,

            -size, -size, -size,
            -size, -size, size,
            size, -size, -size,
            size, -size, -size,
            -size, -size, size,
            size, -size, size
    };

    bool result;
    const std::string skyboxRightPath = common::getResource( "skybox_right.jpg", result );
    assert( result );
    const std::string skyboxLeftPath = common::getResource( "skybox_left.jpg", result );
    assert( result );
    const std::string skyboxTopPath = common::getResource( "skybox_top.jpg", result );
    assert( result );
    const std::string skyboxBottomPath = common::getResource( "skybox_bottom.jpg", result );
    assert( result );
    const std::string skyboxBackPath = common::getResource( "skybox_back.jpg", result );
    assert( result );
    const std::string skyboxFrontPath = common::getResource( "skybox_front.jpg", result );
    assert( result );

    std::vector< std::string > skyboxPaths = {
            skyboxRightPath,
            skyboxLeftPath,
            skyboxTopPath,
            skyboxBottomPath,
            skyboxBackPath,
            skyboxFrontPath,
    };

    Loader loader;

    m_cube = loader.loadToVao( vertices, 3 );
    m_texture = loader.loadCubeMap( skyboxPaths );
    m_shader.start();
    m_shader.loadProjectionMatrix( projectionMatrix );
    m_shader.stop();
}

void SkyboxRenderer::render( const Camera& camera ) {
    m_shader.start();
    m_shader.loadViewMatrix( camera.view() );
    glBindVertexArray( m_cube.getVaoID() );
    glEnableVertexAttribArray( 0 );
    glActiveTexture( GL_TEXTURE0 );
    glBindTexture( GL_TEXTURE_CUBE_MAP, m_texture );
    glDrawArrays( GL_TRIANGLES, 0, m_cube.getVertexCount() );
    glDisableVertexAttribArray( 0 );
    glBindVertexArray( 0 );
    m_shader.stop();
}

void SkyboxRenderer::cleanup() {
    m_shader.cleanup();
}

// ------------------------------------------------------------------------------------------

MasterRenderer::MasterRenderer( StaticShader& entityShader,
                                TerrainShader& terrainShader,
                                SkyboxShader& skyboxShader )
        : m_entityShader( entityShader ),
          m_terrainShader( terrainShader ),
          m_skyboxShader( skyboxShader ),
          m_entities(),
          m_entityRenderer( m_entityShader, glm::mat4() ),
          m_terrainRenderer( m_terrainShader, glm::mat4() ),
          m_skyboxRenderer( m_skyboxShader, glm::mat4() ){

    // Note
    // 'm_entityShader' is initialised above and added to the renderer immediately
    // Do not re-init the shader after this otherwise things break. This
    // should be looked into

    enableCulling();

    createProjectionMatrix();

    m_entityShader.start();
    m_entityShader.loadProjectionMatrix( m_projectionMatrix );
    m_entityShader.stop();

    m_terrainShader.start();
    m_terrainShader.loadProjectionMatrix( m_projectionMatrix );
    m_terrainShader.stop();

    m_skyboxShader.start();
    m_skyboxShader.loadProjectionMatrix( m_projectionMatrix );
    m_skyboxShader.stop();

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
    m_entityShader.cleanup();
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
    glClearColor( kSkyRed, kSkyGreen, kSkyBlue, 1 );
}

void MasterRenderer::enableCulling() {
    glEnable( GL_CULL_FACE );
    glCullFace( GL_BACK );
}

void MasterRenderer::disableCulling() {
    glDisable( GL_CULL_FACE );
}

void MasterRenderer::render( const std::vector< Light >& lights, const Camera& camera ) {

    prepare();

    m_entityShader.start();
    m_entityShader.loadSkyColour( kSkyRed, kSkyGreen, kSkyBlue );
    m_entityShader.loadLights( lights );
    m_entityShader.loadViewMatrix( camera.view() );
    m_entityRenderer.render( m_entities );
    m_entityShader.stop();

    m_terrainShader.start();
    m_terrainShader.loadSkyColour( kSkyRed, kSkyGreen, kSkyBlue );
    m_terrainShader.loadLights( lights );
    m_terrainShader.loadViewMatrix( camera.view() );
    m_terrainRenderer.render( m_terrains );
    m_terrainShader.stop();

    m_skyboxShader.start();
    m_skyboxRenderer.render( camera );
    m_skyboxShader.stop();

    m_terrains.clear();
    m_entities.clear();
}