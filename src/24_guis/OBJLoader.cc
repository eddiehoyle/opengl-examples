//
// Created by Eddie Hoyle on 30/10/17.
//

#include <glm/vec3.hpp>
#include <fstream>
#include "OBJLoader.hh"
#include "../common/obj/parser.hh"
#include "../common/obj/tiny_obj_loader.hh"

RawModel OBJLoader::loadObjModel( const std::string& path, Loader loader ) {

    common::Shape shape;
    common::load_obj( path, shape );

//    std::vector< tinyobj::shape_t > shapes;
//    tinyobj::LoadObj( shapes, path.c_str() );
//    tinyobj::shape_t shape( shapes.front() );

    return loader.loadToVao( shape.mesh.vertices,
                             shape.mesh.texcoords,
                             shape.mesh.normals,
                             shape.mesh.indices );
}
