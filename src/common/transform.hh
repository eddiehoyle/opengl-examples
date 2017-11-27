#ifndef OPENGL_EXAMPLES_TRANSFORM_HH
#define OPENGL_EXAMPLES_TRANSFORM_HH

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/ext.hpp>

class Transform {
public:

    /// Constructor
    Transform()
        : m_translate(),
        m_rotate(),
        m_scale() {}

    /// Constructor
    explicit Transform( const glm::vec3& translate,
                        const glm::vec3& rotate,
                        const glm::vec3& scale )
        : m_translate(),
          m_rotate(),
          m_scale() {}

    /// Set translates
    void setTranslate( float x, float y, float z ) {
        m_translate = glm::translate( glm::mat4(), glm::vec3( x, y, z ) );
    }

    /// Set rotation in degrees
    void setRotate( float x, float y, float z ) {
        glm::mat4 identity;
        glm::mat4 rotateX = glm::rotate( identity, glm::radians( x ), glm::vec3( 1, 0, 0 ) );
        glm::mat4 rotateY = glm::rotate( identity, glm::radians( y ), glm::vec3( 0, 1, 0 ) );
        glm::mat4 rotateZ = glm::rotate( identity, glm::radians( z ), glm::vec3( 0, 0, 1 ) );
        m_rotate = ( rotateX * rotateY * rotateZ );
    }

    /// Set scale
    void setScale( float x, float y, float z ) {
        m_scale = glm::scale( glm::mat4(), glm::vec3( x, y, z ) );
    }

    /// Translate this transform by values
    void translate( float x, float y, float z ) {
        m_translate = glm::translate( m_translate, glm::vec3( x, y, z ) );
    }

    /// Rotate this transform by degrees
    void rotate( float x, float y, float z );

    /// Move this transform forward
    void moveForward( float value );

    /// Move this transform to the right
    void moveRight( float value );

    /// Move this transform up
    void moveUp( float value );

    /// Scale this transform by values
    void scale( float x, float y, float z ) {
        m_scale = glm::scale( m_scale, glm::vec3( x, y, z ) );
    }

    /// Get translation
    glm::vec3 getTranslate() const {
        return glm::vec3( m_translate[3][0],
                          m_translate[3][1],
                          m_translate[3][2] );
    }

    /// Get euler rotation in degrees
    glm::vec3 getRotate() const {
        glm::mat4 rotate = m_rotate; // Copy for non-const
        float x, y, z;
        glm::extractEulerAngleXYZ( rotate, x, y, z );
        return glm::degrees( glm::vec3( x, y, z ) );
    }

    /// Get scale
    glm::vec3 getScale() const {
        glm::vec3 colX( m_scale[0][0], m_scale[0][1], m_scale[0][2] );
        glm::vec3 colY( m_scale[1][0], m_scale[1][1], m_scale[1][2] );
        glm::vec3 colZ( m_scale[2][0], m_scale[2][1], m_scale[2][2] );
        return glm::vec3( glm::length( colX ),
                          glm::length( colY ),
                          glm::length( colZ ) );
    }

    /// Get matrix
    glm::mat4 getMatrix() const {
        return m_scale * m_rotate * m_translate;
    }

private:
    glm::mat4 m_translate;
    glm::mat4 m_rotate;
    glm::mat4 m_scale;
};

#endif //OPENGL_EXAMPLES_TRANSFORM_HH
