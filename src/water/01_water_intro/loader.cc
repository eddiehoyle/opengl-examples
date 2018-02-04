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
                         const std::vector< GLfloat >& normals,
                         const std::vector< GLuint >& indices ) {
    GLint vaoID = createVaoID();
    bindIndicesBuffer( indices );
    storeDataInAttributeList( 0, 3, positions );
    storeDataInAttributeList( 1, 2, textureCoords );
    storeDataInAttributeList( 2, 3, normals);
    unbindVao();
    return RawModel( vaoID, indices.size() );
}

RawModel Loader::loadToVao( const std::vector< float >& positions,
                            int dimensions ) {
    int vaoID = createVaoID();
    storeDataInAttributeList( 0, dimensions, positions );
    unbindVao();
    return RawModel( vaoID, positions.size() / dimensions );
}

GLint Loader::createVaoID() {
    GLuint vaoID;
    glGenVertexArrays( 1, &vaoID );
    glBindVertexArray( vaoID );
    m_vaos.push_back( vaoID );
    return vaoID;
}

GLuint Loader::loadCubeMap( std::vector< std::string > textureFiles ) {

    assert( textureFiles.size() == 6 );

    GLuint texID;
    glGenTextures( 1, &texID );
    glActiveTexture( GL_TEXTURE0 );
    glBindTexture( GL_TEXTURE_CUBE_MAP, texID );

    GLenum targets[6] = {
            GL_TEXTURE_CUBE_MAP_POSITIVE_X,
            GL_TEXTURE_CUBE_MAP_NEGATIVE_X,
            GL_TEXTURE_CUBE_MAP_POSITIVE_Y,
            GL_TEXTURE_CUBE_MAP_NEGATIVE_Y,
            GL_TEXTURE_CUBE_MAP_POSITIVE_Z,
            GL_TEXTURE_CUBE_MAP_NEGATIVE_Z,
    };

    // NOTE
    // All cube map textures MUST be same format, eg RGB or RGBA

    for ( std::size_t i = 0; i < textureFiles.size(); ++i ) {

        TextureData data = decodeTextureFile( textureFiles[i] );
        glTexImage2D( targets[i],
                      0,
                      data.getFormat(),
                      data.getWidth(),
                      data.getHeight(),
                      0,
                      data.getFormat(),
                      GL_UNSIGNED_BYTE,
                      data.getBuffer() );
    }

    glTexParameteri( GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
    glTexParameteri( GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
    glTexParameteri( GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri( GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri( GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

    m_textures.push_back( texID );

    return texID;
}

TextureData Loader::decodeTextureFile( const std::string& fileName ) {

    int width, height, bytesperpixel;
    unsigned char* data = stbi_load( fileName.c_str(), &width, &height, &bytesperpixel, STBI_default );

    GLenum dataFormat = GL_RGB;
    GLenum colorFormat = GL_RGB;
    if ( bytesperpixel == 4 ) {
        colorFormat = GL_RGBA;
        dataFormat = GL_RGBA;
    }

    // TextureData takes ownership of image data
    return TextureData( data, dataFormat, width, height );
}

GLuint Loader::loadTexture( const std::string& path ) {

    int width, height, bytesperpixel;
    unsigned char* data = stbi_load(path.c_str(), &width, &height, &bytesperpixel, STBI_default );

    GLenum dataFormat = GL_RGB;
    GLenum colorFormat = GL_RGB;
    if ( bytesperpixel == 4 ) {
        colorFormat = GL_RGBA;
        dataFormat = GL_RGBA;
    }

    GLuint textureID;
    glGenTextures( 1, &textureID );
    glBindTexture(GL_TEXTURE_2D, textureID);

    glTexImage2D(GL_TEXTURE_2D, 0, dataFormat, width, height, 0, colorFormat, GL_UNSIGNED_BYTE, data);

    glGenerateMipmap( GL_TEXTURE_2D );
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT );
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT );
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR );
    glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_LOD_BIAS, -0.4f );

    stbi_image_free(data);

    m_textures.push_back( textureID );

    return textureID;
}

void Loader::bindIndicesBuffer( const std::vector< GLuint >& indices ) {
    GLuint vboID;
    glGenBuffers( 1, &vboID );
    glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, vboID );
    glBufferData( GL_ELEMENT_ARRAY_BUFFER, sizeof( GLuint ) * indices.size(), &indices[0], GL_STATIC_DRAW );
    m_vbos.push_back( vboID );
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
    m_vbos.push_back( vboID );
}

void Loader::unbindVao() {
    glBindVertexArray( 0 );
}

void Loader::cleanup() {
//    // TODO
    for ( GLuint vao : m_vaos ) {
        glDeleteVertexArrays( 1, &vao );
    }
    for ( GLuint vbo : m_vbos ) {
        glDeleteBuffers( 1, &vbo );
    }
    for ( GLuint texture : m_textures ) {
        glDeleteTextures( 1, &texture );
    }

}
