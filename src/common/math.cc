//
// Created by Eddie Hoyle on 27/10/17.
//

#include "math.hh"

namespace common {

float barryCentric( const glm::vec3& p1,
                    const glm::vec3& p2,
                    const glm::vec3& p3,
                    const glm::vec2& pos ) {
    float det = (p2.z - p3.z) * (p1.x - p3.x) + (p3.x - p2.x) * (p1.z - p3.z);
    float l1 = ((p2.z - p3.z) * (pos.x - p3.x) + (p3.x - p2.x) * (pos.y - p3.z)) / det;
    float l2 = ((p3.z - p1.z) * (pos.x - p3.x) + (p1.x - p3.x) * (pos.y - p3.z)) / det;
    float l3 = 1.0f - l1 - l2;
    return l1 * p1.y + l2 * p2.y + l3 * p3.y;
}

glm::mat4 createTransformationMatrix( const glm::vec3& translate,
                                      const glm::vec3& rotate,
                                      GLfloat scale ) {

    glm::mat4 _translate = glm::translate( glm::mat4(), translate );
    glm::mat4 _rotateX = glm::rotate( glm::mat4(), glm::radians( rotate.x ), glm::vec3( 1, 0, 0 ) );
    glm::mat4 _rotateY = glm::rotate( glm::mat4(), glm::radians( rotate.y ), glm::vec3( 0, 1, 0 ) );
    glm::mat4 _rotateZ = glm::rotate( glm::mat4(), glm::radians( rotate.z ), glm::vec3( 0, 0, 1 ) );
    glm::mat4 _rotate = _rotateX * _rotateY * _rotateZ;
    glm::mat4 _scale = glm::scale( glm::mat4(), glm::vec3( scale, scale, scale ) );
    return _translate * _rotate * _scale;

}

glm::mat4 createProjectionMatrix( const float& fov,
                                  const float& width,
                                  const float& height,
                                  const float& near,
                                  const float& far ) {
    return glm::perspectiveFov( fov,
                                width,
                                height,
                                near,
                                far );
}

}