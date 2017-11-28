//
// Created by Eddie Hoyle on 19/11/17.
//


#include "component.hh"
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/quaternion.hpp>
#include <iostream>

namespace common {

ComponentType Component::type() {
    return m_type;
}

Component::Component( ComponentType type )
        : m_type( type ) {}

Component::~Component() {}

// ------------------------------------------------------------------------------------ //

InputMouseComponent::InputMouseComponent()
        : m_x( 0 ),
          m_y( 0 ),
          Component( ComponentType::InputMouse ) {}

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

MoveStateComponent::MoveStateComponent()
        : m_forward( false ),
          m_backward( false ),
          m_left( false ),
          m_right( false ),
          Component( ComponentType::MoveState ) {
}

bool MoveStateComponent::isForward() const {
    return m_forward;
}

bool MoveStateComponent::isBackward() const {
    return m_backward;
}

bool MoveStateComponent::isLeft() const {
    return m_left;
}

bool MoveStateComponent::isRight() const {
    return m_right;
}

void MoveStateComponent::setForward( bool state ) {
    m_forward = state;
}

void MoveStateComponent::setBackward( bool state ) {
    m_backward = state;
}

void MoveStateComponent::setLeft( bool state ) {
    m_left = state;
}

void MoveStateComponent::setRight( bool state ) {
    m_right = state;
}

// ------------------------------------------------------------------------------------ //

TransformComponent::TransformComponent()
        : m_transform(),
          Component( ComponentType::Transform ) {
}

void TransformComponent::setTranslate( float x, float y, float z ) {
    m_transform.setTranslate( x, y, z );
}

void TransformComponent::setRotate( float x, float y, float z ) {
    m_transform.setRotate( x, y, z );
}

void TransformComponent::translate( float x, float y, float z ) {
    m_transform.translate( x, y, z );
}

void TransformComponent::rotate( float x, float y, float z ) {
    m_transform.rotate( x, y, z );
}

//glm::vec3 TransformComponent::translation() const {
//    return m_transform.getTranslate();
//}
//
//glm::vec3 TransformComponent::rotation() const {
//    return m_transform.getRotate();
//}
//
//glm::mat4 TransformComponent::matrix() const {
//    return m_transform.getMatrix();
//}

}