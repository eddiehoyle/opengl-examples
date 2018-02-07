//
// Created by Eddie Hoyle on 23/01/18.
//

#ifndef OPENGL_EXAMPLES_MOUSEPICKER_HH
#define OPENGL_EXAMPLES_MOUSEPICKER_HH


#include <glm/glm.hpp>
#include "camera.hh"

class MousePicker {
public:
    MousePicker( Camera* camera, const glm::mat4& projection, const Terrain& terrrain );
    glm::vec3 getCurrentRay() const;
    void update();
    glm::vec3 getCurrentTerrainPoint() const;

private:
    glm::vec3 calculateMouseRay() const;
    glm::vec2 getNormalizedDeviceCoords( float x, float y ) const;
    glm::vec4 toEyeCoords( const glm::vec4& clipCoords ) const;
    glm::vec3 toWorldCoords( const glm::vec4& eyeCoords ) const;

    glm::vec3 getPointOnRay( const glm::vec3& ray, float distance );
    glm::vec3 binarySearch( int count, float start, float finish, glm::vec3& ray );
    bool intersectionInRange( float start, float finish, glm::vec3& ray );
    bool isUnderGround( const glm::vec3& testPoint );
    const Terrain& getTerrain( float worldX, float worldZ );


private:
    glm::vec3 m_currentRay;
    glm::mat4 m_projectionMatrix;
    glm::mat4 m_viewMatrix;
    Camera* m_camera;

    Terrain m_terrain;
    glm::vec3 m_currentTerrainPoint;
};


#endif //OPENGL_EXAMPLES_MOUSEPICKER_HH
