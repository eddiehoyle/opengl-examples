//
// Created by Eddie Hoyle on 5/11/17.
//

#include "light.hh"

Light::Light()
        : m_position(),
          m_colour() {}

Light::Light( const glm::vec3& position,
              const glm::vec3& colour )
        : m_position( position ),
          m_colour( colour ),
          m_attenuation( 1, 0, 0 ) {
}

Light::Light( const glm::vec3& position,
              const glm::vec3& colour,
              const glm::vec3& attenuation )
        : m_position( position ),
          m_colour( colour ),
          m_attenuation( attenuation ) {
}

glm::vec3 Light::getAttenuation() const {
    return m_attenuation;
}

glm::vec3 Light::getPosition() const {
    return m_position;
}

void Light::setPosition( const glm::vec3& position ) {
    m_position = position;
}

glm::vec3 Light::getColour() const {
    return m_colour;
}

void Light::setColour( const glm::vec3& colour ) {
    m_colour = colour;
}
