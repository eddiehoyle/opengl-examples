//
// Created by Eddie Hoyle on 29/10/17.
//

#ifndef OPENGL_EXAMPLES_CAMERA_HH
#define OPENGL_EXAMPLES_CAMERA_HH

#include <glm/vec3.hpp>
#include <glm/detail/type_mat.hpp>

namespace common {

class Camera {

public:
    static glm::mat4 createViewMatrix( Camera* camera );

public:
    void move( const glm::vec3& position );
    void setPosition( const glm::vec3& position );
    void setPitch( float pitch );
    void setYaw( float yaw );
    void setRoll( float roll );

    glm::vec3 position() const;
    float pitch() const;
    float yaw() const;
    float roll() const;

    glm::mat4 matrix() const;

private:
    glm::vec3 m_position;
    float m_pitch;
    float m_yaw;
    float m_roll;
};

} // namespace common

#endif //OPENGL_EXAMPLES_CAMERA_HH
