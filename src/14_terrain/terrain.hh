//
// Created by Eddie Hoyle on 9/11/17.
//

#ifndef OPENGL_EXAMPLES_14_TERRAIN_HH
#define OPENGL_EXAMPLES_14_TERRAIN_HH

#include "model.hh"
#include "loader.hh"

const float SIZE = 600;
const int VERTEX_COUNT = 128;


class Terrain {

public:
    explicit Terrain( int gridX, int gridZ, Loader& loader, ModelTexture& texture );
    Model generateTerrain( Loader& loader );

    float getX() const;

    float getY() const;

    Model getModel() const;

    ModelTexture getTexture() const;

private:
    float m_x;
    float m_y;
    Model m_model;
    ModelTexture m_texture;

};


#endif //OPENGL_EXAMPLES_14_TERRAIN_HH
