//
// Created by Eddie Hoyle on 17/12/17.
//

#include "controller.hh"
#include "../common/display.hh"
#include "../common/input/input.hh"
#include "../common/components/moveComponent.hh"
#include "../common/components/transformComponent.hh"

static float MAX_PITCH = 89.0f;
static float MIN_PITCH = -89.0f;

ThirdPersonController::ThirdPersonController( Bunny *player, common::Camera *camera )
        : m_player( player ),
          m_camera( camera ) {
}

void ThirdPersonController::update( double elapsed ) {


    // InputController::update()
    if ( !common::DisplayManager::instance()->isFocused() ) {
        return;
    }

    // Handle mouse move first
    handleMouseMove();

    // Handle commands next
    const common::InputCommands& commands = common::InputManager::instance()->commands();
    for ( common::InputCommand *command : commands ) {
        handleCommand( command );
    }

    m_player->update( elapsed );
    Entity& entity = m_player->getEntity();

    using namespace common;
    glm::vec3 translate = m_player->getComponent( ComponentType::Transform )->asType< TransformComponent >()->getTranslate();
    float pitch = m_player->getComponent( ComponentType::Transform )->asType< TransformComponent >()->getPitch();
    float yaw = m_player->getComponent( ComponentType::Transform )->asType< TransformComponent >()->getYaw();
    float roll = m_player->getComponent( ComponentType::Transform )->asType< TransformComponent >()->getRoll();
    entity.setPosition( translate );
    entity.setRotation( glm::vec3( pitch, yaw, roll ) );

    m_camera->update( elapsed );
}

void ThirdPersonController::handleCommand( common::InputCommand *command ) {

    assert( command );

    using namespace common;
    MoveStateComponent* playerMoveComponent =
            m_player->getComponent( ComponentType::MoveState )->asType< MoveStateComponent >();
    assert( playerMoveComponent );

    switch ( command->state() ) {
        case InputState::Press:
            switch ( command->action() ) {
                case InputAction::MoveForward2:
                    playerMoveComponent->setForward( true );
                    break;
                case InputAction::MoveBackward2:
                    playerMoveComponent->setBackward( true );
                    break;
                case InputAction::TurnLeft2:
                    playerMoveComponent->setTurningLeft( true );
                    break;
                case InputAction::TurnRight2:
                    playerMoveComponent->setTurningRight( true );
                    break;
                case InputAction::Jump:
                    playerMoveComponent->setJump( true );
                    break;
                default:
                    break;
            }
            break;
        case InputState::Release:
            switch ( command->action() ) {
                case InputAction::MoveForward2:
                    playerMoveComponent->setForward( false );
                    break;
                case InputAction::MoveBackward2:
                    playerMoveComponent->setBackward( false );
                    break;
                case InputAction::TurnLeft2:
                    playerMoveComponent->setTurningLeft( false );
                    break;
                case InputAction::TurnRight2:
                    playerMoveComponent->setTurningRight( false );
                    break;
                case InputAction::Jump:
                    playerMoveComponent->setJump( false );
                    break;
                default:
                    break;
            }
            break;
        default:
            break;
    }
}

void ThirdPersonController::handleMouseMove() {

    using namespace common;

    Component *component = m_camera->getComponent( ComponentType::Transform );
    assert( component );

    TransformComponent *transformComponent =
            m_camera->getComponent( ComponentType::Transform )->asType< TransformComponent >();
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
