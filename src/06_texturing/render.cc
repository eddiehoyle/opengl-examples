//
// Created by Eddie Hoyle on 22/10/17.
//

#include "render.hh"
#include "model.hh"
#include <GL/glew.h>
#include <iostream>

void Render::prepare() {
    glClear( GL_COLOR_BUFFER_BIT );
    glClearColor( 0.1, 0.2, 0.8, 1 );
}

void Render::render( const TexturedModel& texturedModel ) {

    Model model = texturedModel.getModel();
    ModelTexture texture = texturedModel.getTexture();
    glBindVertexArray( model.getVaoID() );
    glEnableVertexAttribArray( 0 );
    glEnableVertexAttribArray( 1 );
    glActiveTexture( GL_TEXTURE0 );
    glBindTexture( GL_TEXTURE_2D, texture.getID() );
    glDrawElements( GL_TRIANGLES, model.getVertexCount(), GL_UNSIGNED_INT, 0 );
    glDisableVertexAttribArray( 0 );
    glDisableVertexAttribArray( 1 );
    glBindVertexArray( 0 );
}
