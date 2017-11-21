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

    MoveComponent* move = object()->getComponent< MoveComponent >();
    if ( move != nullptr ) {
        for ( const InputCommand& command : commands ) {
            switch ( command.state() ) {
                case InputState::Press:
                    switch ( command.action() ) {
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
                    switch ( command.action() ) {
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
    }

    m_object->update( elapsed );

    // Temp
//    common::InputManager::instance()->clear();
}

};