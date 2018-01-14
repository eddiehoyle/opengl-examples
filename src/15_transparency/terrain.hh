//
// Created by Eddie Hoyle on 9/11/17.
//

#ifndef OPENGL_EXAMPLES_14_TERRAIN_HH
#define OPENGL_EXAMPLES_14_TERRAIN_HH

#include "model.hh"
#include "loader.hh"

const float SIZE = 100;
const int VERTEX_COUNT = 128;

class Terrain {

public:
    explicit Terrain( int gridX, int gridZ, Loader& loader, ModelTexture& texture );
    RawModel generateTerrain( Loader& loader );
    float getX() const;
    float getZ() const;
    RawModel getModel() const;
    ModelTexture getTexture() const;

private:
    float m_x;
    float m_z;
    RawModel m_model;
    ModelTexture m_texture;

};


#endif //OPENGL_EXAMPLES_14_TERRAIN_HH
