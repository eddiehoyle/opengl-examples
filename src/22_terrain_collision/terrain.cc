//
// Created by Eddie Hoyle on 9/11/17.
//

#include <iostream>
#include <stb_image.h>
#include <glm/vec3.hpp>
#include <glm/ext.hpp>
#include "terrain.hh"

const float SIZE = 500;
const float MAX_HEIGHT = 40;
const float MAX_PIXEL_COLOUR = 256;

//const int VERTEX_COUNT = 128;

Terrain::Terrain( int gridX,
                  int gridZ,
                  Loader& loader,
                  TerrainTexturePack& texturePack,
                  TerrainTexture& blendMap,
                  const std::string& heightMap )
        : m_x( gridX * SIZE ),
          m_z( gridZ * SIZE ),
          m_model( generateTerrain( loader, heightMap ) ),
          m_texturePack( texturePack ),
          m_blendMap( blendMap ) {
}

TerrainTexturePack Terrain::getTexturePack() const {
    return m_texturePack;
}

TerrainTexture Terrain::getBlendMap() const {
    return m_blendMap;
}

Model Terrain::generateTerrain( Loader& loader, const std::string& heightMap ) {

    int VERTEX_COUNT = 128;

    int width, height, bytesperpixel;
    unsigned char* data = stbi_load( heightMap.c_str(), &width, &height, &bytesperpixel, STBI_default );

    GLenum dataFormat = GL_RGB;
    GLenum colorFormat = GL_RGB;
    if ( bytesperpixel == 4 ) {
        colorFormat = GL_RGBA;
        dataFormat = GL_RGBA;
    }

    VERTEX_COUNT = height;
    std::cerr << __func__ << " : height=" << height << std::endl;

    int count = VERTEX_COUNT * VERTEX_COUNT;
    float vertices[count * 3];
    float normals[count * 3];
    float textureCoords[count*2];
    int indices[6*(VERTEX_COUNT-1)*(VERTEX_COUNT-1)];

    int vertexPointer = 0;
    for(int i=0;i<VERTEX_COUNT;i++){
        for(int j=0;j<VERTEX_COUNT;j++){
            vertices[vertexPointer*3] = (float)j/((float)VERTEX_COUNT - 1) * SIZE;
            vertices[vertexPointer*3+1] = getHeight(j, i, width, bytesperpixel, data);
            vertices[vertexPointer*3+2] = (float)i/((float)VERTEX_COUNT - 1) * SIZE;

            glm::vec3 normal = calculateNormal(j, i, width, bytesperpixel, data);
            normals[vertexPointer*3] = normal.x;
            normals[vertexPointer*3+1] = normal.y;
            normals[vertexPointer*3+2] = normal.z;
            textureCoords[vertexPointer*2] = (float)j/((float)VERTEX_COUNT - 1);
            textureCoords[vertexPointer*2+1] = (float)i/((float)VERTEX_COUNT - 1);
            vertexPointer++;
        }
    }
    int pointer = 0;
    for(int gz=0;gz<VERTEX_COUNT-1;gz++){
        for(int gx=0;gx<VERTEX_COUNT-1;gx++){
            int topLeft = (gz*VERTEX_COUNT)+gx;
            int topRight = topLeft + 1;
            int bottomLeft = ((gz+1)*VERTEX_COUNT)+gx;
            int bottomRight = bottomLeft + 1;
            indices[pointer++] = topLeft;
            indices[pointer++] = bottomLeft;
            indices[pointer++] = topRight;
            indices[pointer++] = topRight;
            indices[pointer++] = bottomLeft;
            indices[pointer++] = bottomRight;
        }
    }


    std::vector< GLfloat > verticesVec( vertices, vertices + sizeof vertices / sizeof vertices[0] );
    std::vector< GLfloat > normalsVec( normals, normals + sizeof normals / sizeof normals[0] );
    std::vector< GLfloat > textureCoordsVec( textureCoords, textureCoords + sizeof textureCoords / sizeof textureCoords[0] );
    std::vector< GLuint > indicesVec( indices, indices + sizeof indices / sizeof indices[0] );

    return loader.loadToVao( verticesVec, textureCoordsVec, normalsVec, indicesVec );
}

float Terrain::getX() const {
    return m_x;
}

float Terrain::getZ() const {
    return m_z;
}

Model Terrain::getModel() const {
    return m_model;
}

float Terrain::getHeight( int x, int z, int width, int bytesperpixel, unsigned char *image ) {
    if ( x < 0 || x >= width || z < 0 || z >= width ) {
        return 0.0f;
    }

    unsigned char r = image[ ( x + z * width ) * bytesperpixel + 0 ];
    unsigned char g = image[ ( x + z * width ) * bytesperpixel + 1 ];
    unsigned char b = image[ ( x + z * width ) * bytesperpixel + 2 ];

    // https://www.youtube.com/watch?v=O9v6olrHPwI&list=PLRIWtICgwaX0u7Rf9zkZhLoLuZVfUksDP&index=21
    // 4:38

    float grey = ( r + g + b ) / 3.0f;
    grey -= MAX_PIXEL_COLOUR / 2.0f;
    grey /= MAX_PIXEL_COLOUR / 2.0f;
    grey *= MAX_HEIGHT;
    return grey;
}

glm::vec3 Terrain::calculateNormal( int x, int z, int width, int bytesperpixel, unsigned char *image ) {
    float heightL = getHeight( x-1, z, width, bytesperpixel, image );
    float heightR = getHeight( x+1, z, width, bytesperpixel, image );
    float heightD = getHeight( x, z-1, width, bytesperpixel, image );
    float heightU = getHeight( x, z+1, width, bytesperpixel, image );
    glm::vec3 normal = glm::normalize( glm::vec3( heightL - heightR,
                                                  2.0f,
                                                  heightD - heightU ) );
//    glm::vec3 normal = glm::normalize( glm::vec3( 0.0f, 1.0f, 0.0f ) );
    return normal;
}
