//
// Created by Eddie Hoyle on 22/10/17.
//

#include <string>
#include "loader.hh"
#include <GL/glew.h>

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>
#include <iostream>

Model Loader::loadToVao( const std::vector< GLfloat >& positions,
                         const std::vector< GLfloat >& textureCoords,
                         const std::vector< GLuint >& indices ) {
    GLint vaoID = createVaoID();
    bindIndicesBuffer( indices );
    storeDataInAttributeList( 0, 3, positions );
    storeDataInAttributeList( 1, 2, textureCoords );
    unbindVao();
    return Model( vaoID, indices.size() );
}

GLint Loader::createVaoID() {
    GLuint vaoID;
    glGenVertexArrays( 1, &vaoID );
    glBindVertexArray( vaoID );
    return vaoID;
}

GLuint Loader::loadTexture( const std::string& path ) {

    int width, height, channels;
    unsigned char* data = stbi_load(path.c_str(), &width, &height, &channels, 0 );

    GLuint textureID;
    glGenTextures( 1, &textureID );

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
    // End texture load

    std::cerr << "Loader::loadTexture() : width="
              << width << ", height="
              << height
              << std::endl;
    return textureID;
}

void Loader::bindIndicesBuffer( const std::vector< GLuint >& indices ) {
    GLuint vboID;
    glGenBuffers( 1, &vboID );
    glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, vboID );
    glBufferData( GL_ELEMENT_ARRAY_BUFFER, sizeof( GLuint ) * indices.size(), &indices[0], GL_STATIC_DRAW );
}

void Loader::storeDataInAttributeList( GLint attributeNumber,
                                       GLuint coordinateSize,
                                       const std::vector< GLfloat >& data ) {
    GLuint vboID;
    glGenBuffers( 1, &vboID );
    glBindBuffer( GL_ARRAY_BUFFER, vboID );
    glBufferData( GL_ARRAY_BUFFER, sizeof( GLfloat ) * data.size(), &data[0], GL_STATIC_DRAW );
    glVertexAttribPointer( attributeNumber,   // The attribute number
                           coordinateSize,    // Length of each data array
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
//    glDeleteTextures( textureID );
}
