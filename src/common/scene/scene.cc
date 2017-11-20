//
// Created by Eddie Hoyle on 20/11/17.
//

#include "scene.hh"


namespace common {

AbstractSceneObject::~AbstractSceneObject() {
    for ( AbstractComponent* component : m_components ) {
        delete component;
    }
}

bool AbstractSceneObject::hasComponent( ComponentType type ) {
    for ( const auto& component : m_components ) {
        if ( component->type() == type ) {
            return true;
        }
    }
    return false;
}


}