#ifndef OPENGL_EXAMPLES_TRANSFORM_HH
#define OPENGL_EXAMPLES_TRANSFORM_HH

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/ext.hpp>

#include <iostream>

namespace common {

class Transform {
public:

    /// Constructor
    Transform()
            : m_pitch(),
              m_yaw(),
              m_roll(),
              m_front( 0, 0, -1 ),
              m_up( 0, 1, 0 ),
              m_right( 1, 0, 0 ),
              m_translate(),
              m_scale( 1, 1, 1 ) {}

    /// Constructor
    explicit Transform( const glm::vec3& translate,
                        const glm::vec3& rotate,
                        const glm::vec3& scale )
            : m_pitch(),
              m_yaw(),
              m_roll(),
              m_front(),
              m_up(),
              m_right(),
              m_translate(),
              m_scale() {
        setTranslate( translate.x, translate.y, translate.z );
        setRotate( rotate.x, rotate.y, rotate.z );
        setScale( scale.x, scale.y, scale.z );
    }

    /// Set translates
    void setTranslate( float x, float y, float z ) {
        m_translate = glm::vec3( x, y, z );
    }

    /// Set rotation in degrees
    void setRotate( float x, float y, float z ) {

        m_pitch = x;
        m_yaw = y;
        m_roll = z;

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

    /// Set scale
    void setScale( float x, float y, float z ) {
        m_scale = glm::vec3( x, y, z );
    }

    /// Translate this transform by values
    void translate( float x, float y, float z ) {
        m_translate += glm::vec3( x, y, z );
    }

    /// Rotate this transform by degrees
    void rotate( float x, float y, float z ) {
        setRotate( m_pitch + x, m_yaw + y, m_roll + z );
    }

    /// Scale this transform by values
    void scale( float x, float y, float z ) {
        m_scale = glm::vec3( x, y, z );
    }

    /// Move this transform forward
    void moveForward( float value ) {
        m_translate += m_front * value;
    }

    /// Move this transform to the right
    void moveRight( float value ) {
        m_translate += m_right * value;
    }

    /// Move this transform up
    void moveUp( float value ) {
        m_translate += m_up * value;
    }

    /// Get translation
    glm::vec3 getTranslate() const {
        return m_translate;
    }

    /// Get euler rotation in degrees
    glm::vec3 getRotate() const {
        return glm::vec3();
    }

    /// Get scale
    glm::vec3 getScale() const {
        return m_scale;
    }

    glm::vec3 getFront() const {
        return m_front;
    }

    glm::vec3 getUp() const {
        return m_up;
    }

    glm::vec3 getRight() const {
        return m_right;
    }

    /// Get matrix
    glm::mat4 getMatrix() const {
        glm::mat4 identity;
        glm::mat4 translate = glm::translate( identity, m_translate );
        glm::mat4 rotateX = glm::rotate( identity, m_pitch, glm::vec3( 1, 0, 0 ) );
        glm::mat4 rotateY = glm::rotate( identity, m_yaw, glm::vec3( 0, 1, 0 ) );
        glm::mat4 rotateZ = glm::rotate( identity, m_roll, glm::vec3( 0, 0, 1 ) );
        glm::mat4 rotate = rotateX * rotateY * rotateZ;
        glm::mat4 scale = glm::scale( identity, m_scale );
        return translate * rotate * scale;
    }

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
#endif //OPENGL_EXAMPLES_TRANSFORM_HH
