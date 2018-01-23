//
// Created by Eddie Hoyle on 1/01/18.
//

#include <glm/glm.hpp>
#include <iostream>
#include "player.hh"
#include "../common/input/input.hh"
#include "../common/display.hh"
#include "terrain.hh"

static const float RUN_SPEED = 200;
static const float TURN_SPEED = 160;
static const float GRAVITY = -100;
static const float JUMP_POWER = 50;

static const float TERRAIN_HEIGHT = 0;


Player::Player( const TexturedModel& model,
                const glm::vec3& position,
                const glm::vec3& rotation,
                float scale )
        : Entity( model, position, rotation, scale ),
          m_currentSpeed( 0 ),
          m_currentTurnSpeed( 0 ),
          m_upwardsSpeed( 0 ),
          m_isInAir( false )
{}

void Player::move( const Terrain& terrain ) {

    if ( !common::DisplayManager::instance()->isFocused() ) {
        return;
    }

    checkInputs();
    double elapsed = common::DisplayManager::instance()->getFrameTimeSeconds();
    float rotation = m_currentTurnSpeed * elapsed;
    increaseRotation( 0, rotation, 0 );
    float distance = m_currentSpeed * elapsed;
    float dx = distance * std::sin( glm::radians( getRotation().y ) );
    float dz = distance * std::cos( glm::radians( getRotation().y ) );
    m_upwardsSpeed += GRAVITY * elapsed;
    increasePosition( dx, m_upwardsSpeed * elapsed, dz );
    float terrainHeight = terrain.getHeightOfTerrain( getPosition().x, getPosition().z );
    if ( getPosition().y < terrainHeight ) {
        m_upwardsSpeed = 0;
        setPosition( glm::vec3( getPosition().x, terrainHeight, getPosition().z ) );
        m_isInAir = false;
    }
}

void Player::jump() {
    if ( !m_isInAir ) {
        m_upwardsSpeed = JUMP_POWER;
        m_isInAir = true;
    }
}

void Player::checkInputs() {

    using namespace common;
    const InputCommands commands = InputManager::instance()->commands();
    for ( InputCommand* command : commands ) {

        switch ( command->state() ) {
            case InputState::Press:
                switch ( command->action() ) {
                    case InputAction::MoveForward:
                        m_currentSpeed = RUN_SPEED;
                        break;
                    case InputAction::MoveBackward:
                        m_currentSpeed = -RUN_SPEED;
                        break;
                    case InputAction::TurnLeft:
                        m_currentTurnSpeed = TURN_SPEED;
                        break;
                    case InputAction::TurnRight:
                        m_currentTurnSpeed = -TURN_SPEED;
                        break;
                    case InputAction::Jump:
                        jump();
                        break;
                    default:
                        break;
                }
                break;
            case InputState::Release:
                switch ( command->action() ) {
                    case InputAction::MoveForward:
                        m_currentSpeed = 0;
                        break;
                    case InputAction::MoveBackward:
                        m_currentSpeed = 0;
                        break;
                    case InputAction::TurnLeft:
                        m_currentTurnSpeed = 0;
                        break;
                    case InputAction::TurnRight:
                        m_currentTurnSpeed = 0;
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
