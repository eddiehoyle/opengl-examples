//
// Created by Eddie Hoyle on 22/10/17.
//

#ifndef LEARNING_OPENGL_05_COLOURING_RAWMODEL_HH
#define LEARNING_OPENGL_05_COLOURING_RAWMODEL_HH

#include <GL/glew.h>


class RawModel {

public:

    /// Constructor
    RawModel( GLint vaoID, GLint vertexCount );

    /// Get the VAO ID for this model
    GLint getVaoID() const;

    /// Get the vertex count for this model
    GLint getVertexCount() const;

private:
    GLint m_vaoID;
    GLint m_vertexCount;

};


#endif //LEARNING_OPENGL_05_COLOURING_RAWMODEL_HH
