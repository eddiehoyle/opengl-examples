//
// Created by Eddie Hoyle on 6/12/17.
//

#ifndef OPENGL_EXAMPLES_INPUTCONTROLLER_HH
#define OPENGL_EXAMPLES_INPUTCONTROLLER_HH

#include "controller.hh"

namespace common {

class FpsController : public AbstractController {
public:
    FpsController( AbstractSceneObject* object );
    virtual void update( double elapsed );

private:
    void handleMove( InputCommand* command );
    void handleMouseMove();
};

}

#endif //OPENGL_EXAMPLES_INPUTCONTROLLER_HH
