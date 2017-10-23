//
// Created by Eddie Hoyle on 22/10/17.
//

#ifndef LEARNING_OPENGL_05_COLOURING_RENDER_HH
#define LEARNING_OPENGL_05_COLOURING_RENDER_HH

#include "model.hh"

class Render {

public:

    /// Prepare to render
    void prepare();

    /// Render this model
    void render( const Model& model );

};


#endif //LEARNING_OPENGL_05_COLOURING_RENDER_HH
