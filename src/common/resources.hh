//
// Created by Eddie Hoyle on 26/10/17.
//

#ifndef OPENGL_EXAMPLES_COMMON_RESOURCES_HH
#define OPENGL_EXAMPLES_COMMON_RESOURCES_HH

#include <string>

namespace common {

/// Look up a resource path
/// @param path Relative path to a file in 'resources/' directory.
/// @param[out] result If file exists or not.
/// @returns The full path used to find the resource.
std::string getResource( const std::string& path, bool& result );

} // namespace common

#endif //OPENGL_EXAMPLES_COMMON_RESOURCES_HH
