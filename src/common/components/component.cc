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

InputMoveComponent::InputMoveComponent()
        : m_forward( false ),
          m_backward( false ),
          m_left( false ),
          m_right( false ),
          Component( ComponentType::MoveState ) {
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

// ------------------------------------------------------------------------------------ //

TransformComponent::TransformComponent()
        : m_translate(),
          m_rotate(),
          m_scale( 1, 1, 1 ),
          Component( ComponentType::Transform ) {
}

void TransformComponent::setTranslate( float x, float y, float z ) {
    m_translate = glm::vec3( x, y, z );
}

void TransformComponent::setRotate( float x, float y, float z ) {
    m_rotate = glm::quat( glm::radians( glm::vec3( x, y, z ) ) );
}

void TransformComponent::translate( float x, float y, float z ) {
    m_translate += glm::vec3( x, y, z );
}

void TransformComponent::rotate( const glm::vec3& vec ) {
    // https://github.com/scanberg/particle-skinning/blob/0b8cff3c3916a50da1e1047f42a863be04d80029/src/Entity.cpp
    // Convert 'xyz' to 'zxy'
    glm::vec3 zxy( vec.z, vec.x, vec.y );
    glm::mat3 rotation = glm::orientate3( glm::radians( zxy ) );
    m_rotate = ( m_rotate * glm::quat_cast( rotation ) );

}

glm::vec3 TransformComponent::translation() const {
    return m_translate;
}

glm::vec3 TransformComponent::rotation() const {
//    std::cerr << "TransformComponent::" << __func__ << " : rotation=" << glm::to_string( m_rotate ) << std::endl;
    return glm::degrees( glm::eulerAngles( m_rotate ) );
}

glm::mat4 TransformComponent::matrix() const {
    glm::mat4 translate = glm::translate( glm::mat4(), m_translate );
    glm::mat4 rotate = glm::mat4_cast( m_rotate );
    glm::mat4 scale = glm::scale(glm::mat4(), m_scale);
    return translate * rotate * scale;
}

}