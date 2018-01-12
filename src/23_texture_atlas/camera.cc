//
// Created by Eddie Hoyle on 29/10/17.
//

#include "camera.hh"
#include "../common/command/command.hh"
#include "../common/input/input.hh"
#include "../common/display.hh"
#include <glm/glm.hpp>
#include <glm/ext.hpp>
#include <iostream>

static const float SENSITIVITY = 0.5f;

Camera::Camera()
        : m_position( 0, 0, 0 ),
          m_pitch( 0 ),
          m_yaw( 0 ),
          m_roll( 0 ),
          m_distanceFromPlayer( 50 ),
          m_angleAroundPlayer( 0 ),
          m_player( new Player( TexturedModel( Model( 0, 0 ), ModelTexture( 0 ) ),
                            glm::vec3(),
                            glm::vec3(),
                            1 ) ) {
}

Camera::Camera( Player* player )
        : m_position( 0, 0, 0 ),
          m_pitch( 0 ),
          m_yaw( 0 ),
          m_roll( 0 ),
          m_distanceFromPlayer( 50 ),
          m_angleAroundPlayer( 0 ),
          m_player( player ) {
}

void Camera::setPlayer( Player* player ) {
    m_player = player;
}

void Camera::move() {

    if ( !common::DisplayManager::instance()->isFocused() ) {
        return;
    }

    calculateZoom();
    calculatePitch();
    calculateAngleAroundPlayer();
    float horizontalDistance = calculateHorizontalDistance();
    float verticalDistance = calculateVerticalDistance();
    calculateCameraPosition( horizontalDistance, verticalDistance );
    m_yaw = 180.0f - ( m_player->getRotation().y + m_angleAroundPlayer );
}

void Camera::setPosition( const glm::vec3& position ) {
    m_position = position;
}

void Camera::setPitch( float pitch ) {
    m_pitch = pitch;
}

void Camera::setYaw( float yaw ) {
    m_yaw = yaw;
}

void Camera::setRoll( float roll ) {
    m_roll = roll;
}

glm::vec3 Camera::position() const {
    return m_position;
}

float Camera::pitch() const {
    return m_pitch;
}

float Camera::yaw() const {
    return m_yaw;
}

float Camera::roll() const {
    return m_roll;
}

glm::mat4 Camera::matrix() const {
    return glm::mat4();
}

glm::mat4 Camera::view() const {
    glm::mat4 view;
    view = glm::rotate( view, glm::radians( m_pitch ), glm::vec3( 1, 0, 0 ) );
    view = glm::rotate( view, glm::radians( m_yaw ), glm::vec3( 0, 1, 0 ) );
    view = glm::translate( view, -m_position ); // important
    return view;
}

void Camera::calculateZoom() {
    using namespace common;
    const ZoomCommands& commands = InputManager::instance()->zoomCommands();
    for ( ZoomCommand* command : commands ) {
        m_distanceFromPlayer -= command->value();
    }
}

void Camera::calculatePitch() {
    using namespace common;
    double delta = InputManager::instance()->mouse()->y() - InputManager::instance()->mouse()->prevY();
    delta *= SENSITIVITY;
    if ( m_pitch - delta < 0 ) {
        m_pitch = 0.0;
    } else if ( m_pitch - delta > 90 ) {
        m_pitch = 90.0;
    } else {
        m_pitch -= delta;
    }
}

void Camera::calculateAngleAroundPlayer() {
    using namespace common;
    double delta = InputManager::instance()->mouse()->x() - InputManager::instance()->mouse()->prevX();
    delta *= SENSITIVITY;
    m_angleAroundPlayer += delta;
}

float Camera::calculateHorizontalDistance() {
    return ( float )m_distanceFromPlayer * std::cos( glm::radians( m_pitch ) );
}

float Camera::calculateVerticalDistance() {
    return ( float )m_distanceFromPlayer * std::sin( glm::radians( m_pitch ) );
}

void Camera::calculateCameraPosition( float horizontalDistance, float verticalDistance ) {
    float theta = m_player->getRotation().y + m_angleAroundPlayer;
    float offsetX = horizontalDistance * glm::sin( glm::radians( theta ) );
    float offsetZ = horizontalDistance * glm::cos( glm::radians( theta ) );
    m_position.x = m_player->getPosition().x - offsetX;
    m_position.z = m_player->getPosition().z - offsetZ;
    m_position.y = m_player->getPosition().y + 3 + verticalDistance;
}
