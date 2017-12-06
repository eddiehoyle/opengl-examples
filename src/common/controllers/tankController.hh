//
// Created by Eddie Hoyle on 6/12/17.
//

#ifndef OPENGL_EXAMPLES_TANKCONTROLLER_HH
#define OPENGL_EXAMPLES_TANKCONTROLLER_HH

#include "controller.hh"

namespace common {


class TankController : public AbstractController {
public:
    TankController( AbstractSceneObject* object );
    virtual void update( double elapsed );

private:
    void handleMove( InputCommand* command );

private:
    float m_prevX;
    float m_prevY;
};


}


#endif //OPENGL_EXAMPLES_TANKCONTROLLER_HH
