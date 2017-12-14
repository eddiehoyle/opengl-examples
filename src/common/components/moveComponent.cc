//
// Created by Eddie Hoyle on 10/12/17.
//

#include "moveComponent.hh"

namespace common {

MoveStateComponent::MoveStateComponent()
        : m_forward( false ),
          m_backward( false ),
          m_strafeLeft( false ),
          m_strafeRight( false ),
          m_turnLeft( false ),
          m_turnRight( false ),
          m_jumping( false ),
          Component( ComponentType::MoveState ) {
}

bool MoveStateComponent::isForward() const {
    return m_forward;
}

bool MoveStateComponent::isBackward() const {
    return m_backward;
}

bool MoveStateComponent::isStrafeLeft() const {
    return m_strafeLeft;
}

bool MoveStateComponent::isStrafeRight() const {
    return m_strafeRight;
}

bool MoveStateComponent::isTurningLeft() const {
    return m_turnLeft;
}

bool MoveStateComponent::isTurningRight() const {
    return m_turnRight;
}

void MoveStateComponent::setForward( bool state ) {
    m_forward = state;
}

void MoveStateComponent::setBackward( bool state ) {
    m_backward = state;
}

void MoveStateComponent::setStrafeLeft( bool state ) {
    m_strafeLeft = state;
}

void MoveStateComponent::setStrafeRight( bool state ) {
    m_strafeRight = state;
}

void MoveStateComponent::setTurningLeft( bool state ) {
    m_turnLeft = state;
}

void MoveStateComponent::setTurningRight( bool state ) {
    m_turnRight = state;
}

void MoveStateComponent::setJump( bool state ) {
    m_jumping = state;
}

bool MoveStateComponent::isJumping() const {
    return m_jumping;
}

}