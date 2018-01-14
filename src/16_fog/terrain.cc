//
// Created by Eddie Hoyle on 9/11/17.
//

#include <iostream>
#include "terrain.hh"

Terrain::Terrain( int gridX,
                  int gridZ,
                  Loader& loader,
                  ModelTexture& texture )
        : m_x( gridX * SIZE ),
          m_z( gridZ * SIZE ),
          m_model( generateTerrain( loader ) ),
          m_texture( texture ) {
}

RawModel Terrain::generateTerrain( Loader& loader ) {

    int count = VERTEX_COUNT * VERTEX_COUNT;
    float vertices[count * 3];
    float normals[count * 3];
    float textureCoords[count*2];
    int indices[6*(VERTEX_COUNT-1)*(VERTEX_COUNT-1)];

    int vertexPointer = 0;
    for(int i=0;i<VERTEX_COUNT;i++){
        for(int j=0;j<VERTEX_COUNT;j++){
            vertices[vertexPointer*3] = (float)j/((float)VERTEX_COUNT - 1) * SIZE;
            vertices[vertexPointer*3+1] = 0;
            vertices[vertexPointer*3+2] = (float)i/((float)VERTEX_COUNT - 1) * SIZE;
            normals[vertexPointer*3] = 0;
            normals[vertexPointer*3+1] = 1;
            normals[vertexPointer*3+2] = 0;
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

RawModel Terrain::getModel() const {
    return m_model;
}

ModelTexture Terrain::getTexture() const {
    return m_texture;
}
