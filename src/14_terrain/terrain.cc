//
// Created by Eddie Hoyle on 9/11/17.
//

#include "terrain.hh"

Terrain::Terrain( int x,
                  int y,
                  Loader& loader,
                  ModelTexture& texture )
        : m_x( x * SIZE ),
          m_y( y * SIZE ),
          m_model( generateTerrain( loader )),
          m_texture( texture ) {}

Model Terrain::generateTerrain( Loader& loader ) {
    int count = VERTEX_COUNT * VERTEX_COUNT;

    std::vector< GLfloat > vertices;
    std::vector< GLfloat > normals;
    std::vector< GLfloat > textureCoords;
    std::vector< GLuint > indices;

    vertices.reserve( count * 3 );
    normals.reserve( count * 3 );
    textureCoords.reserve( count * 2 );
    indices.reserve( 6 * ( VERTEX_COUNT - 1 ) * ( VERTEX_COUNT - 1 ) );

    int vertexPointer = 0;
    for ( int i = 0; i < VERTEX_COUNT; ++i ) {
        for ( int j = 0; j < VERTEX_COUNT; ++j ) {
            vertices[vertexPointer * 3] = ( float )j / ( ( float )VERTEX_COUNT - 1 ) * SIZE;
            vertices[vertexPointer * 3 + 1] = 0;
            vertices[vertexPointer * 3 + 2] = ( float )i / ( ( float )VERTEX_COUNT - 1 ) * SIZE;
            normals[vertexPointer * 3] = 0;
            normals[vertexPointer * 3 + 1] = 1;
            normals[vertexPointer * 3 + 2] = 0;
            textureCoords[vertexPointer * 2] = ( float )j / ( ( float )VERTEX_COUNT - 1 );
            textureCoords[vertexPointer * 2 + 1] = ( float )i / ( ( float )VERTEX_COUNT - 1 );
            vertexPointer++;
        }
    }

    int pointer = 0;
    for ( int gz = 0; gz < VERTEX_COUNT; ++gz ) {
        for ( int gx = 0; gx < VERTEX_COUNT; ++gx ) {
            int topLeft = ( gz * VERTEX_COUNT ) + gx;
            int topRight = topLeft + 1;
            int bottomLeft = ( ( gz + 1 ) * VERTEX_COUNT ) + gx;
            int bottomRight = bottomLeft + 1;
            indices[pointer++] = topLeft;
            indices[pointer++] = bottomLeft;
            indices[pointer++] = topRight;
            indices[pointer++] = topRight;
            indices[pointer++] = bottomLeft;
            indices[pointer++] = bottomRight;
        }
    }
    return loader.loadToVao( vertices, textureCoords, normals, indices );
}

float Terrain::getX() const {
    return m_x;
}

float Terrain::getY() const {
    return m_y;
}

Model Terrain::getModel() const {
    return m_model;
}

ModelTexture Terrain::getTexture() const {
    return m_texture;
}
