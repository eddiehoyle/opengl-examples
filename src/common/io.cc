//
// Created by Eddie Hoyle on 13/08/17.
//

#include "io.hh"

#include <fstream>

std::string read_file( const std::string& path ) {

    // Read the Vertex Shader code from the file
    std::string data;
    std::ifstream stream( path, std::ios::in );
    if ( stream.is_open() ) {
        std::string line;
        while ( getline( stream, line ) )
            data += "\n" + line;
        stream.close();
    }
    return data;
}
