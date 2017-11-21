//
// Created by Eddie Hoyle on 14/11/17.
//

#ifndef OPENGL_EXAMPLES_INPUT_HH
#define OPENGL_EXAMPLES_INPUT_HH

#include <set>
#include <vector>
#include "../command/command.hh"

class GLFWwindow;

namespace common {

typedef std::vector< InputCommand > InputCommands;

void glfw3KeyPressCallback( GLFWwindow *window, int key, int scancode, int action, int mods );

class InputManager {

public:
    static InputManager *instance();

public:
    void add( InputAction action, InputState state, double value = 0.0 );
    const InputCommands& commands() const;
    void clear();

private:
    InputManager();
    ~InputManager();
    InputManager( const InputManager& ) = delete;
    InputManager& operator=( const InputManager& ) = delete;

    static InputManager* s_instance;

private:
    InputCommands m_commands;

};

} // namespace common



#endif //OPENGL_EXAMPLES_INPUT_HH
