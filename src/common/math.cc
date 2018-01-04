//
// Created by Eddie Hoyle on 27/10/17.
//

#include "math.hh"

namespace common {

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