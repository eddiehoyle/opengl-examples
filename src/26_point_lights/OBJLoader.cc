//
// Created by Eddie Hoyle on 30/10/17.
//

#include <iostream>
#include <glm/vec3.hpp>
#include <fstream>
#include "OBJLoader.hh"
#include "../common/obj/parser.hh"
#include "../common/obj/tiny_obj_loader.hh"


// Removing this for now
//#include <assimp/Importer.hpp>      // C++ importer interface
//#include <assimp/scene.h>           // Output data structure
//#include <assimp/postprocess.h>     // Post processing fla

RawModel OBJLoader::loadObjModel( const std::string& path, Loader loader ) {

    std::vector< tinyobj::shape_t > shapes;
    tinyobj::LoadObj( shapes, path.c_str() );
    tinyobj::shape_t shape( shapes.front() );

    return loader.loadToVao( shape.mesh.vertices,
                             shape.mesh.texcoords,
                             shape.mesh.normals,
                             shape.mesh.indices );
}

RawModel OBJLoader::loadObjModel( const std::string& obj_path,
                                  const std::string& material_path,
                                  Loader loader ) {

    std::vector< tinyobj::shape_t > shapes;
    tinyobj::LoadObj( shapes, obj_path.c_str(), material_path.c_str() );
    tinyobj::shape_t shape( shapes.front() );

    return loader.loadToVao( shape.mesh.vertices,
                             shape.mesh.texcoords,
                             shape.mesh.normals,
                             shape.mesh.indices );
}

//RawModel OBJLoader::loadObjModel2( const std::string& path, Loader loader ) {
//
//    Assimp::Importer importer;
//
//    //load the file
//    const aiScene *scene = importer.ReadFile( path, aiProcess_Triangulate | aiProcess_FlipUVs );
//
//    assert( scene != nullptr );
//    assert( scene->mFlags != AI_SCENE_FLAGS_INCOMPLETE );
//    assert( scene->mRootNode );
//
//    std::vector< GLfloat > _vertices;
//    std::vector< GLfloat > _texcoords;
//    std::vector< GLfloat > _normals;
//    std::vector< GLuint > _indices;
//
//    for( unsigned int m = 0; m < scene->mNumMeshes; ++m ) {
//
//        aiMesh* mesh = scene->mMeshes[m];
//
//        for( unsigned int i = 0; i < mesh->mNumVertices; ++i ) {
//
//            _vertices.push_back( mesh->mVertices[i].x );
//            _vertices.push_back( mesh->mVertices[i].y );
//            _vertices.push_back( mesh->mVertices[i].z );
//
//            _normals.push_back( mesh->mNormals[i].x );
//            _normals.push_back( mesh->mNormals[i].y );
//            _normals.push_back( mesh->mNormals[i].z );
//
//            if(mesh->mTextureCoords[0]) {
//                _texcoords.push_back( mesh->mTextureCoords[0][i].x );
//                _texcoords.push_back( mesh->mTextureCoords[0][i].y );
//            } else {
//                _texcoords.push_back( 0.0 );
//                _texcoords.push_back( 0.0 );
//            }
//        }
//
//        for( unsigned int j = 0; j < mesh->mNumFaces; ++j ) {
//            aiFace face = mesh->mFaces[j];
//            for( unsigned int k = 0; k < face.mNumIndices; ++k ) {
//                _indices.push_back( face.mIndices[k] );
//            }
//        }
//    }

//    std::cerr << "OBJLoader::loadObjModel2() "
//              << ": vertices=" << _vertices.size()
//              << ", texcoords=" << _texcoords.size()
//              << ", normals=" << _normals.size()
//              << ", indices=" << _indices.size()
//              << std::endl;
//
//    return loader.loadToVao( _vertices,
//                             _texcoords,
//                             _normals,
//                             _indices );
//
//}
