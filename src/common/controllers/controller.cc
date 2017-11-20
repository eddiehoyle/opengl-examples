//
// Created by Eddie Hoyle on 20/11/17.
//

#include "controller.hh"
#include "../input/input.hh"

namespace common {

AbstractSceneObject* AbstractController::object() {
    return m_object;
}

void PlayerMoveController::update( double elapsed ) {

    std::vector< Command* > commands = InputManager::instance()->commands();

    MoveComponent* move = m_object->getComponent< MoveComponent >();
    if ( move != nullptr ) {
        move
    }

    m_object->update( elapsed );

}

};