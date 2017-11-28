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
    ComponentT* asType() {
        return dynamic_cast< ComponentT* >( this );
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
    TransformComponent();

    void setRotate( float x, float y, float z );
    void setTranslate( float x, float y, float z );

    void translate( float x, float y, float z );
    void rotate( float x, float y, float z );
//
//    glm::vec3 translation() const;
//    glm::vec3 rotation() const;
//    glm::mat4 matrix() const;

    common::Transform getTransform() const {
        return m_transform;
    }

private:
    common::Transform m_transform;
};

}

#endif //OPENGL_EXAMPLES_COMPONENT_HH
