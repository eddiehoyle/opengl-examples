//
// Created by Eddie Hoyle on 24/10/17.
//

#ifndef OPENGL_EXAMPLES_TEXTURE_HH
#define OPENGL_EXAMPLES_TEXTURE_HH


#include <GL/glew.h>
#include <vector>

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

    int getNumberOfRows();
    void setNumberOfRows( int num );

private:
    GLuint m_textureID;
    GLfloat m_shineDamper;
    GLfloat m_reflectivity;

    bool m_hasTransparency;
    bool m_useFakeLighting;

    int m_numberOfRows;
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

class TextureData {

public:
    TextureData( unsigned char* buffer, GLuint format, int width, int height );
    ~TextureData();
    int getWidth() const;
    int getHeight() const;
    unsigned char* getBuffer() const;
    GLuint getFormat() const;

private:
    int m_width;
    int m_height;
    unsigned char* m_buffer;
    GLuint m_format;
};


#endif //OPENGL_EXAMPLES_TEXTURE_HH
