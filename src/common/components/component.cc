//
// Created by Eddie Hoyle on 19/11/17.
//


#include "component.hh"

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
    : m_matrix(),
      Component( ComponentType::Transform ){
}

void TransformComponent::rotate( float x, float y, float z ) {
    m_matrix = glm::rotate( glm::mat4(), glm::radians( x ), glm::vec3( 1.0f, 0.0f, 0.0f ) );
    m_matrix = glm::rotate( glm::mat4(), glm::radians( y ), glm::vec3( 0.0f, 1.0f, 0.0f ) );
    m_matrix = glm::rotate( glm::mat4(), glm::radians( z ), glm::vec3( 0.0f, 0.0f, 1.0f ) );
}

const glm::mat4& TransformComponent::matrix() const {
    return m_matrix;
}

glm::vec3 TransformComponent::translation() const {
    return glm::vec3();
}

glm::vec3 TransformComponent::rotation() const {

    glm::mat4 matrix = m_matrix; // copy
    glm::vec3 euler;
    glm::extractEulerAngleXYZ( matrix, euler.x, euler.y, euler.z );
    return euler;
}

glm::vec3 TransformComponent::scale() const {
    return glm::vec3();
}


}