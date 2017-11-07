//
// Created by Eddie Hoyle on 22/10/17.
//

#ifndef OPENGL_EXAMPLES_11_RENDER_HH
#define OPENGL_EXAMPLES_11_RENDER_HH

#include "model.hh"
#include "entity.hh"
#include "shader.hh"

class Render {

public:

    explicit Render( StaticShader& shader );

    /// Prepare to render
    void prepare();

    /// Render this model
    void render( const Entity& entity, StaticShader& shader );

    /// TODO
    void createProjectionMatrix();

private:
    glm::mat4 m_projectionMatrix;


};


#endif //OPENGL_EXAMPLES_11_RENDER_HH
