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

    // General
    Accept,
    Cancel,
    Quit
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

typedef std::vector< Command* > Commands;
typedef std::vector< InputCommand* > InputCommands;


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
    explicit InputCommand( InputAction action,
                           InputState state );
    InputAction action() const;
    InputState state() const;

protected:

    InputAction m_action;
    InputState m_state;
};

}

#endif //OPENGL_EXAMPLES_COMMAND_HH
