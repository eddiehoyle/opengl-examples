//
// Created by Eddie Hoyle on 14/11/17.
//

#include "input.hh"

#include <GLFW/glfw3.h>
#include <iostream>

namespace common {

void glfw3KeyPressCallback( GLFWwindow* window, int key, int scancode, int type, int mods ) {

    if ( key == GLFW_KEY_ESCAPE && type == GLFW_PRESS ) {
        glfwSetWindowShouldClose( window, GLFW_TRUE );
        return;
    }

    InputState state = InputState::None;
    switch ( type ) {
        case GLFW_PRESS:
            state = InputState::Press;
            break;
        case GLFW_RELEASE:
            state = InputState::Release;
            break;
    }

    InputAction action = InputAction::None;
    switch ( key ) {
        case GLFW_KEY_W:
            action = InputAction::MoveForward;
            break;
        case GLFW_KEY_S:
            action = InputAction::MoveBackward;
            break;
        case GLFW_KEY_A:
            action = InputAction::MoveLeft;
            break;
        case GLFW_KEY_D:
            action = InputAction::MoveRight;
            break;
    }

    if ( action != InputAction::None && state != InputState::None ) {
        InputManager::instance()->add( action, state );
    }
}

InputManager* InputManager::s_instance = nullptr;

InputManager* InputManager::instance() {
    if ( s_instance == nullptr ) {
        s_instance = new InputManager();
    }
    return s_instance;
}

InputManager::InputManager()
    : m_commands() {
}

InputManager::~InputManager() {
    delete s_instance;
}

void InputManager::add( InputAction action, InputState state, double value ) {
    const InputCommand command( action, state, value );
    m_commands.push_back( command );
}

const InputCommands& InputManager::commands() const {
    return m_commands;
}

void InputManager::clear() {
    m_commands.clear();
}


} // namespace common
