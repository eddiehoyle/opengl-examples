//
// Created by Eddie Hoyle on 6/12/17.
//

#include <iostream>
#include "tankController.hh"
#include "../display.hh"
#include "../command/command.hh"
#include "../input/input.hh"
#include "../components/moveComponent.hh"
#include "../components/transformComponent.hh"

namespace common {

TankController::TankController( AbstractSceneObject *object )
        : AbstractController( object ) {
}

void TankController::update( double elapsed ) {

    // InputController::update()
    if ( !DisplayManager::instance()->isFocused() ) {
        return;
    }

    // Handle commands next
    const InputCommands& commands = InputManager::instance()->commands();
    for ( InputCommand *command : commands ) {
        handleMove( command );
    }

    // Update object
    m_object->update( elapsed );

}

void TankController::handleMove( InputCommand *command ) {

    assert( command );

    Component *component = object()->getComponent( ComponentType::MoveState );
    assert( component );

    MoveStateComponent *moveComponent = component->asType< MoveStateComponent >();
    assert( moveComponent );

    switch ( command->state() ) {
        case InputState::Press:
            switch ( command->action() ) {
                case InputAction::MoveForward:
                    moveComponent->setForward( true );
                    break;
                case InputAction::MoveBackward:
                    moveComponent->setBackward( true );
                    break;
                case InputAction::TurnLeft:
                    moveComponent->setTurningLeft( true );
                    break;
                case InputAction::TurnRight:
                    moveComponent->setTurningRight( true );
                    break;
                default:
                    break;
            }
            break;
        case InputState::Release:
            switch ( command->action() ) {
                case InputAction::MoveForward:
                    moveComponent->setForward( false );
                    break;
                case InputAction::MoveBackward:
                    moveComponent->setBackward( false );
                    break;
                case InputAction::TurnLeft:
                    moveComponent->setTurningLeft( false );
                    break;
                case InputAction::TurnRight:
                    moveComponent->setTurningRight( false );
                    break;
                default:
                    break;
            }
            break;
        default:
            break;
    }
}

}