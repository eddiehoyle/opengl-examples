//
// Created by Eddie Hoyle on 20/11/17.
//

#include <iostream>
#include "controller.hh"
#include "../input/input.hh"
#include "../display.hh"

namespace common {

AbstractController::AbstractController( AbstractSceneObject *object )
        : m_object( object ) {}

AbstractSceneObject *AbstractController::object() {
    return m_object;
}

};