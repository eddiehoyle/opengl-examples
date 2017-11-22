//
// Created by Eddie Hoyle on 19/11/17.
//

#include "component.hh"

namespace common {

ComponentType AbstractComponent::type() {
    return ComponentType::None;
}

AbstractComponent::AbstractComponent( ComponentType type )
    : m_type( type ) {}

AbstractComponent::~AbstractComponent() {}

// ------------------------------------------------------------------------------------ //

InputMouseComponent::InputMouseComponent()
    : m_x( 0 ),
      m_y( 0 ),
      AbstractComponent( ComponentType::InputMouse ) {}

void InputMouseComponent::set( int x, int y ) {
    m_x = x;
    m_y = y;
}

int InputMouseComponent::x() const {
    return m_x;
}

int InputMouseComponent::y() const {
    return m_y;
}


// ------------------------------------------------------------------------------------ //


InputMoveComponent::InputMoveComponent()
    : m_forward( false ),
      m_backward( false ),
      m_left( false ),
      m_right( false ),
      AbstractComponent( ComponentType::InputMove ) {
}

bool InputMoveComponent::isForward() const {
    return m_forward;
}

bool InputMoveComponent::isBackward() const {
    return m_backward;
}

bool InputMoveComponent::isLeft() const {
    return m_left;
}

bool InputMoveComponent::isRight() const {
    return m_right;
}

void InputMoveComponent::setForward( bool state ) {
    m_forward = state;
}

void InputMoveComponent::setBackward( bool state ) {
    m_backward = state;
}

void InputMoveComponent::setLeft( bool state ) {
    m_left = state;
}

void InputMoveComponent::setRight( bool state ) {
    m_right = state;
}

}