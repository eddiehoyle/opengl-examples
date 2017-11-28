//
// Created by Eddie Hoyle on 20/11/17.
//

#include <iostream>
#include "controller.hh"
#include "../input/input.hh"

namespace common {

AbstractController::AbstractController( AbstractSceneObject* object )
        : m_object( object ) {}

AbstractSceneObject* AbstractController::object() {
    return m_object;
}

InputController::InputController( AbstractSceneObject* object )
    : AbstractController( object ) {
}

void InputController::update( double elapsed ) {

    // Handle mouse move first
    handleMouseMove();

    // Handle commands next
    const InputCommands& commands = InputManager::instance()->commands();
    for ( InputCommand* command : commands ) {
        handleMove( command );
        handleMouse( command );
    }

    // Update object
    m_object->update( elapsed );

}

void InputController::handleMove( InputCommand *command ) {

    assert( command );

    Component* component = object()->getComponent( ComponentType::MoveState );
    assert( component );

    MoveStateComponent* moveComponent = component->asType< MoveStateComponent >();
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
                case InputAction::MoveLeft:
                    moveComponent->setLeft( true );
                    break;
                case InputAction::MoveRight:
                    moveComponent->setRight( true );
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
                case InputAction::MoveLeft:
                    moveComponent->setLeft( false );
                    break;
                case InputAction::MoveRight:
                    moveComponent->setRight( false );
                    break;
                default:
                    break;
            }
            break;
        default:
            break;
    }
}

void InputController::handleMouse( InputCommand* command ) {

}

void InputController::handleMouseMove() {

    Component* component = object()->getComponent( ComponentType::Transform );
    assert( component );

    TransformComponent* transformComponent = component->asType< TransformComponent >();
    assert( transformComponent );

    int pitch = InputManager::instance()->mouse()->y() - InputManager::instance()->mouse()->prevY();
    int yaw = InputManager::instance()->mouse()->x() - InputManager::instance()->mouse()->prevX();

//    std::cerr << "InputController::" << __func__ << " : delta=(" << yaw << ", " << pitch << ")" << std::endl;
    transformComponent->rotate( pitch, yaw, 0.0f );

}


};