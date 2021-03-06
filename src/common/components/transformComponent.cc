//
// Created by Eddie Hoyle on 10/12/17.
//

#include "transformComponent.hh"

#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/quaternion.hpp>
#include <iostream>

namespace common {

glm::mat4 look( TransformComponent* component ) {
    return look( component, component->getFront() );
}

glm::mat4 look( TransformComponent* component, const glm::vec3& point ) {
    const glm::vec3 position = component->getTranslate();
    const glm::vec3 front = component->getFront();
    const glm::vec3 up = component->getUp();
    return glm::lookAt( position, position + point, up );
}

glm::mat4 look( TransformComponent* source, TransformComponent* target ) {
    return glm::lookAt( source->getTranslate(), source->getTranslate() + target->getTranslate(), source->getUp() );
}

TransformComponent::TransformComponent()
        : m_pitch(),
          m_yaw(),
          m_roll(),
          m_front(),
          m_up(),
          m_right(),
          m_translate(),
          m_scale( 1, 1, 1 ),
          Component( ComponentType::Transform ) {
    update();
}

TransformComponent::TransformComponent( const glm::vec3& translate,
                                        const glm::vec3& rotate,
                                        const glm::vec3& scale )
        : m_pitch(),
          m_yaw(),
          m_roll(),
          m_front(),
          m_up(),
          m_right(),
          m_translate(),
          m_scale(),
          Component( ComponentType::Transform ) {
    setTranslate( translate.x, translate.y, translate.z );
    setRotate( rotate.x, rotate.y, rotate.z );
    setScale( scale.x, scale.y, scale.z );
}

void TransformComponent::setTranslate( float x, float y, float z ) {
    m_translate = glm::vec3( x, y, z );
}

void TransformComponent::setRotate( float x, float y, float z ) {

    // Store values
    m_pitch = x;
    m_yaw = y;
    m_roll = z;

    // Update vectors
    update();
}

void TransformComponent::setScale( float x, float y, float z ) {
    m_scale = glm::vec3( x, y, z );
}

void TransformComponent::translate( float x, float y, float z ) {
    m_translate += glm::vec3( x, y, z );
}

void TransformComponent::rotate( float x, float y, float z ) {
    setRotate( m_pitch + x, m_yaw + y, m_roll + z );
}

void TransformComponent::scale( float x, float y, float z ) {
    m_scale = glm::vec3( x, y, z );
}

void TransformComponent::moveForward( float value ) {
    m_translate += m_front * value;
}

void TransformComponent::moveRight( float value ) {
    m_translate += m_right * value;
}

void TransformComponent::moveUp( float value ) {
    m_translate += m_up * value;
}

glm::mat4 TransformComponent::getMatrix() const {
    glm::mat4 translate = glm::translate( glm::mat4(), m_translate );
    glm::mat4 rotateX = glm::rotate( glm::mat4(), m_pitch, glm::vec3( 1, 0, 0 ) );
    glm::mat4 rotateY = glm::rotate( glm::mat4(), m_yaw, glm::vec3( 0, 1, 0 ) );
    glm::mat4 rotateZ = glm::rotate( glm::mat4(), m_roll, glm::vec3( 0, 0, 1 ) );
    glm::mat4 rotate = rotateX * rotateY * rotateZ;
    glm::mat4 scale = glm::scale( glm::mat4(), m_scale );
    return translate * rotate * scale;
}

void TransformComponent::update() {

    // Compute front
    glm::vec3 front;
    front.x = static_cast< float >( cos( glm::radians( m_yaw ) ) * cos( glm::radians( m_pitch ) ) );
    front.y = static_cast< float >( sin( glm::radians( m_pitch ) ) );
    front.z = static_cast< float >( sin( glm::radians( m_yaw ) ) * cos( glm::radians( m_pitch ) ) );
    m_front = glm::normalize( front );

    // Compute right and up vector
    m_right = glm::normalize( glm::cross( m_front, glm::vec3( 0, 1, 0 ) ) );
    m_up = glm::normalize( glm::cross( m_right, m_front ) );
}

}