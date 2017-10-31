//
// Created by Eddie Hoyle on 30/10/17.
//

#include <glm/vec3.hpp>
#include <fstream>
#include "OBJLoader.hh"
#include "../common/io.hh"
#include "../common/string.hh"

Model OBJLoader::loadObjModel( const std::string& path, Loader loader ) {

    std::vector< GLfloat > tempVertices;
    std::vector< GLfloat > tempUvs;
    std::vector< GLfloat > tempNormals;
    std::vector< GLuint > tempIndices;

    common::read_obj( path,
                      tempVertices,
                      tempUvs,
                      tempNormals,
                      tempIndices );
//
//    std::vector< glm::vec3 > vertices;
//    std::vector< glm::vec2 > uvs;
//    std::vector< glm::vec3 > normals;
//    std::vector< GLuint > indices;
//
//    common::loadOBJ( path.c_str(),
//                     vertices,
//                     uvs,
//                     normals,
//                     indices );
//
//    std::vector< GLfloat > stream_vertices;
//    for ( glm::vec3 vec : vertices ) {
//        stream_vertices.push_back( vec.x );
//        stream_vertices.push_back( vec.y );
//        stream_vertices.push_back( vec.z );
//    }
//
//    std::vector< GLfloat > stream_uvs;
//    for ( glm::vec2 vec : uvs ) {
//        stream_uvs.push_back( vec.x );
//        stream_uvs.push_back( vec.y );
//    }
//
//    std::vector< GLfloat > stream_normals;
//    for ( glm::vec3 vec : normals ) {
//        stream_normals.push_back( vec.x );
//        stream_normals.push_back( vec.y );
//        stream_normals.push_back( vec.z );
//    }
//
//    std::vector< GLuint > stream_indices;
//    for ( GLuint index : indices ) {
//        stream_indices.push_back( index );
//    }
//
//    std::cerr << __func__ << " : stream_vertices=" << stream_vertices.size()
//              << ", stream_uvs=" << stream_uvs.size()
//              << ", stream_normals=" << stream_normals.size()
//              << ", stream_indices=" << stream_indices.size()
//              << std::endl;
//
//    return loader.loadToVao( stream_vertices, stream_uvs, indices );
    return Model( 0, 0 );
}
