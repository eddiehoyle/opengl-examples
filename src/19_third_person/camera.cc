//
// Created by Eddie Hoyle on 29/10/17.
//

#include "camera.hh"
#include "texture.hh"
#include "../common/command/command.hh"
#include "../common/input/input.hh"
#include <glm/glm.hpp>
#include <glm/ext.hpp>
#include <iostream>

glm::mat4 Camera::createViewMatrix( Camera *camera ) {
    return glm::inverse( camera->matrix() );
}

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
    calculateZoom();
    calculatePitch();
    calculateAngleAroundPlayer();
    float horizontalDistance = calculateHorizontalDistance();
    float verticalDistance = calculateVerticalDistance();
    calculateCameraPosition( horizontalDistance, verticalDistance );
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
//    glm::mat4 translate = glm::translate( glm::mat4(), m_position );
//    glm::mat4 rotateX = glm::rotate( glm::mat4(), m_pitch, glm::vec3( 1, 0, 0 ) );
//    glm::mat4 rotateY = glm::rotate( glm::mat4(), m_yaw, glm::vec3( 0, 1, 0 ) );
//    glm::mat4 rotateZ = glm::rotate( glm::mat4(), m_roll, glm::vec3( 0, 0, 1 ) );
//    glm::mat4 rotate = rotateX * rotateY * rotateZ;
//    glm::mat4 scale = glm::scale( glm::mat4(), glm::vec3( 1 ) );
//    return translate * rotate * scale;

    // ---------------------------------------------------------------------------------------------------

//    vDir->X = sin(yaw);
//    vDir->Y = -(sin(pitch)*cos(yaw));
//    vDir->Z = -(cos(pitch)*cos(yaw));

//     Compute front
//    glm::vec3 front;
//    front.x = static_cast< float >( glm::sin( glm::radians( m_yaw ) ) );
//    front.y = static_cast< float >( -glm::sin( glm::radians( m_pitch ) * glm::cos( glm::radians( m_yaw ) ) ) );
//    front.z = static_cast< float >( -glm::cos( glm::radians( m_pitch ) * glm::cos( glm::radians( m_yaw ) ) ) );
//    front = glm::normalize( front );
//
////     Compute right and up vector
//    glm::vec3 right = glm::normalize( glm::cross( front, glm::vec3( 0, 1, 0 ) ) );
//    glm::vec3 up = glm::normalize( glm::cross( right, front ) );
//
//    std::cerr << glm::to_string( m_position ) << std::endl;
//
//    return glm::lookAt( m_position, m_position + front, up );

    // ---------------------------------------------------------------------------------------------------

    glm::mat4 viewMatrix;
    viewMatrix = glm::rotate( viewMatrix, glm::radians( m_pitch ), glm::vec3( 1, 0, 0 ) );
    viewMatrix = glm::rotate( viewMatrix, glm::radians( m_yaw ), glm::vec3( 0, 1, 0 ) );
    viewMatrix = glm::translate( viewMatrix, m_position );
    return viewMatrix;

//    Matrix4f viewMatrix = new Matrix4f();
//    viewMatrix.setIdentity();
//    Matrix4f.rotate((float) Math.toRadians(camera.getPitch()), new Vector3f(1, 0, 0), viewMatrix, viewMatrix);
//    Matrix4f.rotate((float) Math.toRadians(camera.getYaw()), new Vector3f(0, 1, 0), viewMatrix, viewMatrix);
//    Vector3f cameraPos = camera.getPosition();
//    Vector3f negativeCameraPos = new Vector3f(-cameraPos.x,-cameraPos.y,-cameraPos.z);
//    Matrix4f.translate(negativeCameraPos, viewMatrix, viewMatrix);
//    return viewMatrix;
}

glm::mat4 Camera::view() const {
    return glm::inverse( matrix() );
}

void Camera::calculateZoom() {
    using namespace common;
    const ZoomCommands& commands = InputManager::instance()->zoomCommands();
    for ( ZoomCommand* command : commands ) {
        m_distanceFromPlayer += command->value();
    }
//    std::cerr << "m_distanceFromPlayer=" << m_distanceFromPlayer << std::endl;
}

void Camera::calculatePitch() {
    using namespace common;
    const InputCommands& commands = InputManager::instance()->commands();

    for ( InputCommand* command : commands ) {
        if ( command->action() == InputAction::RMB ) {
            m_pitchActive = command->state() == InputState::Press;
            break;
        }
    }
    if ( m_pitchActive ) {
        double delta = InputManager::instance()->mouse()->y() - InputManager::instance()->mouse()->prevY();
        m_pitch -= ( delta * 0.1 );
    }
}

void Camera::calculateAngleAroundPlayer() {
    using namespace common;
    const InputCommands& commands = InputManager::instance()->commands();

    for ( InputCommand* command : commands ) {
        if ( command->action() == InputAction::LMB ) {
            m_yawActive = command->state() == InputState::Press;
            break;
        }
    }
    if ( m_yawActive ) {
        double delta = InputManager::instance()->mouse()->x() - InputManager::instance()->mouse()->prevX();
        m_angleAroundPlayer -= delta;
    }
}

float Camera::calculateHorizontalDistance() {
    return ( float )m_distanceFromPlayer * glm::cos( glm::radians( m_pitch ) );
}

float Camera::calculateVerticalDistance() {
    return ( float )m_distanceFromPlayer * glm::sin( glm::radians( m_pitch ) );
}

void Camera::calculateCameraPosition( float horizontalDistance, float verticalDistance ) {
    float theta = m_player->getRotation().y + m_angleAroundPlayer;
    float offsetX = horizontalDistance * glm::sin( glm::radians( theta ) );
    float offsetZ = horizontalDistance * glm::cos( glm::radians( theta ) );
    m_position.x = m_player->getPosition().x - offsetX;
    m_position.y = m_player->getPosition().y + verticalDistance;
    m_position.z = m_player->getPosition().z - offsetZ;

    std::cerr << __func__ << " : m_player position=" << glm::to_string( m_player->getPosition() ) << std::endl;



}
