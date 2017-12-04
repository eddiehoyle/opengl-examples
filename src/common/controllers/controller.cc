//
// Created by Eddie Hoyle on 20/11/17.
//

#include <iostream>
#include "controller.hh"
#include "../input/input.hh"

namespace common {

AbstractController::AbstractController( AbstractSceneObject *object )
        : m_object( object ) {}

AbstractSceneObject *AbstractController::object() {
    return m_object;
}

InputController::InputController( AbstractSceneObject *object )
        : m_pitch( 0 ),
          m_prevX( 0 ),
          m_prevY( 0 ),
          m_initialised( false ),
          AbstractController( object ) {
}

void InputController::update( double elapsed ) {

    if ( !m_initialised ) {
        m_prevX = InputManager::instance()->mouse()->x();
        m_prevY = InputManager::instance()->mouse()->y();
    }

    // Handle mouse move first
    handleMouseMove();

    // Handle commands next
    const InputCommands& commands = InputManager::instance()->commands();
    for ( InputCommand *command : commands ) {
        handleMove( command );
        handleMouse( command );
    }

    // Update object
    m_object->update( elapsed );

    // First update complete
    m_initialised = true;

}

void InputController::handleMove( InputCommand *command ) {

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

void InputController::handleMouse( InputCommand *command ) {

}

void InputController::handleMouseMove() {

    Component *component = object()->getComponent( ComponentType::Transform );
    assert( component );

    TransformComponent *transformComponent = component->asType< TransformComponent >();
    assert( transformComponent );

    float pitch = static_cast< float >( InputManager::instance()->mouse()->y() -
                                        InputManager::instance()->mouse()->prevY() );
    float yaw = static_cast< float >( InputManager::instance()->mouse()->x() -
                                      InputManager::instance()->mouse()->prevX() );

    pitch *= 0.3;
    yaw *= 0.3;

    float maxPitch = 89.0f;
    float minPitch = -89.0f;

    float prevPitch = m_pitch;
    m_pitch += pitch;

    if ( ( prevPitch + pitch ) >= maxPitch ) {
        pitch = std::max( maxPitch - prevPitch, 0.0f );
        m_pitch = maxPitch;
    }

    if ( ( prevPitch + pitch ) <= minPitch ) {
        pitch = -std::max( prevPitch - minPitch, 0.0f );
        m_pitch = minPitch;
    }

//    std::cerr << "InputController::handleMouseMove() : mouse=(" << -pitch << ", " << yaw << ")" << std::endl;

    transformComponent->rotate( -pitch, yaw, 0.0f );

}


};