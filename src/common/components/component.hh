//
// Created by Eddie Hoyle on 19/11/17.
//

#ifndef OPENGL_EXAMPLES_COMPONENT_HH
#define OPENGL_EXAMPLES_COMPONENT_HH

namespace common {

enum class ComponentType {
    None,
    InputMove,
    InputMouse
};

class AbstractComponent {
public:
    virtual ~AbstractComponent();

    ComponentType type();

    template< class ComponentT >
    ComponentT* asType() {
        return dynamic_cast< ComponentT* >( this );
    }
protected:
    AbstractComponent( ComponentType type );
    ComponentType m_type;

};

class InputMouseComponent : public AbstractComponent {

public:
    InputMouseComponent();

    void set( int x, int y );

    int x() const;
    int y() const;

private:
    int m_x;
    int m_y;
};

class InputMoveComponent : public AbstractComponent {

public:
    InputMoveComponent();

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

}

#endif //OPENGL_EXAMPLES_COMPONENT_HH
