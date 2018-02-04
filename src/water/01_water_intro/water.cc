//
// Created by Eddie Hoyle on 4/02/18.
//

#include "water.hh"

static const float TILE_SIZE = 1;

WaterTile::WaterTile( float centerX, float centerZ, float height )
        : m_x( centerX ),
          m_z( centerZ ),
          m_height( height ) {

}

float WaterTile::getHeight() const {
    return m_height;
}

float WaterTile::getX() const {
    return m_x;
}

float WaterTile::getZ() const {
    return m_z;
}

float WaterTile::getTileSize() const {
    return TILE_SIZE;
}
