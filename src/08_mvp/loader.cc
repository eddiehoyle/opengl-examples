//
// Created by Eddie Hoyle on 22/10/17.
//

#include <string>
#include "loader.hh"
#include <GL/glew.h>

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>
#include <iostream>

RawModel Loader::loadToVao( const std::vector< GLfloat >& positions,
                         const std::vector< GLfloat >& textureCoords,
                         const std::vector< GLuint >& indices ) {
    GLint vaoID = createVaoID();
    bindIndicesBuffer( indices );
    storeDataInAttributeList( 0, 3, positions );
    storeDataInAttributeList( 1, 2, textureCoords );
    unbindVao();
    return RawModel( vaoID, indices.size() );
}

GLint Loader::createVaoID() {
    GLuint vaoID;
    glGenVertexArrays( 1, &vaoID );
    glBindVertexArray( vaoID );
    return vaoID;
}

GLuint Loader::loadTexture( const std::string& path ) {

    int width, height, bytesperpixel;
    unsigned char* data = stbi_load(path.c_str(), &width, &height, &bytesperpixel, STBI_rgb );

    GLenum colorFormat = GL_RGB;
    if ( bytesperpixel == 4 ) {
        colorFormat = GL_RGBA;
    }

    GLuint textureID;
    glGenTextures( 1, &textureID );
    glBindTexture(GL_TEXTURE_2D, textureID);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, colorFormat, GL_UNSIGNED_BYTE, data);

    stbi_image_free(data);

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
