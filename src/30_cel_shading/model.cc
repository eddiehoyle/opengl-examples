//
// Created by Eddie Hoyle on 22/10/17.
//

#include "model.hh"

RawModel::RawModel( GLint vaoID, GLint vertexCount )
        : m_vaoID( vaoID ),
          m_vertexCount( vertexCount ) {
}

GLint RawModel::getVaoID() const {
    return m_vaoID;
}

GLint RawModel::getVertexCount() const {
    return m_vertexCount;
}

// ------------------------------------------------------------ //

TexturedModel::TexturedModel( const RawModel& model,
                              const ModelTexture& texture )
        : m_model( model ),
          m_texture( texture ) {
}

RawModel TexturedModel::getModel() const {
    return m_model;
}

ModelTexture TexturedModel::getTexture() const {
    return m_texture;
}