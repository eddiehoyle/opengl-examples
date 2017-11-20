//
// Created by Eddie Hoyle on 20/11/17.
//

#ifndef OPENGL_EXAMPLES_CONTROLLER_HH
#define OPENGL_EXAMPLES_CONTROLLER_HH

#include "../scene/scene.hh"

namespace common {

class AbstractController {

public:
    virtual void update( double elapsed ) = 0;
    AbstractSceneObject* object();

protected:
    AbstractSceneObject* m_object;
};

class PlayerMoveController : public AbstractController {
    virtual void update( double elapsed );
};

}


#endif //OPENGL_EXAMPLES_CONTROLLER_HH
