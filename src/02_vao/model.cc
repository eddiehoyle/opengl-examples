//
// Created by Eddie Hoyle on 22/10/17.
//

#include "model.hh"

Model::Model( GLint vaoID, GLint vertexCount )
        : m_vaoID( vaoID ),
          m_vertexCount( vertexCount ) {
}

GLint Model::getVaoID() const {
    return m_vaoID;
}

GLint Model::getVertexCount() const {
    return m_vertexCount;
}
