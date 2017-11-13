//
// Created by Eddie Hoyle on 13/11/17.
//

#include "player.hh"
#include <GLFW/glfw3.h>
#include <cstdio>

Player::Player( const TexturedModel& model,
                const glm::vec3& position,
                const glm::vec3& rotation,
                float scale )
        : Entity( model, position, rotation, scale ) {
}

void Player::move() {

}

void Player::checkInputs( GLFWwindow* window ) {

    if ( glfwGetKey( window, GLFW_KEY_W ) == GLFW_PRESS ) {
        m_currentSpeed = kRunSpeed;
        printf( "W\n" );
    }
    if ( glfwGetKey( window, GLFW_KEY_S ) == GLFW_PRESS ) {
        m_currentSpeed = -kRunSpeed;
        printf( "S\n" );
    }
    if ( glfwGetKey( window, GLFW_KEY_A ) == GLFW_PRESS ) {
        m_currentTurnSpeed = kTurnSpeed;
        printf( "A\n" );
    }
    if ( glfwGetKey( window, GLFW_KEY_D ) == GLFW_PRESS ) {
        m_currentTurnSpeed = -kTurnSpeed;
        printf( "D\n" );
    }
}
