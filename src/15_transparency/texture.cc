//
// Created by Eddie Hoyle on 24/10/17.
//

#include "texture.hh"

ModelTexture::ModelTexture( GLuint textureID )
        : m_textureID( textureID ) {
}

GLuint ModelTexture::getID() const {
    return m_textureID;
}


GLfloat ModelTexture::getShineDamper() const {
    return m_shineDamper;
}

void ModelTexture::setShineDamper( GLfloat value ) {
    m_shineDamper = value;
}

GLfloat ModelTexture::getReflectivity() const {
    return m_reflectivity;
}

void ModelTexture::setReflectivity( GLfloat value ) {
    m_reflectivity = value;
}

bool ModelTexture::isHasTransparency() const {
    return m_hasTransparency;
}

void ModelTexture::setHasTransparency( bool state ) {
    m_hasTransparency = state;
}

bool ModelTexture::isUseFakeLighting() const {
    return m_useFakeLighting;
}

void ModelTexture::setUseFakeLighting( bool state ) {
    m_useFakeLighting = state;
}

