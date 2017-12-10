//
// Created by Eddie Hoyle on 10/12/17.
//

#ifndef OPENGL_EXAMPLES_BUNNY_HH
#define OPENGL_EXAMPLES_BUNNY_HH


#include "../common/scene/scene.hh"
#include "entity.hh"

class Bunny : public common::AbstractSceneObject {

public:

    /// Constructor
    Bunny();

    Entity& getEntity() const;

    /// Update
    virtual void update( double elapsed );
};



#endif //OPENGL_EXAMPLES_BUNNY_HH
