//
// Created by Eddie Hoyle on 4/02/18.
//

#ifndef OPENGL_EXAMPLES_WATER_HH
#define OPENGL_EXAMPLES_WATER_HH


class WaterTile {

public:
    WaterTile( float centerX, float centerZ, float height );
    float getHeight() const;
    float getX() const;
    float getZ() const;
    float getTileSize() const;

private:
    float m_height;
    float m_x;
    float m_z;
};


#endif //OPENGL_EXAMPLES_WATER_HH
