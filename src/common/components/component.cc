//
// Created by Eddie Hoyle on 19/11/17.
//

#include "component.hh"

namespace common {

MoveComponent::MoveComponent()
    : m_forward( false ),
      m_backward( false ),
      m_left( false ),
      m_right( false ),
      AbstractComponent( ComponentType::kMove ) {
}

bool MoveComponent::isForward() const {
    return m_forward;
}

bool MoveComponent::isBackward() const {
    return m_backward;
}

bool MoveComponent::isLeft() const {
    return m_left;
}

bool MoveComponent::isRight() const {
    return m_right;
}

void MoveComponent::setForward( bool state ) {
    m_forward = state;
}

void MoveComponent::setBackward( bool state ) {
    m_backward = state;
}

void MoveComponent::setLeft( bool state ) {
    m_left = state;
}

void MoveComponent::setRight( bool state ) {
    m_right = state;
}

}