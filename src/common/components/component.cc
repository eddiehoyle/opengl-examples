//
// Created by Eddie Hoyle on 19/11/17.
//


#include "component.hh"
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/quaternion.hpp>
#include <iostream>

namespace common {

ComponentType Component::type() {
    return m_type;
}

Component::Component( ComponentType type )
        : m_type( type ) {}

Component::~Component() {}

}