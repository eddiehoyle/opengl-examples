//
// Created by Eddie Hoyle on 23/01/18.
//

#include <glm/gtc/matrix_transform.hpp>
#include "mousePicker.hh"
#include "../common/display.hh"
#include "../common/command/command.hh"
#include "../common/input/input.hh"

MousePicker::MousePicker( const Camera& camera, const glm::mat4& projection )
    : m_camera( camera ),
      m_projectionMatrix( projection ),
      m_viewMatrix( camera.view() ) {
}

glm::vec3 MousePicker::getCurrentRay() const {
    return m_currentRay;
}

void MousePicker::update() {
    m_viewMatrix = m_camera.view();
    m_currentRay = calculateMouseRay();
}

glm::vec3 MousePicker::calculateMouseRay() const {
    float mouseX = common::InputManager::instance()->mouse()->x();
    float mouseY = common::InputManager::instance()->mouse()->y();
    glm::vec2 normalizedCoords = getNormalizedDeviceCoords( mouseX, mouseY );
    glm::vec4 clipCoords( normalizedCoords.x,
                          normalizedCoords.y,
                          -1.0f,
                          1.0f );
    glm::vec4 eyeCoords = toEyeCoords( clipCoords );
    glm::vec3 worldRay = toWorldCoords( eyeCoords );
    return worldRay;
}

glm::vec2 MousePicker::getNormalizedDeviceCoords( float x, float y ) const {
    float _x = ( 2.0f * x ) / common::DisplayManager::instance()->width() - 1;
    float _y = ( 2.0f * y ) / common::DisplayManager::instance()->height() - 1;
    return glm::vec2( _x, -_y ); // Might need to use -y here?
}

glm::vec4 MousePicker::toEyeCoords( const glm::vec4& clipCoords ) const {
    glm::mat4 invertedProjection = glm::inverse( m_projectionMatrix );
    glm::vec4 eyeCoords = invertedProjection * clipCoords;
    return glm::vec4( eyeCoords.x, eyeCoords.y, -1.0f, 0.0f );
}

glm::vec3 MousePicker::toWorldCoords( const glm::vec4& eyeCoords ) const {
    glm::mat4 invertedView = glm::inverse( m_viewMatrix );
    glm::vec4 rayWorld = invertedView * eyeCoords;
    glm::vec3 mouseRay = glm::normalize( glm::vec3( rayWorld.x, rayWorld.y, rayWorld.z ) );
    return mouseRay;
}
