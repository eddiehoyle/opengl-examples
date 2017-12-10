//
// Created by Eddie Hoyle on 20/11/17.
//

#ifndef OPENGL_EXAMPLES_SCENE_HH
#define OPENGL_EXAMPLES_SCENE_HH

#include <vector>
#include "../components/component.hh"

namespace common {

class AbstractSceneObject {
public:
    virtual ~AbstractSceneObject();
    virtual void update( double elapsed ) = 0;

    bool hasComponent( ComponentType type );

    Component* getComponent( ComponentType type ) const {
        for ( Component* component : m_components ) {
            if ( component->type() == type ) {
                return component;
            }
        }
        return nullptr;
    }

protected:
    std::vector< Component* > m_components;

    template< class ComponentT >
    void addComponent( ComponentT* component ) {
        m_components.push_back( component );
    }

};

}


#endif //OPENGL_EXAMPLES_SCENE_HH
