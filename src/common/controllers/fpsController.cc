//
// Created by Eddie Hoyle on 6/12/17.
//

#include <iostream>
#include "fpsController.hh"
#include "../display.hh"
#include "../command/command.hh"
#include "../input/input.hh"
#include "../components/moveComponent.hh"
#include "../components/transformComponent.hh"


namespace common {

static float MAX_PITCH = 89.0f;
static float MIN_PITCH = -89.0f;

FpsController::FpsController( AbstractSceneObject *object )
        : AbstractController( object ) {
}

void FpsController::update( double elapsed ) {

    // InputController::update()
    if ( !DisplayManager::instance()->isFocused() ) {
        return;
    }

    // Handle mouse move first
    handleMouseMove();

    // Handle commands next
    const InputCommands& commands = InputManager::instance()->commands();
    for ( InputCommand *command : commands ) {
        handleMove( command );
    }

    // Update object
    m_object->update( elapsed );

}

void FpsController::handleMove( InputCommand *command ) {

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
                    moveComponent->setStrafeLeft( true );
                    break;
                case InputAction::MoveRight:
                    moveComponent->setStrafeRight( true );
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
                    moveComponent->setStrafeLeft( false );
                    break;
                case InputAction::MoveRight:
                    moveComponent->setStrafeRight( false );
                    break;
                default:
                    break;
            }
            break;
        default:
            break;
    }
}


void FpsController::handleMouseMove() {

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

    float prevPitch = -transformComponent->getPitch();

    if ( ( prevPitch + pitch ) >= MAX_PITCH ) {
        pitch = std::max( MAX_PITCH - prevPitch, 0.0f );
    }

    if ( ( prevPitch + pitch ) <= MIN_PITCH ) {
        pitch = -std::max( prevPitch - MIN_PITCH, 0.0f );
    }

//    std::cerr << "InputController::handleMouseMove() : mouse=(" << -pitch << ", " << yaw << ")" << std::endl;

    transformComponent->rotate( -pitch, yaw, 0.0f );

}

}