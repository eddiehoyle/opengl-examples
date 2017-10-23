//
// Created by Eddie Hoyle on 22/10/17.
//

#include "loader.hh"
#include <GL/glew.h>

Model Loader::loadToVao( const std::vector< GLfloat >& positions,
                         const std::vector< GLuint >& indices ) {
    GLint vaoID = createVaoID();
    bindIndicesBuffer( indices );
    storeDataInAttributeList( 0, positions );
    unbindVao();
    return Model( vaoID, indices.size() );
}

GLint Loader::createVaoID() {
    GLuint vaoID;
    glGenVertexArrays( 1, &vaoID );
    glBindVertexArray( vaoID );
    return vaoID;
}

void Loader::bindIndicesBuffer( const std::vector< GLuint >& indices ) {
    GLuint vboID;
    glGenBuffers( 1, &vboID );
    glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, vboID );
    glBufferData( GL_ELEMENT_ARRAY_BUFFER, sizeof( GLuint ) * indices.size(), &indices, GL_STATIC_DRAW );
}

void Loader::storeDataInAttributeList( GLint attributeNumber, const std::vector< GLfloat >& data ) {
    GLuint vboID;
    glGenBuffers( 1, &vboID );
    glBindBuffer( GL_ARRAY_BUFFER, vboID );
    glBufferData( GL_ARRAY_BUFFER, sizeof( GLfloat ) * data.size(), &data, GL_STATIC_DRAW );
    glVertexAttribPointer( attributeNumber,   // The attribute number
                           3,                 // Length of each 'vertex' data array
                           GL_FLOAT,          // Type of data
                           GL_FALSE,          // Is this data normalized
                           0,                 // Distance between vertices (is there any other data between them?)
                           0 );               // Offset. Should it start at the beginning of this data?
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
