//
// Created by Eddie Hoyle on 14/11/17.
//

#include "input.hh"
#include "../device/device.hh"
#include "../display.hh"

#include <GLFW/glfw3.h>
#include <iostream>

namespace common {

void glfw3KeyPressCallback( GLFWwindow *window, int key, int scancode, int type, int mods ) {

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
        case GLFW_KEY_UP:
            action = InputAction::MoveForward2;
            break;
        case GLFW_KEY_DOWN:
            action = InputAction::MoveBackward2;
            break;
        case GLFW_KEY_LEFT:
            action = InputAction::TurnLeft2;
            break;
        case GLFW_KEY_RIGHT:
            action = InputAction::TurnRight2;
            break;
    }

    if ( action != InputAction::None && state != InputState::None ) {
        InputManager::instance()->add( action, state );
    }
}

void glfw3MouseScrollCallback( GLFWwindow *window, double x, double y ) {

}

void glfw3MouseButtonCallback( GLFWwindow *window, int button, int action, int mods ) {

}

void glfw3ProcessMouse( GLFWwindow* window ) {

    if ( common::DisplayManager::instance()->isFocused() ) {
        double x, y;
        glfwGetCursorPos( window, &x, &y );
        InputManager::instance()->mouse()->set( x, y );
    }

}

InputManager *InputManager::s_instance = nullptr;

InputManager *InputManager::instance() {
    if ( s_instance == nullptr ) {
        s_instance = new InputManager();
    }
    return s_instance;
}

InputManager::InputManager()
        : m_commands() {
    m_mouse = new MouseDevice();
}

InputManager::~InputManager() {
    delete m_mouse;
    delete s_instance;
}

MouseDevice *InputManager::mouse() const {
    return m_mouse;
}

void InputManager::add( InputAction action, InputState state ) {
    m_commands.push_back( new InputCommand( action, state ) );
}

const InputCommands& InputManager::commands() const {
    return m_commands;
}

void InputManager::clear() {
    for ( InputCommand* command : m_commands ) {
        delete command;
    }
    m_commands.clear();
}


} // namespace common
