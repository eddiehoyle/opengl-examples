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

void glfw3KeyPressCallback( GLFWwindow *window, int key, int scancode, int action, int mods );

class InputManager {

public:
    static InputCommand* create( InputAction action );

public:
    static InputManager *instance();

public:

    /// TODO
    void add( InputCommand* command );

    void add( InputAction action, InputState state );
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
