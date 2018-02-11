//
// Created by Eddie Hoyle on 5/11/17.
//

#ifndef OPENGL_EXAMPLES_17_LIGHT_HH
#define OPENGL_EXAMPLES_17_LIGHT_HH


#include <glm/vec3.hpp>

class Light {

public:

    Light();
    explicit Light( const glm::vec3& position,
                    const glm::vec3& colour );
    explicit Light( const glm::vec3& position,
                    const glm::vec3& colour,
                    const glm::vec3& attenuation );

    glm::vec3 getPosition() const;

    glm::vec3 getAttenuation() const;

    void setPosition( const glm::vec3& position );

    glm::vec3 getColour() const;

    void setColour( const glm::vec3& colour );

private:
    glm::vec3 m_position;
    glm::vec3 m_colour;
    glm::vec3 m_attenuation;
};

#endif //OPENGL_EXAMPLES_17_LIGHT_HH
