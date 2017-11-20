//
// Created by Eddie Hoyle on 19/11/17.
//

#ifndef OPENGL_EXAMPLES_COMPONENT_HH
#define OPENGL_EXAMPLES_COMPONENT_HH

namespace common {

enum class ComponentType {
    kMove
};

class AbstractComponent {
public:
    virtual ~AbstractComponent() {}
    ComponentType type() {
        return m_type;
    }
protected:
    AbstractComponent( ComponentType type )
            : m_type( type ) {}
    ComponentType m_type;

};

class MoveComponent : public AbstractComponent {

public:
    MoveComponent();

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
