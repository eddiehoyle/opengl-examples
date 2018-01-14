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
