//
// Created by Eddie Hoyle on 14/11/17.
//

#include "input.hh"

#include <GLFW/glfw3.h>

namespace common {

void glfw3KeyPressCallback( GLFWwindow* window, int key, int scancode, int action, int mods ) {

    KeyState state = KeyState::kUnknown;
    switch ( action ) {
        case GLFW_PRESS:
            state = KeyState::kPress;
            break;
        case GLFW_REPEAT:
            state = KeyState::kRepeat;
            break;
        case GLFW_RELEASE:
            state = KeyState::kRelease;
            break;
        default:
            state = KeyState::kUnknown;
            break;
    }

    KeyEvent event = KeyEvent::kUnknown;
    switch ( key ) {
        case GLFW_KEY_W:
            event = KeyEvent::kForward;
            break;
        case GLFW_KEY_A:
            event = KeyEvent::kTurnLeft;
            break;
        case GLFW_KEY_S:
            event = KeyEvent::kBackward;
            break;
        case GLFW_KEY_D:
            event = KeyEvent::kTurnRight;
            break;
        case GLFW_KEY_ESCAPE:
            event = KeyEvent::kCancel;
            break;
        default:
            event = KeyEvent::kUnknown;
            break;
    }

    InputManager::instance()->input( event, state );
}

InputManager* InputManager::s_instance = nullptr;

InputManager* InputManager::instance() {
    if ( s_instance == nullptr ) {
        s_instance = new InputManager();
    }
    return s_instance;
}

InputManager::InputManager() {
}

InputManager::~InputManager() {
    delete s_instance;
}

void InputManager::input( KeyEvent event, KeyState state ) {

}

} // namespace common
