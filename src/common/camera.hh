//
// Created by Eddie Hoyle on 29/10/17.
//

#ifndef OPENGL_EXAMPLES_CAMERA_HH
#define OPENGL_EXAMPLES_CAMERA_HH

#include <glm/vec3.hpp>
#include <glm/detail/type_mat.hpp>

#include <glm/ext.hpp>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/string_cast.hpp>
#include <iostream>
#include <vector>

#include "scene/scene.hh"

namespace common {


class Camera : public common::AbstractSceneObject {

public:

    /// Constructor
    Camera();

    void setSpeed( double value );

    /// Camera control
    void look( float x, float y );
    void zoom( float value );

    /// Update
    virtual void update( double elapsed );

    /// View matrix
    glm::mat4 view() const;

    /// Perspective matrix
    glm::mat4 perspective() const;

private:
    void processMove( double elapsed );
    void processAim( double elapsed );

private:

//    /// Vectors
//    glm::vec3 m_position;
//    glm::vec3 m_front;
//    glm::vec3 m_up;
//    glm::vec3 m_right;
//    glm::vec3 m_worldUp;
//
//    /// Euler Angles
//    float m_yaw;
//    float m_pitch;

    /// Camera options
    float m_movementSpeed;
    float m_mouseSensitivity;
    float m_zoom;
};
} // namespace common

#endif //OPENGL_EXAMPLES_CAMERA_HH
