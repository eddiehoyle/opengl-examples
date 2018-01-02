//
// Created by Eddie Hoyle on 14/11/17.
//

#ifndef OPENGL_EXAMPLES_INPUT_HH
#define OPENGL_EXAMPLES_INPUT_HH

#include <set>
#include <vector>
#include "../command/command.hh"
#include "../device/device.hh"

class GLFWwindow;

namespace common {

void glfw3KeyPressCallback( GLFWwindow *window, int key, int scancode, int action, int mods );
void glfw3MouseScrollCallback( GLFWwindow* window, double x, double y );
void glfw3MouseButtonCallback( GLFWwindow* window, int button, int action, int mods );
void glfw3ProcessMouse( GLFWwindow* window );

class InputManager {

public:
    static InputManager *instance();

public:

    MouseDevice* mouse() const;

    /// @deprecated
    void add( InputAction action, InputState state );

    void add( InputCommand* command );
    void add( ZoomCommand* command );

    const InputCommands& commands() const;
    const ZoomCommands& zoomCommands() const;
    void clear();

private:
    InputManager();
    ~InputManager();
    InputManager( const InputManager& ) = delete;
    InputManager& operator=( const InputManager& ) = delete;

    static InputManager* s_instance;

private:
    InputCommands m_commands;
    ZoomCommands m_zoomCommands;
    MouseDevice* m_mouse;

};

} // namespace common



#endif //OPENGL_EXAMPLES_INPUT_HH
