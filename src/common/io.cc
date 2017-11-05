//
// Created by Eddie Hoyle on 13/08/17.
//

#include "io.hh"
#include "obj/parser.hh"
#include "obj/tiny_obj_loader.hh"

#include <vector>
#include <stdio.h>
#include <string>
#include <cstring>

#include <fstream>
#include <GL/glew.h>
#include <glm/ext.hpp>

namespace common {

std::string read_file( const std::string& path ) {

    // Read the file
    std::string data;
    std::ifstream stream( path, std::ios::in );
    if ( !stream.good() ) {
        std::cerr << __func__ << " : File does not exist: " << path << std::endl;
        return std::string();
    }

    if ( stream.is_open() ) {
        std::string line;
        while ( getline( stream, line ) )
            data += "\n" + line;
        stream.close();
    }
    return data;
}

} // namespace common