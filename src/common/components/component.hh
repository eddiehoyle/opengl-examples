//
// Created by Eddie Hoyle on 19/11/17.
//

#ifndef OPENGL_EXAMPLES_COMPONENT_HH
#define OPENGL_EXAMPLES_COMPONENT_HH

#include <glm/glm.hpp>
#include <glm/ext.hpp>
#include <glm/gtx/matrix_decompose.hpp>

#include "../transform.hh"

namespace common {

enum class ComponentType {
    None,

    MoveState,
    InputMouse,

    Transform

};

class Component {
public:
    virtual ~Component();

    ComponentType type();

    template< class ComponentT >
    ComponentT *asType() {
        return dynamic_cast< ComponentT * >( this );
    }

protected:
    Component( ComponentType type );

    ComponentType m_type;

};

class InputMouseComponent : public Component {

public:
    InputMouseComponent();

    void set( int x, int y );

    int x() const;

    int y() const;

private:
    int m_x;
    int m_y;
};

class MoveStateComponent : public Component {

public:
    MoveStateComponent();

    void setForward( bool m_forward );

    void setBackward( bool m_backward );

    void setLeft( bool m_strafeLeft );

    void setRight( bool m_strafeRight );

    bool isForward() const;

    bool isBackward() const;

    bool isLeft() const;

    bool isRight() const;

private:
    bool m_forward;
    bool m_backward;
    bool m_left;
    bool m_right;
};

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

    /// Look at point
    void look( float x, float y, float z );

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

#endif //OPENGL_EXAMPLES_COMPONENT_HH
