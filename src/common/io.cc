//
// Created by Eddie Hoyle on 13/08/17.
//

#include "io.hh"

#include <fstream>

namespace common {

std::string read_file( const std::string& path ) {

    // Read the Vertex Shader code from the file
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