//
// Created by Eddie Hoyle on 24/10/17.
//

#ifndef OPENGL_EXAMPLES_17_TEXTURE_HH
#define OPENGL_EXAMPLES_17_TEXTURE_HH


#include <GL/glew.h>

class ModelTexture {

public:
    explicit ModelTexture( GLuint textureID );
    GLuint getID() const;

    GLfloat getShineDamper() const;
    GLfloat getReflectivity() const;

    void setShineDamper( GLfloat value );
    void setReflectivity( GLfloat value );

    bool isHasTransparency() const;
    void setHasTransparency( bool state );

    bool isUseFakeLighting() const;
    void setUseFakeLighting( bool state );

private:
    GLuint m_textureID;
    GLfloat m_shineDamper;
    GLfloat m_reflectivity;

    bool m_hasTransparency;
    bool m_useFakeLighting;
};

class TerrainTexture {

public:
    explicit TerrainTexture( GLuint id );
    GLuint getTextureID() const;

private:
    GLuint m_textureID;
};

class TerrainTexturePack {

public:
    TerrainTexturePack( const TerrainTexture& backgroundTexture,
                        const TerrainTexture& rTexture,
                        const TerrainTexture& gTexture,
                        const TerrainTexture& bTexture );

    TerrainTexture getBackgroundTexture() const;
    TerrainTexture getRTexture() const;
    TerrainTexture getGTexture() const;
    TerrainTexture getBTexture() const;


private:
    TerrainTexture m_backgroundTexture;
    TerrainTexture m_rTexture;
    TerrainTexture m_gTexture;
    TerrainTexture m_bTexture;

};


#endif //OPENGL_EXAMPLES_17_TEXTURE_HH
