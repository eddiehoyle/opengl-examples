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
    MoveForward,
    MoveBackward,
    MoveLeft,
    MoveRight,
    MouseMove,
    MouseScroll,
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
    InputCommand();

    InputAction action() const;
    InputState state() const;

protected:
    explicit InputCommand( InputAction action,
                           InputState state );

    InputAction m_action;
    InputState m_state;
};

class InputMouseCommand : public InputCommand {

public:
    InputMouseCommand();
    explicit InputMouseCommand( InputAction action,
                                InputState state,
                                int x,
                                int y );

    int x() const;
    int y() const;

private:
    int m_x;
    int m_y;
};

class InputMoveCommand : public InputCommand {

public:
    InputMoveCommand();
    explicit InputMoveCommand( InputAction action,
                               InputState state );
};


}

#endif //OPENGL_EXAMPLES_COMMAND_HH
