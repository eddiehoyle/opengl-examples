//
// Created by Eddie Hoyle on 23/01/18.
//

#include <glm/gtc/matrix_transform.hpp>
#include <iostream>
#include <glm/ext.hpp>
#include "mousePicker.hh"
#include <common/display.hh>
#include <common/command/command.hh>
#include <common/input/input.hh>

static const int RECURSION_COUNT = 200;
static const float RAY_RANGE = 600;

MousePicker::MousePicker( Camera *camera, const glm::mat4& projection, const Terrain& terrain )
        : m_camera( camera ),
          m_terrain( terrain ),
          m_projectionMatrix( projection ),
          m_viewMatrix( camera->view() ) {
}

glm::vec3 MousePicker::getCurrentRay() const {
    return m_currentRay;
}

void MousePicker::update() {

    m_viewMatrix = m_camera->view();
    m_currentRay = calculateMouseRay();

    bool inRange = intersectionInRange( 0, RAY_RANGE, m_currentRay );

    if ( inRange ) {
        m_currentTerrainPoint = binarySearch( 0, 0, RAY_RANGE, m_currentRay );
    } else {
        m_currentTerrainPoint = glm::vec3( 0, 0, 0 );
    }
}

glm::vec3 MousePicker::getCurrentTerrainPoint() const {
    return m_currentTerrainPoint;
}

glm::vec3 MousePicker::calculateMouseRay() const {
    float mouseX = common::InputManager::instance()->mouse()->windowX();
    float mouseY = common::InputManager::instance()->mouse()->windowY();
    glm::vec2 normalizedCoords = getNormalizedDeviceCoords( mouseX, mouseY );
    glm::vec4 clipCoords( normalizedCoords.x, normalizedCoords.y, -1.0f, 1.0f );
    glm::vec4 eyeCoords = toEyeCoords( clipCoords );
    glm::vec3 worldRay = toWorldCoords( eyeCoords );
    return worldRay;
}

glm::vec2 MousePicker::getNormalizedDeviceCoords( float x, float y ) const {
    float _x = ( 2.0f * x ) / common::DisplayManager::instance()->width() - 1;
    float _y = ( 2.0f * y ) / common::DisplayManager::instance()->height() - 1;
    return glm::vec2( _x, -_y ); // Might need to use -y here?
}

glm::vec4 MousePicker::toEyeCoords( const glm::vec4& clipCoords ) const {
    glm::mat4 invertedProjection = glm::inverse( m_projectionMatrix );
    glm::vec4 eyeCoords = invertedProjection * clipCoords;
    return glm::vec4( eyeCoords.x, eyeCoords.y, -1.0f, 0.0f );
}

glm::vec3 MousePicker::toWorldCoords( const glm::vec4& eyeCoords ) const {
    glm::mat4 invertedView = glm::inverse( m_viewMatrix );
    glm::vec4 rayWorld = invertedView * eyeCoords;
    glm::vec3 mouseRay = glm::normalize( glm::vec3( rayWorld.x, rayWorld.y, rayWorld.z ) );
    return mouseRay;
}

glm::vec3 MousePicker::getPointOnRay( const glm::vec3& ray, float distance ) {
    glm::vec3 scaledRay = ray * distance;
    return m_camera->position() + scaledRay;
}

glm::vec3 MousePicker::binarySearch( int count, float start, float finish, glm::vec3& ray ) {
    float half = start + ( ( finish - start ) / 2.0f );
    if ( count >= RECURSION_COUNT ) {
        glm::vec3 endPoint = getPointOnRay( ray, half );
        return endPoint;
    }
    if ( intersectionInRange( start, half, ray ) ) {
        return binarySearch( count + 1, start, half, ray );
    } else {
        return binarySearch( count + 1, half, finish, ray );
    }
}

bool MousePicker::intersectionInRange( float start, float finish, glm::vec3& ray ) {
    glm::vec3 startPoint = getPointOnRay( ray, start );
    glm::vec3 endPoint = getPointOnRay( ray, finish );
    bool a = !isUnderGround( startPoint );
    bool b = isUnderGround( endPoint );
    bool result = !isUnderGround( startPoint ) && isUnderGround( endPoint );
    return result;
}

bool MousePicker::isUnderGround( const glm::vec3& testPoint ) {
    float height = m_terrain.getHeightOfTerrain( testPoint.x, testPoint.z );
    return testPoint.y < height;
}

const Terrain& MousePicker::getTerrain( float worldX, float worldZ ) {
    return m_terrain;
}


/*
 *
	private Vector3f getPointOnRay(Vector3f ray, float distance) {
		Vector3f camPos = camera.getPosition();
		Vector3f start = new Vector3f(camPos.x, camPos.y, camPos.z);
		Vector3f scaledRay = new Vector3f(ray.x * distance, ray.y * distance, ray.z * distance);
		return Vector3f.add(start, scaledRay, null);
	}

	private Vector3f binarySearch(int count, float start, float finish, Vector3f ray) {
		float half = start + ((finish - start) / 2f);
		if (count >= RECURSION_COUNT) {
			Vector3f endPoint = getPointOnRay(ray, half);
			Terrain terrain = getTerrain(endPoint.getX(), endPoint.getZ());
			if (terrain != null) {
				return endPoint;
			} else {
				return null;
			}
		}
		if (intersectionInRange(start, half, ray)) {
			return binarySearch(count + 1, start, half, ray);
		} else {
			return binarySearch(count + 1, half, finish, ray);
		}
	}

	private boolean intersectionInRange(float start, float finish, Vector3f ray) {
		Vector3f startPoint = getPointOnRay(ray, start);
		Vector3f endPoint = getPointOnRay(ray, finish);
		if (!isUnderGround(startPoint) && isUnderGround(endPoint)) {
			return true;
		} else {
			return false;
		}
	}

	private boolean isUnderGround(Vector3f testPoint) {
		Terrain terrain = getTerrain(testPoint.getX(), testPoint.getZ());
		float height = 0;
		if (terrain != null) {
			height = terrain.getHeightOfTerrain(testPoint.getX(), testPoint.getZ());
		}
		if (testPoint.y < height) {
			return true;
		} else {
			return false;
		}
	}

	private Terrain getTerrain(float worldX, float worldZ) {
		return terrain;
	}
 */
