//
// Created by Eddie Hoyle on 17/11/17.
//

#ifndef OPENGL_EXAMPLES_COMMAND_HH
#define OPENGL_EXAMPLES_COMMAND_HH

#include <vector>

namespace common {

enum class CommandType {
    None,
    Input,
    Other
};

enum class InputAction {
    None,

    // Player
    MoveForward,
    MoveBackward,
    MoveLeft,
    MoveRight,
    TurnLeft,
    TurnRight,
    Attack,
    Jump,

    // Player2
    MoveForward2,
    MoveBackward2,
    TurnLeft2,
    TurnRight2,

    // General
    Accept,
    Cancel,
    Quit,

    // Other
    LMB,
    RMB,
    Zoom
};

enum class InputState {
    None,
    Press,
    Release,
    Repeat
};

/// Forward Declare
class Command;
class InputCommand;
class ZoomCommand;

typedef std::vector< Command* > Commands;
typedef std::vector< InputCommand* > InputCommands;
typedef std::vector< ZoomCommand* > ZoomCommands;


class Command {
public:
    virtual ~Command() {}
    CommandType type() const;

    template< class CommandT >
    CommandT* asType() {
        return dynamic_cast< CommandT* >( this );
    }
protected:
    explicit Command( CommandType type );
    CommandType m_type;
};

class InputCommand : public Command {
public:
    explicit InputCommand( InputAction action, InputState state );
    InputAction action() const;
    InputState state() const;

protected:

    InputAction m_action;
    InputState m_state;
};

class ZoomCommand : public Command {
public:
    explicit ZoomCommand( InputAction action, double value );
    InputAction action() const;
    double value() const;

protected:

    InputAction m_action;
    double m_value;
};

}

#endif //OPENGL_EXAMPLES_COMMAND_HH
