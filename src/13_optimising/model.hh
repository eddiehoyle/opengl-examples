//
// Created by Eddie Hoyle on 22/10/17.
//

#ifndef OPENGL_EXAMPLES_MODEL_HH
#define OPENGL_EXAMPLES_MODEL_HH

#include <GL/glew.h>

#include "texture.hh"

class Model {

public:

    /// Constructor
    Model( GLint vaoID, GLint vertexCount );

    /// Get the VAO ID for this model
    GLint getVaoID() const;

    /// Get the vertex count for this model
    GLint getVertexCount() const;

    bool operator<( const Model& rhs ) const {
        return getVaoID() < rhs.getVaoID();
    }

private:
    GLint m_vaoID;
    GLint m_vertexCount;

};

class TexturedModel {

public:
    explicit TexturedModel( const Model& model, const ModelTexture& texture );
    Model getModel() const;
    ModelTexture getTexture() const;
    bool operator<( const TexturedModel& rhs ) const {
        return getModel().getVaoID() < rhs.getModel().getVaoID();
    }

private:
    Model m_model;
    ModelTexture m_texture;

};

#endif //OPENGL_EXAMPLES_MODEL_HH
