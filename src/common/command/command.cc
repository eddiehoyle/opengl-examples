//
// Created by Eddie Hoyle on 17/11/17.
//

#include "command.hh"

#include "../scene/camera.hh"

namespace common {

Command::Command( CommandType type )
        : m_type( type ) {}

CommandType Command::type() const {
    return m_type;
}

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

ZoomCommand::ZoomCommand( InputAction action, double value )
        : Command( CommandType::Input ),
          m_action( action ),
          m_value( value ) {}

InputAction ZoomCommand::action() const {
    return m_action;
}

double ZoomCommand::value() const {
    return m_value;
}

}

