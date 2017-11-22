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

PlayerMoveController::PlayerMoveController( AbstractSceneObject* object )
    : AbstractController( object ) {
}

void PlayerMoveController::update( double elapsed ) {

    const InputCommands commands = InputManager::instance()->commands();

//    std::cerr << __func__ << " : commands=" << commands.size() << std::endl;

    for ( InputCommand* command : commands ) {
        switch ( command->action() ) {
            case InputAction::MoveForward:
            case InputAction::MoveBackward:
            case InputAction::MoveLeft:
            case InputAction::MoveRight:
                InputMoveCommand *moveCommand = command->asType< InputMoveCommand >();
                handleMove( command );
                break;
            case InputAction::MouseMove:
                handleMouse( command );
                break;
            case InputAction::MouseScroll:
//                InputScrollCommand* scrollCommand = inputCommand->asType< InputScrollCommand >();
                handleScroll( command );
                break;
        }
    }
}

void PlayerMoveController::handleMove( InputMoveCommand *command ) {

    if ( command == nullptr ) {
        return;
    }

    AbstractComponent* component = object()->getComponent( ComponentType::InputMove );
    if ( component == nullptr ) {
        return;
    }

    InputMoveCommand* moveCommand = command->asType< InputMoveCommand >();
    InputMoveComponent* moveComponent = component->asType< InputMoveComponent >();

    switch ( command->state() ) {
        case InputState::Press:
            switch ( command->action() ) {
                case InputAction::MoveForward:
                    move->setForward( true );
                    break;
                case InputAction::MoveBackward:
                    move->setBackward( true );
                    break;
                case InputAction::MoveLeft:
                    move->setLeft( true );
                    break;
                case InputAction::MoveRight:
                    move->setRight( true );
                    break;
                default:
                    break;
            }
            break;
        case InputState::Release:
            switch ( command->action() ) {
                case InputAction::MoveForward:
                    move->setForward( false );
                    break;
                case InputAction::MoveBackward:
                    move->setBackward( false );
                    break;
                case InputAction::MoveLeft:
                    move->setLeft( false );
                    break;
                case InputAction::MoveRight:
                    move->setRight( false );
                    break;
                default:
                    break;
            }
            break;
        default:
            break;
    }
}

void PlayerMoveController::handleMouse( InputCommand* command ) {

    if ( command == nullptr ) {
        return;
    }

    AbstractComponent* component = object()->getComponent( ComponentType::InputMouse );
    if ( component == nullptr ) {
        return;
    }

    InputMouseCommand* mouseCommand = command->asType< InputMouseCommand >();
    InputMouseComponent* mouseComponent = component->asType< InputMouseComponent >();

    switch ( command->action() ) {
        case InputAction::MouseMove;
            mouseComponent->set( mouseCommand->x(), mouseCommand->y() );
            break;
    }

}


void PlayerMoveController::handleScroll( InputMouseCommand *command ) {

    if ( command == nullptr ) {
        return;
    }

    InputMouseComponent* mouse = object()->getComponent< InputMouseComponent >();

    switch ( command->action() ) {
        case InputAction::MouseMove;
            mouse->set( mouse->x(), mouse->y() );
            break;
    }

}

};