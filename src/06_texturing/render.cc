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

void Render::render( const Model& model ) {
    glBindVertexArray( model.getVaoID() );
    glEnableVertexAttribArray( 0 );
    glDrawElements( GL_TRIANGLES, model.getVertexCount(), GL_UNSIGNED_INT, 0 );
    glDisableVertexAttribArray( 0 );
    glBindVertexArray( 0 );
}

void Render::render( const TexturedModel& texturedModel ) {
    Model model = texturedModel.getModel();
    glBindVertexArray( model.getVaoID() );
    glEnableVertexAttribArray( 0 );
    glDrawElements( GL_TRIANGLES, model.getVertexCount(), GL_UNSIGNED_INT, 0 );
    glDisableVertexAttribArray( 0 );
    glBindVertexArray( 0 );
}
