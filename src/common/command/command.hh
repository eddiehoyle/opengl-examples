//
// Created by Eddie Hoyle on 17/11/17.
//

#ifndef OPENGL_EXAMPLES_COMMAND_HH
#define OPENGL_EXAMPLES_COMMAND_HH

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
    MouseHorizontal,
    MouseVectical,
    Quit
};

enum class InputState {
    None,
    Press,
    Release,
    Repeat
};

class Command {
public:
    virtual ~Command() {}
protected:
    explicit Command( CommandType type );
    CommandType m_type;
};

class InputCommand : public Command {

public:
    InputCommand();
    explicit InputCommand( InputAction action,
                           InputState state,
                           double value=0.0 );

    InputAction action() const;
    InputState state() const;
    double value() const;

private:
    InputAction m_action;
    InputState m_state;
    double m_value;
};


}

#endif //OPENGL_EXAMPLES_COMMAND_HH
