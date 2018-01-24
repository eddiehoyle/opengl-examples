//
// Created by Eddie Hoyle on 23/01/18.
//

#ifndef OPENGL_EXAMPLES_MOUSEPICKER_HH
#define OPENGL_EXAMPLES_MOUSEPICKER_HH


#include <glm/glm.hpp>
#include "camera.hh"

class MousePicker {
public:
    MousePicker( Camera* camera, const glm::mat4& projection );
    glm::vec3 getCurrentRay() const;
    void update();

private:
    glm::vec3 calculateMouseRay() const;
    glm::vec2 getNormalizedDeviceCoords( float x, float y ) const;
    glm::vec4 toEyeCoords( const glm::vec4& clipCoords ) const;
    glm::vec3 toWorldCoords( const glm::vec4& eyeCoords ) const;

private:
    glm::vec3 m_currentRay;
    glm::mat4 m_projectionMatrix;
    glm::mat4 m_viewMatrix;
    Camera* m_camera;
};


#endif //OPENGL_EXAMPLES_MOUSEPICKER_HH
