//
// Created by Eddie Hoyle on 17/11/17.
//

#include "command.hh"

#include "../camera.hh"

namespace common {

Command::Command( CommandType type )
    : m_type( type ){}

InputCommand::InputCommand()
        : Command( CommandType::None ),
          m_action( InputAction::None ),
          m_state( InputState::None ) {}

InputCommand::InputCommand( InputAction action, InputState state, double value )
        : Command( CommandType::Input ),
          m_action( action ),
          m_state( state ),
          m_value( value ) {}

InputAction InputCommand::action() const {
    return m_action;
}

InputState InputCommand::state() const {
    return m_state;
}

double InputCommand::value() const {
    return m_value;
}

}