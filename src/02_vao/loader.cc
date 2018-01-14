//
// Created by Eddie Hoyle on 22/10/17.
//

#include "loader.hh"
#include <GL/glew.h>

RawModel Loader::loadToVao( const std::vector< GLfloat >& positions ) {
    GLint vaoID = createVaoID();
    storeDataInAttributeList( 0, positions );
    unbindVao();
    GLint vertexCount = positions.size() / 3;
    return RawModel( vaoID, vertexCount );
}

GLint Loader::createVaoID() {
    GLuint vaoID;
    glGenVertexArrays( 1, &vaoID );
    glBindVertexArray( vaoID );
    return vaoID;
}

void Loader::storeDataInAttributeList( GLint attributeNumber, const std::vector< GLfloat >& data ) {
    GLuint vboID;
    glGenBuffers( 1, &vboID );
    glBindBuffer( GL_ARRAY_BUFFER, vboID );
    glBufferData( GL_ARRAY_BUFFER, sizeof( GLfloat ) * data.size(), &data[0], GL_STATIC_DRAW );
    glVertexAttribPointer( attributeNumber,   // The attribute number
                           3,                 // Length of each 'vertex' data array
                           GL_FLOAT,          // Type of data
                           GL_FALSE,          // Is this data normalized
                           0,                 // Distance between vertices (is there any other data between them?)
                           0 );               // Offset. Should it start at the beginning of this
    glBindBuffer( GL_ARRAY_BUFFER, 0 );
}

void Loader::unbindVao() {
    glBindVertexArray( 0 );
}

void Loader::cleanup() {
//    // TODO
//    glDeleteVertexArrays( vaoID );
//    glDeleteBuffers( vboID );
}
