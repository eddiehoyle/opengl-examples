//
// Created by Eddie Hoyle on 30/10/17.
//

#ifndef OPENGL_EXAMPLES_OBJLOADER_HH
#define OPENGL_EXAMPLES_OBJLOADER_HH


#include <string>
#include "model.hh"
#include "loader.hh"

class OBJLoader {

public:
    static Model loadObjModel( const std::string& path,
                               Loader loader );
};

#endif //OPENGL_EXAMPLES_OBJLOADER_HH
