//
// Created by Eddie Hoyle on 17/12/17.
//

#ifndef OPENGL_EXAMPLES_TPSCONTROLLER_HH
#define OPENGL_EXAMPLES_TPSCONTROLLER_HH

#include "bunny.hh"
#include "../common/scene/camera.hh"
#include "../common/command/command.hh"


class ThirdPersonController {
public:
    ThirdPersonController( Bunny* player, common::Camera* camera );
    virtual void update( double elapsed );

private:
    void handleCommand( common::InputCommand *command );
    void handleMouseMove();

    Bunny* m_player;
    common::Camera* m_camera;

    bool m_mouseMoveEnabled;
};


#endif //OPENGL_EXAMPLES_TPSCONTROLLER_HH
