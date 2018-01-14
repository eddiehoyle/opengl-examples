//
// Created by Eddie Hoyle on 30/10/17.
//

#include <glm/vec3.hpp>
#include <fstream>
#include "OBJLoader.hh"
#include "../common/obj/parser.hh"

RawModel OBJLoader::loadObjModel( const std::string& path, Loader loader ) {

    common::Shape shape;
    common::load_obj( path, shape );

    return loader.loadToVao( shape.mesh.vertices,
                             shape.mesh.texcoords,
                             shape.mesh.indices );
}
