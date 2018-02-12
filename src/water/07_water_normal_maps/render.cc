//
// Created by Eddie Hoyle on 22/10/17.
//

#include "render.hh"
#include "model.hh"
#include "entity.hh"
#include "shader.hh"
#include "water.hh"
#include "buffer.hh"
#include <common/math.hh>
#include <common/display.hh>
#include <common/resources.hh>
#include <GL/glew.h>
#include <iostream>

static const float FOV = 70;
static const float NEAR_PLANE = 0.01f;
static const float FAR_PLANE = 1000.0f;

static const float WAVE_SPEED = 0.03f;

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
          m_cube( 0, 0 ),
          m_time( 0 ) {

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

    const std::string skyboxRightPath = common::getResource( "skybox_right.png", result );
    assert( result );
    const std::string skyboxLeftPath = common::getResource( "skybox_left.png", result );
    assert( result );
    const std::string skyboxTopPath = common::getResource( "skybox_top.png", result );
    assert( result );
    const std::string skyboxBottomPath = common::getResource( "skybox_bottom.png", result );
    assert( result );
    const std::string skyboxBackPath = common::getResource( "skybox_back.png", result );
    assert( result );
    const std::string skyboxFrontPath = common::getResource( "skybox_front.png", result );
    assert( result );

    std::vector< std::string > skyboxPaths = {
            skyboxRightPath,
            skyboxLeftPath,
            skyboxTopPath,
            skyboxBottomPath,
            skyboxBackPath,
            skyboxFrontPath,
    };

    const std::string skyboxNightRightPath = common::getResource( "skybox_nightRight.png", result );
    assert( result );
    const std::string skyboxNightLeftPath = common::getResource( "skybox_nightLeft.png", result );
    assert( result );
    const std::string skyboxNightTopPath = common::getResource( "skybox_nightTop.png", result );
    assert( result );
    const std::string skyboxNightBottomPath = common::getResource( "skybox_nightBottom.png", result );
    assert( result );
    const std::string skyboxNightBackPath = common::getResource( "skybox_nightBack.png", result );
    assert( result );
    const std::string skyboxNightFrontPath = common::getResource( "skybox_nightFront.png", result );
    assert( result );

    std::vector< std::string > skyboxNightPaths = {
            skyboxNightRightPath,
            skyboxNightLeftPath,
            skyboxNightTopPath,
            skyboxNightBottomPath,
            skyboxNightBackPath,
            skyboxNightFrontPath,
    };

    Loader loader;

    m_cube = loader.loadToVao( vertices, 3 );
    m_texture = loader.loadCubeMap( skyboxPaths );
    m_nightTexture = loader.loadCubeMap( skyboxNightPaths );
    m_shader.start();
    m_shader.connectTextureUnits();
    m_shader.loadProjectionMatrix( projectionMatrix );
    m_shader.stop();
}

void SkyboxRenderer::render( const Camera& camera, float r, float g, float b ) {
    m_shader.start();
    m_shader.loadViewMatrix( camera.view() );
    m_shader.loadFogColour( r, g, b );
    glBindVertexArray( m_cube.getVaoID() );
    glEnableVertexAttribArray( 0 );
    bindTextures();
    glDrawArrays( GL_TRIANGLES, 0, m_cube.getVertexCount() );
    glDisableVertexAttribArray( 0 );
    glBindVertexArray( 0 );
    m_shader.stop();
}

void SkyboxRenderer::bindTextures() {
    m_time += common::DisplayManager::instance()->getFrameTimeSeconds() * 1000;
    m_time = int( m_time ) % 24000;
//    int texture1;
//    int texture2;
//    float blendFactor;
//    if ( m_time >= 0 && m_time < 5000 ) {
//        texture1 = m_nightTexture;
//        texture2 = m_nightTexture;
//        blendFactor = ( m_time - 0 ) / ( 5000 - 0 );
//    } else if ( m_time >= 5000 && m_time < 8000 ) {
//        texture1 = m_nightTexture;
//        texture2 = m_texture;
//        blendFactor = ( m_time - 5000 ) / ( 8000 - 5000 );
//    } else if ( m_time >= 8000 && m_time < 21000 ) {
//        texture1 = m_texture;
//        texture2 = m_texture;
//        blendFactor = ( m_time - 8000 ) / ( 21000 - 8000 );
//    } else {
//        texture1 = m_texture;
//        texture2 = m_nightTexture;
//        blendFactor = ( m_time - 21000 ) / ( 24000 - 21000 );
//    }

    // Clamp to daytime for now
    int texture1 = m_texture;
    int texture2 = m_texture;
    float blendFactor = 1.0;

    glActiveTexture( GL_TEXTURE0 );
    glBindTexture( GL_TEXTURE_CUBE_MAP, texture1 );
    glActiveTexture( GL_TEXTURE1 );
    glBindTexture( GL_TEXTURE_CUBE_MAP, texture2 );
    m_shader.loadBlendFactor( blendFactor );
}

void SkyboxRenderer::cleanup() {
    m_shader.cleanup();
}

// ------------------------------------------------------------------------------------------


