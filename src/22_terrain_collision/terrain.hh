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

    Model generateTerrain( Loader& loader, const std::string& heightMap );
    float getX() const;
    float getZ() const;
    Model getModel() const;
    TerrainTexturePack getTexturePack() const;
    TerrainTexture getBlendMap() const;


    float getHeight( int x, int z, int width, int bytesperpixel, unsigned char *image );
    glm::vec3 calculateNormal( int x, int z, int width, int bytesperpixel, unsigned char *image );

    float getHeightOfTerrain( float worldX, float worldZ ) const;

private:
    float m_x;
    float m_z;
    Model m_model;
    TerrainTexturePack m_texturePack;
    TerrainTexture m_blendMap;

    std::vector< std::vector< float > > m_heights;

};


#endif //OPENGL_EXAMPLES_17_TERRAIN_HH
