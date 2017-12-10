//
// Created by Eddie Hoyle on 19/11/17.
//

#ifndef OPENGL_EXAMPLES_COMPONENT_HH
#define OPENGL_EXAMPLES_COMPONENT_HH

namespace common {

enum class ComponentType {
    None,
    MoveState,
    InputMouse,
    Transform,
    Entity
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

}

#endif //OPENGL_EXAMPLES_COMPONENT_HH
