//
// Created by Eddie Hoyle on 29/10/17.
//

#include "camera.hh"
#include <glm/glm.hpp>
#include <glm/ext.hpp>

glm::mat4 Camera::createViewMatrix( Camera* camera ) {
    return glm::inverse( camera->matrix() );
}

void Camera::move( const glm::vec3& position ) {
    m_position += position;
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
    glm::mat4 translate = glm::translate( glm::mat4(), m_position );
    glm::mat4 rotateX = glm::rotate( glm::mat4(), m_pitch, glm::vec3( 1, 0, 0 ) );
    glm::mat4 rotateY = glm::rotate( glm::mat4(), m_yaw, glm::vec3( 0, 1, 0 ) );
    glm::mat4 rotateZ = glm::rotate( glm::mat4(), m_roll, glm::vec3( 0, 0, 1 ) );
    glm::mat4 rotate = rotateX * rotateY * rotateZ;
    glm::mat4 scale = glm::scale( glm::mat4(), glm::vec3( 1 ) );
    return translate * rotate * scale;
}

glm::mat4 Camera::view() const {
    return glm::inverse( matrix() );
}

