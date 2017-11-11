//
// Created by Eddie Hoyle on 24/10/17.
//

#include "texture.hh"

ModelTexture::ModelTexture( GLuint textureID )
        : m_textureID( textureID ),
          m_shineDamper( 1 ),
          m_reflectivity( 0 ) {
}

GLuint ModelTexture::getID() const {
    return m_textureID;
}