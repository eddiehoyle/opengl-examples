//
// Created by Eddie Hoyle on 27/10/17.
//

#ifndef OPENGL_EXAMPLES_COMMON_MATH_HH
#define OPENGL_EXAMPLES_COMMON_MATH_HH

#include <glm/glm.hpp>
#include <glm/ext.hpp>
#include <GL/glew.h>
#include "scene/camera.hh"

namespace common {

/// TODO
float barryCentric( const glm::vec3& p1,
                    const glm::vec3& p2,
                    const glm::vec3& p3,
                    const glm::vec2& pos );

/// TODO
glm::mat4 createTransformationMatrix( const glm::vec3& translate,
                                      const glm::vec3& rotate,
                                      GLfloat scale );

/// TODO
glm::mat4 createProjectionMatrix( const float& fov,
                                  const float& width,
                                  const float& height,
                                  const float& near,
                                  const float& far );

}


#endif //OPENGL_EXAMPLES_COMMON_MATH_HH
