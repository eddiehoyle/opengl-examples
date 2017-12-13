//
// Created by Eddie Hoyle on 10/12/17.
//

#ifndef OPENGL_EXAMPLES_MOVECOMPONENT_HH
#define OPENGL_EXAMPLES_MOVECOMPONENT_HH


#include "component.hh"

namespace common {



class MoveStateComponent : public Component {

public:
    MoveStateComponent();

    void setForward( bool state );
    void setBackward( bool state );
    void setStrafeLeft( bool state );
    void setStrafeRight( bool state );
    void setTurningLeft( bool state );
    void setTurningRight( bool state );
    void setJump( bool state );

    bool isForward() const;
    bool isBackward() const;
    bool isStrafeLeft() const;
    bool isStrafeRight() const;
    bool isTurningLeft() const;
    bool isTurningRight() const;
    bool isJumping() const;

private:
    bool m_forward;
    bool m_backward;
    bool m_strafeLeft;
    bool m_strafeRight;
    bool m_turnLeft;
    bool m_turnRight;
    bool m_jumping;
};

}

#endif //OPENGL_EXAMPLES_MOVECOMPONENT_HH
