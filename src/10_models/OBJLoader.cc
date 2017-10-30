//
// Created by Eddie Hoyle on 30/10/17.
//

#include <glm/vec3.hpp>
#include <fstream>
#include "OBJLoader.hh"
#include "../common/io.hh"
#include "../common/string.hh"

Model OBJLoader::loadObjModel( const std::string& path, Loader loader ) {

//    std::string data = common::read_file( path );

//    std::vector< glm::vec3 > vertices;
//    std::vector< glm::vec2 > textures;
//    std::vector< glm::vec3 > normals;
//    std::vector< glm::vec3 > indices;
//
//    std::vector< GLfloat > verticesArray;
//    std::vector< GLfloat > textureArray;
//    std::vector< GLfloat > normalArray;
//    std::vector< GLuint > indicesArray;

    // Read the file
    std::ifstream stream( path, std::ios::in );
    if ( !stream.good() ) {
        std::cerr << __func__ << " : File does not exist: " << path << std::endl;
        return Model( 0, 0 );
    }

    if ( stream.is_open() ) {
        std::string line;
        while ( getline( stream, line ) ) {
            common::SimpleString lineStr( line );

            // Vertex;
            if ( lineStr.startswith( "v " ) ) {

            } else if ( lineStr.startswith( "vt " ) ) {

            } else if ( lineStr.startswith( "vn " ) ) {

            } else if ( lineStr.startswith( "f " ) ) {

            }
        }

        stream.close();
    }

    return Model( 0, 0 );
}
