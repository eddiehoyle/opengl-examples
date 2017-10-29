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
static const float kNearPlane = 0.1f;
static const float kFarPlane = 1000.0f;

Render::Render( StaticShader& shader ) {

    createProjectionMatrix();
    shader.start();
    shader.loadProjectionMatrix( m_projectionMatrix );
    shader.stop();
}

void Render::prepare() {
    glClear( GL_COLOR_BUFFER_BIT );
    glClearColor( 0.1, 0.2, 0.8, 1 );
}

void Render::render( const Entity& entity, StaticShader& shader ) {

    TexturedModel texturedModel = entity.getMode();

    Model model = texturedModel.getModel();
    ModelTexture texture = texturedModel.getTexture();
    glBindVertexArray( model.getVaoID() );
    glEnableVertexAttribArray( 0 );
    glEnableVertexAttribArray( 1 );

    glm::mat4 transformationMatrix = common::createTransformationMatrix(
            entity.getPosition(),
            entity.getRotation(),
            entity.getScale() );

    shader.loadTransformationMatrix( transformationMatrix );

    glActiveTexture( GL_TEXTURE0 );
    glBindTexture( GL_TEXTURE_2D, texture.getID() );
    glDrawElements( GL_TRIANGLES, model.getVertexCount(), GL_UNSIGNED_INT, 0 );
    glDisableVertexAttribArray( 0 );
    glDisableVertexAttribArray( 1 );
    glBindVertexArray( 0 );
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
