//
// Created by Eddie Hoyle on 29/10/17.
//

#include "camera.hh"
#include <iostream>
#include "components/component.hh"

namespace common {

static const float kMovementSpeed = 100.0;

Camera::Camera()
        : m_position(),
          m_front( 0.0f, 0.0f, -1.0f ),
          m_up( 0.0f, 1.0f, 0.0f ),
          m_right(),
          m_worldUp( 0.0f, 1.0f, 0.0f ),
          m_yaw(),
          m_pitch(),
          m_movementSpeed( kMovementSpeed ),
          m_mouseSensitivity( 0.2 ),
          m_zoom() {
    addComponent( new InputMoveComponent );
}

void Camera::setSpeed( double value ) {
    m_movementSpeed = std::max( 0.0, value );
}

void Camera::look( float x, float y ) {

    x *= m_mouseSensitivity;
    y *= m_mouseSensitivity;

    m_yaw += x;
    m_pitch += y;

    if ( m_pitch > 89.0f ) {
        m_pitch = 89.0f;
    }

    if ( m_pitch < -89.0f ) {
        m_pitch = -89.0f;
    }
}

void Camera::zoom( float value ) {

    if ( m_zoom >= 1.0f && m_zoom <= 45.0f )
        m_zoom -= value;

    if ( m_zoom <= 1.0f )
        m_zoom = 1.0f;

    if ( m_zoom >= 45.0f )
        m_zoom = 45.0f;
}

glm::mat4 Camera::view() const {
    return glm::lookAt( m_position, m_position + m_front, m_up );
}

glm::mat4 Camera::perspective() const {
    return glm::mat4();
}

void Camera::update( double elapsed ) {

    InputMoveComponent* component = getComponent< InputMoveComponent >();
    if ( component == nullptr ) {
        return;
    }

    double velocity = m_movementSpeed * elapsed;
    if ( component->isForward() ) {
        m_position += m_front * velocity;
    }
    if ( component->isBackward() ) {
        m_position -= m_front * velocity;
    }
    if ( component->isLeft() ) {
        m_position -= m_right * velocity;
    }
    if ( component->isRight() ) {
        m_position += m_right * velocity;
    }

    // Calculate the new Front vector
    glm::vec3 front;
    front.x = cos( glm::radians( m_yaw ) ) * cos( glm::radians( m_pitch ) );
    front.y = sin( glm::radians( m_pitch ) );
    front.z = sin( glm::radians( m_yaw ) ) * cos( glm::radians( m_pitch ) );
    m_front = glm::normalize( front );

    // Also re-calculate the Right and m_up vector
    m_right = glm::normalize( glm::cross( m_front, m_worldUp ) );
    m_up = glm::normalize( glm::cross( m_right, m_front ) );

}


} // namespace common;