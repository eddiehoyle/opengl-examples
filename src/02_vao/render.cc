//
// Created by Eddie Hoyle on 22/10/17.
//

#include "render.hh"
#include "model.hh"
#include <GL/glew.h>
#include <iostream>

void Render::prepare() {
    glClear( GL_COLOR_BUFFER_BIT );
    glClearColor( 1, 0.5, 0, 1 );
}

void Render::render( const RawModel& model ) {
    glBindVertexArray( model.getVaoID() );
    glEnableVertexAttribArray( 0 );
    glDrawArrays( GL_TRIANGLES, 0, model.getVertexCount() );
    glDisableVertexAttribArray( 0 );
    glBindVertexArray( 0 );
}
