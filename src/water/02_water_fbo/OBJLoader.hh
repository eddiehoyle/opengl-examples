//
// Created by Eddie Hoyle on 30/10/17.
//

#ifndef OPENGL_EXAMPLES_17_OBJLOADER_HH
#define OPENGL_EXAMPLES_17_OBJLOADER_HH


#include <string>
#include "model.hh"
#include "loader.hh"

class OBJLoader {

public:
    static RawModel loadObjModel( const std::string& obj_path,
                                  Loader loader );
    static RawModel loadObjModel( const std::string& obj_path,
                                  const std::string& material_path,
                                  Loader loader );

    /// assimp loader
    ///
    /// Deprecated
//    static RawModel loadObjModel2( const std::string& obj_path, Loader loader );

};

#endif //OPENGL_EXAMPLES_17_OBJLOADER_HH
