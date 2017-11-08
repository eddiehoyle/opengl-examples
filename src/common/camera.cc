//
// Created by Eddie Hoyle on 29/10/17.
//

#include "camera.hh"
#include <glm/glm.hpp>
#include <glm/ext.hpp>

namespace common {

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
//    glm::mat4 camera = glm::lookAt(
//            m_position, // Camera is at (4,3,3), in World Space
//            glm::vec3( 1, 0, 0 ),
//            glm::vec3(0,1,0)  // Head is up (set to 0,-1,0 to look upside-down)
//    );
    glm::mat4 camera = glm::translate( glm::mat4(), m_position );
    return camera;
}

} // namespace common;