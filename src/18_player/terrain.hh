//
// Created by Eddie Hoyle on 9/11/17.
//

#ifndef OPENGL_EXAMPLES_18_TERRAIN_HH
#define OPENGL_EXAMPLES_18_TERRAIN_HH

#include "model.hh"
#include "loader.hh"

const float SIZE = 500;
const int VERTEX_COUNT = 128;

class Terrain {

public:
    explicit Terrain( int gridX, int gridZ,
                      Loader& loader,
                      TerrainTexturePack& texturePack,
                      TerrainTexture& blendMap );

    Model generateTerrain( Loader& loader );
    float getX() const;
    float getZ() const;
    Model getModel() const;
    TerrainTexturePack getTexturePack() const;
    TerrainTexture getBlendMap() const;

private:
    float m_x;
    float m_z;
    Model m_model;
    TerrainTexturePack m_texturePack;
    TerrainTexture m_blendMap;

};


#endif //OPENGL_EXAMPLES_18_TERRAIN_HH
