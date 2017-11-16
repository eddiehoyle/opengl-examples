//
// Created by Eddie Hoyle on 14/11/17.
//

#ifndef OPENGL_EXAMPLES_INPUT_HH
#define OPENGL_EXAMPLES_INPUT_HH

#include <set>
#include "defs.hh"
#include "../event/observer.hh"

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
    void addObserver( Observer* observer );
    void removeObserver( Observer* observer );

private:
    InputManager();
    static InputManager* s_instance;

private:

    // Objects that listen for events
    std::set< Observer* > m_observers;

};

} // namespace common



#endif //OPENGL_EXAMPLES_INPUT_HH
