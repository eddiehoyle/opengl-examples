//
// Created by Eddie Hoyle on 14/11/17.
//

#ifndef OPENGL_EXAMPLES_OBSERVER_HH
#define OPENGL_EXAMPLES_OBSERVER_HH

#include "../input/defs.hh"

namespace common {

class Observer {

public:
    virtual void notify( KeyEvent event, KeyState state )=0;
};

class ObserverGame : public Observer {
public:
    ObserverGame();
    void notify( KeyEvent event, KeyState state );
    bool isQuit() const;

private:
    bool m_quit;
};

class ObserverMovement : public Observer {

public:
    ObserverMovement();
    void notify( KeyEvent event, KeyState state );

    bool isMovingForward() const;
    bool isMovingBackward() const;
    bool isTurningLeft() const;
    bool isTurningRight() const;

private:
    bool m_movingForward;
    bool m_movingBackward;
    bool m_turningLeft;
    bool m_turningRight;
};

}

#endif //OPENGL_EXAMPLES_OBSERVER_HH
