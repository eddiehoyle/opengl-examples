//
// Created by Eddie Hoyle on 6/02/18.
//

#include <GL/glew.h>
#include <common/display.hh>
#include "buffer.hh"

static const int REFLECTION_WIDTH = 320;
static const int REFLECTION_HEIGHT = 180;

static const int REFRACTION_WIDTH = 1280;
static const int REFRACTION_HEIGHT = 720;

WaterFrameBuffers::WaterFrameBuffers() {
    initialiseReflectionFrameBuffer();
    initialiseRefractionFrameBuffer();
}

void WaterFrameBuffers::cleanup() {
    glDeleteFramebuffers( 1, &m_reflectionFrameBuffer );
    glDeleteTextures( 1, &m_reflectionTexture );
    glDeleteRenderbuffers( 1, &m_reflectionDepthBuffer );
    glDeleteFramebuffers( 1, &m_refractionFrameBuffer );
    glDeleteTextures( 1, &m_refractionTexture );
    glDeleteTextures( 1, &m_refractionDepthTexture );
}

void WaterFrameBuffers::bindReflectionFrameBuffer() {
    bindFrameBuffer( m_reflectionFrameBuffer, REFLECTION_WIDTH, REFLECTION_HEIGHT );
}

void WaterFrameBuffers::bindRefractionFrameBuffer() {
    bindFrameBuffer( m_refractionFrameBuffer, REFRACTION_WIDTH, REFRACTION_HEIGHT );
}

void WaterFrameBuffers::unbindCurrentFrameBuffer() {
    glBindFramebuffer( GL_FRAMEBUFFER, 0 );
    int width = common::DisplayManager::instance()->width();
    int height = common::DisplayManager::instance()->height();
    int mult = __APPLE__ == true ? 2 : 1;
    glViewport( 0, 0, width * mult, height * mult );
}

GLuint WaterFrameBuffers::getReflectionTexture() {
    return m_reflectionTexture;
}

GLuint WaterFrameBuffers::getRefractionTexture() {
    return m_refractionTexture;
}

GLuint WaterFrameBuffers::getRefractionDepthTexture() {
    return m_refractionDepthTexture;
}

void WaterFrameBuffers::initialiseReflectionFrameBuffer() {
    m_reflectionFrameBuffer = createFrameBuffer();
    m_reflectionTexture = createTextureAttachment( REFLECTION_WIDTH, REFLECTION_HEIGHT );
    m_reflectionDepthBuffer = createDepthBufferAttachment( REFLECTION_WIDTH, REFLECTION_HEIGHT );
    unbindCurrentFrameBuffer();
}

void WaterFrameBuffers::initialiseRefractionFrameBuffer() {
    m_refractionFrameBuffer = createFrameBuffer();
    m_refractionTexture = createTextureAttachment( REFRACTION_WIDTH, REFRACTION_HEIGHT );
    m_refractionDepthTexture = createDepthTextureAttachment( REFRACTION_WIDTH, REFRACTION_HEIGHT );
    unbindCurrentFrameBuffer();
}

void WaterFrameBuffers::bindFrameBuffer( int frameBuffer, int width, int height ) {
    glBindTexture( GL_TEXTURE_2D, 0 );
    glBindFramebuffer( GL_FRAMEBUFFER, frameBuffer );
    glViewport( 0, 0, width, height );
}

GLuint WaterFrameBuffers::createFrameBuffer() {
    GLuint frameBuffer;
    glGenFramebuffers( 1, &frameBuffer );
    glBindFramebuffer( GL_FRAMEBUFFER, frameBuffer );
    glDrawBuffer( GL_COLOR_ATTACHMENT0 );
    return frameBuffer;
}

GLuint WaterFrameBuffers::createTextureAttachment( int width, int height ) {
    GLuint texture;
    glGenTextures( 1, &texture );
    glBindTexture( GL_TEXTURE_2D, texture );
    glTexImage2D( GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, static_cast< void* >( 0 ) );
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
    glFramebufferTexture( GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, texture, 0 );
    return texture;

}

GLuint WaterFrameBuffers::createDepthTextureAttachment( int width, int height ) {
    GLuint texture;
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT32, width, height, 0, GL_DEPTH_COMPONENT, GL_FLOAT, static_cast< void* >( 0 ));
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glFramebufferTexture(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, texture, 0);
    return texture;
}

GLuint WaterFrameBuffers::createDepthBufferAttachment( int width, int height ) {
    GLuint depthBuffer;
    glGenRenderbuffers(1, &depthBuffer);
    glBindRenderbuffer(GL_RENDERBUFFER, depthBuffer);
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, width, height);
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, depthBuffer);
    return depthBuffer;

}
