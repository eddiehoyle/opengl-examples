//
// Created by Eddie Hoyle on 24/10/17.
//

#include "texture.hh"
#include <stb_image.h>

ModelTexture::ModelTexture( GLuint textureID )
        : m_textureID( textureID ),
          m_numberOfRows( 1 ) {
}

int ModelTexture::getNumberOfRows() {
    return m_numberOfRows;
}

void ModelTexture::setNumberOfRows( int num ) {
    m_numberOfRows = num;
}

GLuint ModelTexture::getID() const {
    return m_textureID;
}

GLfloat ModelTexture::getShineDamper() const {
    return m_shineDamper;
}

void ModelTexture::setShineDamper( GLfloat value ) {
    m_shineDamper = value;
}

GLfloat ModelTexture::getReflectivity() const {
    return m_reflectivity;
}

void ModelTexture::setReflectivity( GLfloat value ) {
    m_reflectivity = value;
}

bool ModelTexture::isHasTransparency() const {
    return m_hasTransparency;
}

void ModelTexture::setHasTransparency( bool state ) {
    m_hasTransparency = state;
}

bool ModelTexture::isUseFakeLighting() const {
    return m_useFakeLighting;
}

void ModelTexture::setUseFakeLighting( bool state ) {
    m_useFakeLighting = state;
}

// ---------------------------------------------------------------------------


TerrainTexture::TerrainTexture( GLuint id )
        : m_textureID( id ) {
}

GLuint TerrainTexture::getTextureID() const {
    return m_textureID;
}

TerrainTexturePack::TerrainTexturePack( const TerrainTexture& backgroundTexture,
                                        const TerrainTexture& rTexture,
                                        const TerrainTexture& gTexture,
                                        const TerrainTexture& bTexture )
        : m_backgroundTexture( backgroundTexture ),
          m_rTexture( rTexture ),
          m_gTexture( gTexture ),
          m_bTexture( bTexture ) {
}

TerrainTexture TerrainTexturePack::getBackgroundTexture() const {
    return m_backgroundTexture;
}

TerrainTexture TerrainTexturePack::getRTexture() const {
    return m_rTexture;
}

TerrainTexture TerrainTexturePack::getGTexture() const {
    return m_gTexture;
}

TerrainTexture TerrainTexturePack::getBTexture() const {
    return m_bTexture;
}

// ----------------------------------------------------------------- //

TextureData::TextureData( unsigned char* buffer, GLuint format, int width, int height )
        : m_width( width ),
          m_height( height ),
          m_format( format ),
          m_buffer( buffer ) {
}

TextureData::~TextureData() {
    stbi_image_free( m_buffer );
}

int TextureData::getWidth() const {
    return m_width;
}

int TextureData::getHeight() const {
    return m_height;
}

unsigned char* TextureData::getBuffer() const {
    return m_buffer;
}

GLuint TextureData::getFormat() const {
    return m_format;
}
