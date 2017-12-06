//
// Created by Eddie Hoyle on 6/12/17.
//

#ifndef OPENGL_EXAMPLES_PLAYER_HH
#define OPENGL_EXAMPLES_PLAYER_HH


#include "../common/scene/scene.hh"

namespace common {

class Player : public common::AbstractSceneObject {

public:

    /// Constructor
    Player();


    /// Update
    virtual void update( double elapsed );

};

}

#endif //OPENGL_EXAMPLES_PLAYER_HH
