//
// Created by Eddie Hoyle on 10/12/17.
//

#ifndef OPENGL_EXAMPLES_TRANSFORMCOMPONENT_HH
#define OPENGL_EXAMPLES_TRANSFORMCOMPONENT_HH

#include <glm/glm.hpp>
#include <glm/ext.hpp>
#include <glm/gtx/matrix_decompose.hpp>
#include "component.hh"

namespace common {

class TransformComponent;

glm::mat4 look( TransformComponent* component );

glm::mat4 look( TransformComponent* component, const glm::vec3& point );

glm::mat4 look( TransformComponent* source, TransformComponent* target );

class TransformComponent : public Component {
public:

    /// Constructor
    TransformComponent();

    /// Constructor
    explicit TransformComponent( const glm::vec3& translate,
                                 const glm::vec3& rotate,
                                 const glm::vec3& scale );

    /// Set translates
    void setTranslate( float x, float y, float z );

    /// Set rotation in degrees
    void setRotate( float x, float y, float z );

    /// Set scale
    void setScale( float x, float y, float z );

    /// Translate this transform by values
    void translate( float x, float y, float z );

    /// Rotate this transform by degrees
    void rotate( float x, float y, float z );

    /// Scale this transform by values
    void scale( float x, float y, float z );

    /// Move this transform forward
    void moveForward( float value );

    /// Move this transform to the right
    void moveRight( float value );

    /// Move this transform up
    void moveUp( float value );

    glm::vec3 getTranslate() const { return m_translate; }
    glm::vec3 getFront() const { return m_front; }
    glm::vec3 getUp() const { return m_up; }
    glm::vec3 getRight() const { return m_right; }
    float getPitch() const { return m_pitch; }
    float getYaw() const { return m_yaw; }
    float getRoll() const { return m_roll; }

    /// Get composite matrix
    glm::mat4 getMatrix() const;

private:

    void update();

private:

    /// Rotation
    float m_pitch;
    float m_yaw;
    float m_roll;

    /// Vectors
    glm::vec3 m_front;
    glm::vec3 m_up;
    glm::vec3 m_right;

    /// Values
    glm::vec3 m_translate;
    glm::vec3 m_scale;
};

}
#endif //OPENGL_EXAMPLES_TRANSFORMCOMPONENT_HH
