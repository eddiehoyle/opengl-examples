//
// Created by Eddie Hoyle on 22/10/17.
//

#ifndef LEARNING_OPENGL_03_INDICIES_LOADER_HH
#define LEARNING_OPENGL_03_INDICIES_LOADER_HH

#include <vector>
#include "model.hh"

class Loader {

public:

    /// Create a model from some vertices
    Model loadToVao( const std::vector< GLfloat >& positions,
                     const std::vector< GLuint >& indices );

    /// Clean up the vao/vbos
    void cleanup();

private:

    /// Create a vertex array id
    GLint createVaoID();

    /// TODO
    void bindIndicesBuffer( const std::vector< GLuint >& indices );

    /// Store vertex data into an attribute handle
    void storeDataInAttributeList( GLint attributeNumber,
                                   const std::vector< GLfloat >& vertices );

    /// Unbind vertex array handle
    void unbindVao();
};


#endif //LEARNING_OPENGL_03_INDICIES_LOADER_HH
