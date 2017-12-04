//
// Created by Eddie Hoyle on 29/10/17.
//

#include "camera.hh"
#include <iostream>
#include "components/component.hh"

namespace common {

static const float kMovementSpeed = 100.0;

Camera::Camera()
        : m_movementSpeed( kMovementSpeed ),
          m_mouseSensitivity( 0.2 ),
          m_zoom() {
    addComponent( new MoveStateComponent );
    addComponent( new TransformComponent );
}

void Camera::setSpeed( double value ) {
    m_movementSpeed = std::max( 0.0, value );
}

void Camera::update( double elapsed ) {

    Component *moveStatecomponent = getComponent( ComponentType::MoveState );
    assert( moveStatecomponent );

    MoveStateComponent *moveComponent = moveStatecomponent->asType< MoveStateComponent >();
    assert( moveComponent );

    Component *transformBaseComponent = getComponent( ComponentType::Transform );
    assert( transformBaseComponent );

    TransformComponent *transformComponent = transformBaseComponent->asType< TransformComponent >();
    assert( transformComponent );


    double velocity = m_movementSpeed * elapsed;
    if ( moveComponent->isForward() ) {
        transformComponent->moveForward( velocity );
    }
    if ( moveComponent->isBackward() ) {
        transformComponent->moveForward( -velocity );
    }
    if ( moveComponent->isLeft() ) {
        transformComponent->moveRight( -velocity );
    }
    if ( moveComponent->isRight() ) {
        transformComponent->moveRight( velocity );
    }

}

glm::mat4 Camera::view() const {

    Component* component = getComponent( ComponentType::Transform );
    assert( component );

    TransformComponent* transformComponent = component->asType< TransformComponent >();
    assert( transformComponent );

    return common::look( transformComponent );
}

glm::mat4 Camera::perspective() const {
    return glm::mat4();
}


} // namespace common;