//
// Created by Eddie Hoyle on 13/11/17.
//

#ifndef OPENGL_EXAMPLES_18_PLAYER_HH
#define OPENGL_EXAMPLES_18_PLAYER_HH

#include "entity.hh"

class GLFWwindow;

const float kRunSpeed = 20.0f;
const float kTurnSpeed = 160.0f;

class Player : public Entity {

public:

    Player();
    explicit Player( const TexturedModel& model,
                     const glm::vec3& position,
                     const glm::vec3& rotation,
                     float scale );

    void move();
    void checkInputs( GLFWwindow* window );

private:

private:
    float m_currentSpeed = 0;
    float m_currentTurnSpeed = 0;

};


#endif //OPENGL_EXAMPLES_18_PLAYER_HH
