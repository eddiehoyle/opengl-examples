//
// Created by Eddie Hoyle on 29/10/17.
//

#include "camera.hh"
#include <glm/glm.hpp>
#include <glm/ext.hpp>
#include <iostream>

#include "event/observer.hh"
#include "input/input.hh"

const float kMoveSpeed = 1.0;
const float kTurnSpeed = 0.1;

namespace common {

Camera::Camera()
        : m_observer( nullptr ),
          m_position(),
          m_pitch(),
          m_yaw(),
          m_roll() {
    m_observer = new ObserverMovement;
    InputManager::instance()->addObserver( m_observer );
}

Camera::~Camera() {
    InputManager::instance()->removeObserver( m_observer );
    delete m_observer;
}

void Camera::update() {
    if ( m_observer->isMovingForward() ) {
        move( glm::vec3( 0.0f, 0.0, kMoveSpeed ) );
    }
    if ( m_observer->isMovingBackward() ) {
        move( glm::vec3( 0.0f, 0.0, -kMoveSpeed ) );
    }
    if ( m_observer->isTurningLeft() ) {
        setYaw( yaw() + -kTurnSpeed );
    }
    if ( m_observer->isTurningRight() ) {
        setYaw( yaw() + kTurnSpeed );
    }
}

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

    glm::mat4 camera;
    glm::mat4 translate = glm::translate( camera, m_position );
    camera = glm::rotate( translate, glm::radians( m_pitch ), glm::vec3( 1, 0, 0 ) );
    camera = glm::rotate( translate, glm::radians( m_yaw ), glm::vec3( 0, 1, 0 ) );
    return camera;
}

//
//namespace {
//float pan_speed = 0.1f;
//float roll_speed = 0.1f;
//float rotation_speed = 0.05f;
//float zoom_speed = 0.1f;
//};
//
//void Camera2::yaw(float dir) {
//    rotate *= glm::rotate(rotation_speed * dir, up_);
//    glm::vec3 eye(rotate * glm::vec4(eye_, 1));
//    look_ = glm::normalize(middle_ - eye);
//    right_ = glm::normalize(glm::cross(look_, up_));
//    up_ = glm::normalize(glm::cross(right_, look_));
//}
//
//void Camera2::pitch(float dir) {
//    rotate = glm::rotate(rotation_speed*dir, right_) * rotate;
//    glm::vec3 eye(rotate * glm::vec4(eye_, 1));
//    look_ = glm::normalize(middle_ - eye);
//    right_ = glm::normalize(glm::cross(look_, up_));
//    up_ = glm::normalize(glm::cross(right_, look_));
//}
//
//void Camera2::roll(float dir) {
//    glm::mat4 roll_rotate = glm::rotate(dir * roll_speed, look_);
//    right_ = glm::normalize(glm::vec3(roll_rotate * glm::vec4(right_, 0.0f)));
//    up_ = glm::normalize(glm::vec3(roll_rotate * glm::vec4(up_, 0.0f)));
//}
//
//void Camera2::trans(glm::vec2 dir) {
//    translate *= glm::translate((dir.y * up_ + dir.x * right_) * pan_speed);
//}
//
//void Camera2::zoom(float dir) {
//    camera_distance_ += zoom_speed * dir;
//    eye_ = glm::vec3(0.0f, 0.0f, camera_distance_);
//}
//
//glm::mat4 Camera2::get_view_matrix() const {
//    glm::vec3 newEye(translate * rotate * glm::vec4(eye_, 1));
//    glm::vec3 newmiddle(translate * rotate * glm::vec4(middle_, 1));
//
//    glm::vec3 Z = glm::normalize(newEye - newmiddle);
//    glm::vec3 X = glm::cross(up_, Z);
//    glm::vec3 Y = glm::normalize(glm::cross(Z, X));
//    X = glm::normalize(X);
//
//    glm::mat4 eye(1.0f);
//    eye[0] = glm::vec4(X.x, Y.x, Z.x, 0);
//    eye[1] = glm::vec4(X.y, Y.y, Z.y, 0);
//    eye[2] = glm::vec4(X.z, Y.z, Z.z, 0);
//    eye[3] = glm::vec4(glm::dot(-X, newEye), glm::dot(-Y, newEye), glm::dot(-Z, newEye), 1);
//
//    return eye;
//}

} // namespace common;