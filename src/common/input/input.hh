//
// Created by Eddie Hoyle on 14/11/17.
//

#ifndef OPENGL_EXAMPLES_INPUT_HH
#define OPENGL_EXAMPLES_INPUT_HH

#include <set>
#include <vector>
#include "defs.hh"
#include "../command/command.hh"

class GLFWwindow;

namespace common {

void glfw3KeyPressCallback( GLFWwindow* window, int key, int scancode, int action, int mods );

class InputManager {

public:
    static InputManager* instance();

public:
    InputManager( const InputManager& ) = delete;
    InputManager& operator=( const InputManager& ) = delete;
    ~InputManager();

    void input( KeyEvent event, KeyState state );

    std::vector< AbstractCommand* > commands() const;

    void clear();

private:
    InputManager();
    static InputManager* s_instance;

private:
    std::vector< AbstractCommand* > m_commands;

};

} // namespace common



#endif //OPENGL_EXAMPLES_INPUT_HH
