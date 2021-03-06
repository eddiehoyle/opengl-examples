//
// Created by Eddie Hoyle on 22/10/17.
//

#ifndef OPENGL_EXAMPLES_LOADER_HH
#define OPENGL_EXAMPLES_LOADER_HH

#include <vector>
#include <string>
#include "model.hh"

class Loader {

public:

    /// Create a model from some vertices
    RawModel loadToVao( const std::vector< GLfloat >& positions,
                     const std::vector< GLfloat >& textureCoords,
                     const std::vector< GLfloat >& normals,
                     const std::vector< GLuint >& indices );

    /// Cubemap support
    RawModel loadToVao( const std::vector< float >& positions, int dimensions );

    /// TODO
    GLuint loadTexture( const std::string& path );

    /// TODO
    GLuint loadCubeMap( std::vector< std::string > textureFiles );

    /// Clean up the vao/vbos
    void cleanup();

private:

    /// Create a vertex array id
    GLint createVaoID();

    /// TODO
    TextureData decodeTextureFile( const std::string& fileName );

    /// TODO
    void bindIndicesBuffer( const std::vector< GLuint >& indices );

    /// Store vertex data into an attribute handle
    void storeDataInAttributeList( GLint attributeNumber,
                                   GLuint coordinateSize,
                                   const std::vector< GLfloat >& vertices );

    /// Unbind vertex array handle
    void unbindVao();

    std::vector< GLuint > m_vaos;
    std::vector< GLuint > m_vbos;
    std::vector< GLuint > m_textures;
};


#endif //OPENGL_EXAMPLES_LOADER_HH
