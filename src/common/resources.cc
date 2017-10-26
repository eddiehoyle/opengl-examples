//
// Created by Eddie Hoyle on 26/10/17.
//

#include <ios>
#include <fstream>
#include "resources.hh"

namespace common {

std::string getResource( const std::string& path, bool& result ) {

    // Create full resource path
    std::string fullpath = PROJECT_ROOT_DIR;
    fullpath += "/resources/";
    fullpath += path;

    // Get results
    std::ifstream stream( fullpath, std::ios::in );
    result = stream.good();
    stream.close();
    return fullpath;
}

} // namespace common