WaterRenderer::WaterRenderer( WaterShader& shader,
                              const RawModel& quad,
                              const glm::mat4& projectionMatrix,
                              const WaterFrameBuffers& fbos )
        : m_shader( shader ),
          m_quad( quad ),
          m_fbos( fbos ),
          m_dudvTexture( 0 ) {

    bool result;
    const std::string dudvMapPath = common::getResource( "dudvMap.png", result );
    assert( result );
    const std::string normalMapPath = common::getResource( "normalMap.png", result );
    assert( result );

    Loader loader;
    m_dudvTexture = loader.loadTexture( dudvMapPath );
    m_normalMapTexture = loader.loadTexture( normalMapPath );

    // Note
    // 'm_shader' is initialised before added to this renderer.
    // Do not re-init the shader after this otherwise things break.
    // This is stupid and should be fixed
    m_shader.start();
    m_shader.connectTextureUnits();
    m_shader.loadProjectionMatrix( projectionMatrix );
    m_shader.stop();
}

void WaterRenderer::render( const std::vector< WaterTile >& water, const Camera& camera, const Light& light ) {

    prepareRender( camera, light );

    for ( const WaterTile& tile : water ) {
        glm::mat4 modelMatrix = common::createTransformationMatrix( glm::vec3( tile.getX(), tile.getHeight(), tile.getZ() ),
                                                                    glm::vec3( 0, 0, 0 ),
                                                                    tile.getTileSize() );
        m_shader.loadModelMatrix( modelMatrix );
        glDrawArrays( GL_TRIANGLES, 0, m_quad.getVertexCount() );
    }

    unbind();
}

void WaterRenderer::prepareRender( const Camera& camera, const Light& light ) {
    m_shader.start();
    m_shader.loadViewMatrix( camera.view() );
    m_moveFactor += WAVE_SPEED * common::DisplayManager::instance()->getFrameTimeSeconds();
    if ( m_moveFactor > 1.0f ) {
        m_moveFactor = 0.0f;
    }
    m_shader.loadMoveFactor( m_moveFactor );
    m_shader.loadLightColour( light.getColour() );
    m_shader.loadLightPosition( light.getPosition() );
    m_shader.loadCameraPosition( camera.position() );
    glBindVertexArray( m_quad.getVaoID() );
    glEnableVertexAttribArray( 0 );
    glActiveTexture( GL_TEXTURE0 );
    glBindTexture( GL_TEXTURE_2D, m_fbos.getReflectionTexture() );
    glActiveTexture( GL_TEXTURE1 );
    glBindTexture( GL_TEXTURE_2D, m_fbos.getRefractionTexture() );
    glActiveTexture( GL_TEXTURE2 );
    glBindTexture( GL_TEXTURE_2D, m_dudvTexture );
    glActiveTexture( GL_TEXTURE3 );
    glBindTexture( GL_TEXTURE_2D, m_normalMapTexture );
}

void WaterRenderer::unbind() {
    glDisableVertexAttribArray( 0 );
    glBindVertexArray( 0 );
    m_shader.stop();
}
// ------------------------------------------------------------------------------------------

MasterRenderer::MasterRenderer( StaticShader& entityShader,
                                TerrainShader& terrainShader,
                                SkyboxShader& skyboxShader )
        : m_entityShader( entityShader ),
          m_terrainShader( terrainShader ),
          m_skyboxShader( skyboxShader ),
          m_entities(),
          m_terrains(),
          m_entityRenderer( m_entityShader, glm::mat4() ),
          m_terrainRenderer( m_terrainShader, glm::mat4() ),
          m_skyboxRenderer( m_skyboxShader, glm::mat4() ) {

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
            FOV,
            width,
            height,
            NEAR_PLANE,
            FAR_PLANE );
}

void MasterRenderer::cleanup() {
    m_entityShader.cleanup();
    m_terrainShader.cleanup();
    m_skyboxShader.cleanup();
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

glm::mat4 MasterRenderer::getProjectionMatrix() const {
    return m_projectionMatrix;
}

void MasterRenderer::render( const std::vector< Light >& lights, const Camera& camera, const glm::vec4& clipPlane ) {

    prepare();

    m_entityShader.start();
    m_entityShader.loadClipPlane( clipPlane );
    m_entityShader.loadSkyColour( kSkyRed, kSkyGreen, kSkyBlue );
    m_entityShader.loadLights( lights );
    m_entityShader.loadViewMatrix( camera.view() );
    m_entityRenderer.render( m_entities );
    m_entityShader.stop();

    m_terrainShader.start();
    m_terrainShader.loadClipPlane( clipPlane );
    m_terrainShader.loadSkyColour( kSkyRed, kSkyGreen, kSkyBlue );
    m_terrainShader.loadLights( lights );
    m_terrainShader.loadViewMatrix( camera.view() );
    m_terrainRenderer.render( m_terrains );
    m_terrainShader.stop();

    m_skyboxShader.start();
    m_skyboxRenderer.render( camera, kSkyRed, kSkyGreen, kSkyBlue );
    m_skyboxShader.stop();

    m_terrains.clear();
    m_entities.clear();
}

void MasterRenderer::renderScene( const Entity& player,
                                  const std::vector< Entity >& entities,
                                  const std::vector< Terrain >& terrains,
                                  const std::vector< Light >& lights,
                                  const Camera& camera,
                                  const glm::vec4& clipPlane ) {

    processEntity( player );

    for ( const auto& terrain : terrains ) {
        processTerrain( terrain );
    }

    for ( const auto& entity : entities ) {
        processEntity( entity );
    }

    render( lights, camera, clipPlane );
}