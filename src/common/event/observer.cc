//
// Created by Eddie Hoyle on 14/11/17.
//

#include "observer.hh"

namespace common {

ObserverGame::ObserverGame()
    : m_quit( false ) {
}

void ObserverGame::notify( KeyEvent event, KeyState state ) {

    switch ( state ) {
        case KeyState::kPress:
            switch ( event ) {
                case KeyEvent::kCancel:
                    m_quit = true;
                    break;
                default:
                    break;
            }
            break;
        case KeyState::kRelease:
            switch ( event ) {
                case KeyEvent::kCancel:
                    m_quit = false;
                default:
                    break;
            }
            break;
        default:
            break;
    }
}

bool ObserverGame::isQuit() const {
    return m_quit;
}

ObserverMovement::ObserverMovement()
        : m_movingForward( false ),
          m_movingBackward( false ),
          m_turningLeft( false ),
          m_turningRight( false ) {}

void ObserverMovement::notify( KeyEvent event, KeyState state ) {

    switch ( state ) {
        case KeyState::kPress:
            switch ( event ) {
                case KeyEvent::kForward:
                    m_movingForward = true;
                    break;
                case KeyEvent::kBackward:
                    m_movingBackward = true;
                    break;
                case KeyEvent::kTurnLeft:
                    m_turningLeft = true;
                    break;
                case KeyEvent::kTurnRight:
                    m_turningRight = true;
                    break;
                default:
                    break;
            }
            break;
        case KeyState::kRelease:
            switch ( event ) {
                case KeyEvent::kForward:
                    m_movingForward = false;
                    break;
                case KeyEvent::kBackward:
                    m_movingBackward = false;
                    break;
                case KeyEvent::kTurnLeft:
                    m_turningLeft = false;
                    break;
                case KeyEvent::kTurnRight:
                    m_turningRight = false;
                    break;
                default:
                    break;
            }
            break;
        default:
            break;
    }
}

bool ObserverMovement::isMovingForward() const {
    return m_movingForward;
}

bool ObserverMovement::isMovingBackward() const {
    return m_movingBackward;
}

bool ObserverMovement::isTurningLeft() const {
    return m_turningLeft;
}

bool ObserverMovement::isTurningRight() const {
    return m_turningRight;
}

}

