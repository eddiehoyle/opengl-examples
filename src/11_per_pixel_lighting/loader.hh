//
// Created by Eddie Hoyle on 22/10/17.
//

#ifndef OPENGL_EXAMPLES_11_LOADER_HH
#define OPENGL_EXAMPLES_11_LOADER_HH

#include <vector>
#include "model.hh"

class Loader {

public:

    /// Create a model from some vertices
    Model loadToVao( const std::vector< GLfloat >& positions,
                     const std::vector< GLfloat >& textureCoords,
                     const std::vector< GLfloat >& normals,
                     const std::vector< GLuint >& indices );

    /// TODO
    GLuint loadTexture( const std::string& path );

    /// Clean up the vao/vbos
    void cleanup();

private:

    /// Create a vertex array id
    GLint createVaoID();

    /// TODO
    void bindIndicesBuffer( const std::vector< GLuint >& indices );

    /// Store vertex data into an attribute handle
    void storeDataInAttributeList( GLint attributeNumber,
                                   GLuint coordinateSize,
                                   const std::vector< GLfloat >& vertices );

    /// Unbind vertex array handle
    void unbindVao();
};


#endif //OPENGL_EXAMPLES_11_LOADER_HH
