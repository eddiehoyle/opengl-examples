//
// Created by Eddie Hoyle on 1/01/18.
//

#ifndef OPENGL_EXAMPLES_PLAYER_HH
#define OPENGL_EXAMPLES_PLAYER_HH


#include "entity.hh"

class Player : public Entity {

public:
    Player( const TexturedModel& model,
            const glm::vec3& position,
            const glm::vec3& rotation,
            float scale );

    void move();
    void checkInputs();

private:
    void jump();

private:
    float m_currentSpeed;
    float m_currentTurnSpeed;
    float m_upwardsSpeed;

    bool m_isInAir;

};


#endif //OPENGL_EXAMPLES_PLAYER_HH
