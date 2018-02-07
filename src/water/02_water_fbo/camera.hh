//
// Created by Eddie Hoyle on 29/10/17.
//

#ifndef OPENGL_EXAMPLES_CAMERA_19_HH
#define OPENGL_EXAMPLES_CAMERA_19_HH

#include <glm/vec3.hpp>
#include <glm/detail/type_mat.hpp>
#include "player.hh"

class Camera {

public:
    static glm::mat4 createViewMatrix( Camera* camera );

public:

    Camera();
    explicit Camera( Player* player );

    void setPlayer( Player* player );

    void move();
    void setPosition( const glm::vec3& position );
    void setPitch( float pitch );
    void setYaw( float yaw );
    void setRoll( float roll );

    glm::vec3 position() const;
    float pitch() const;
    float yaw() const;
    float roll() const;

    glm::mat4 matrix() const;
    glm::mat4 view() const;

private:
    void calculateZoom();
    void calculatePitch();
    void calculateAngleAroundPlayer();

    float calculateHorizontalDistance();
    float calculateVerticalDistance();

    void calculateCameraPosition( float horizontalDistance, float verticalDistance );

private:
    glm::vec3 m_position;
    float m_pitch;
    float m_yaw;
    float m_roll;

    Player* m_player;

    float m_distanceFromPlayer;
    float m_angleAroundPlayer;

    bool m_pitchActive;
    bool m_yawActive;

};

#endif //OPENGL_EXAMPLES_CAMERA_HH