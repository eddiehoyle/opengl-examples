//
// Created by Eddie Hoyle on 9/11/17.
//

#ifndef OPENGL_EXAMPLES_17_TERRAIN_HH
#define OPENGL_EXAMPLES_17_TERRAIN_HH

#include "model.hh"
#include "loader.hh"

class Terrain {

public:
    explicit Terrain( int gridX, int gridZ,
                      Loader& loader,
                      TerrainTexturePack& texturePack,
                      TerrainTexture& blendMap,
                      const std::string& heightMap );

    RawModel generateTerrain( Loader& loader, const std::string& heightMap );
    float getX() const;
    float getZ() const;
    RawModel getModel() const;
    TerrainTexturePack getTexturePack() const;
    TerrainTexture getBlendMap() const;

    float getHeightMapHeight( int x, int z, int width, int bytesperpixel, unsigned char *image );
    glm::vec3 calculateNormal( int x, int z, int width, int bytesperpixel, unsigned char *image );

private:
    float m_x;
    float m_z;
    RawModel m_model;
    TerrainTexturePack m_texturePack;
    TerrainTexture m_blendMap;

};


#endif //OPENGL_EXAMPLES_17_TERRAIN_HH
