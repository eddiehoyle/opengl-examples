//
// Created by Eddie Hoyle on 17/11/17.
//

#include "command.hh"

#include "../camera.hh"

namespace common {

Command::Command( CommandType type )
    : m_type( type ){}

CommandType Command::type() const {
    return m_type;
}

// ----------------------------------------------------------------------

InputCommand::InputCommand()
        : Command( CommandType::None ),
          m_action( InputAction::None ),
          m_state( InputState::None ) {}


InputCommand::InputCommand( InputAction action, InputState state )
        : Command( CommandType::Input ),
          m_action( action ),
          m_state( state ) {}

InputAction InputCommand::action() const {
    return m_action;
}

InputState InputCommand::state() const {
    return m_state;
}

// ----------------------------------------------------------------------

InputMouseCommand::InputMouseCommand()
        : InputCommand( InputAction::None,
                        InputState::None ) {}

InputMouseCommand::InputMouseCommand( InputAction action,
                                      InputState state,
                                      int x,
                                      int y )
        : Command( CommandType::Input ),
          m_action( action ),
          m_state( state ),
          m_x( x ),
          m_y( y ) {}

int InputMouseCommand::x() const {
    return m_x;
}

int InputMouseCommand::y() const {
    return m_y;
}

// ----------------------------------------------------------------------


InputMoveCommand::InputMoveCommand()
        : InputCommand( InputAction::None, InputState::None ) {}

InputMoveCommand::InputMoveCommand( InputAction action, InputState state )
        : Command( CommandType::Input ),
          m_action( action ),
          m_state( state ) {}

}