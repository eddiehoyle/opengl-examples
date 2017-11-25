//
// Created by Eddie Hoyle on 20/11/17.
//

#ifndef OPENGL_EXAMPLES_CONTROLLER_HH
#define OPENGL_EXAMPLES_CONTROLLER_HH

#include "../scene/scene.hh"

namespace common {

// Forward decl
class InputCommand;

class AbstractController {

public:
    virtual void update( double elapsed ) = 0;
    AbstractSceneObject* object();

protected:
    explicit AbstractController( AbstractSceneObject* object );
    AbstractSceneObject* m_object;
};

class InputController : public AbstractController {
public:
    InputController( AbstractSceneObject* object );
    virtual void update( double elapsed );

private:
    void handleMove( InputCommand* command );
    void handleMouse( InputCommand* command );
    void handleMouseMove();
};

}


#endif //OPENGL_EXAMPLES_CONTROLLER_HH
