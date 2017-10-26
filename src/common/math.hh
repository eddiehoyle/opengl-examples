//
// Created by Eddie Hoyle on 27/10/17.
//

#ifndef OPENGL_EXAMPLES_COMMON_MATH_HH
#define OPENGL_EXAMPLES_COMMON_MATH_HH

#include <glm/glm.hpp>
#include <glm/ext.hpp>
#include <GL/glew.h>

namespace common {

glm::mat4 createTransformationMatrix( const glm::vec3& translate,
                                      const glm::vec3& rotate,
                                      GLfloat scale ) {

    // Move pivot with translates
    glm::vec3 pivot = translate;

    // Create matrices
    glm::mat4 translate_matrix( 1.0f );
    glm::mat4 rotate_matrix( 1.0f );
    glm::mat4 scale_matrix( 1.0f );

    translate_matrix = glm::translate( translate_matrix, pivot);

    rotate_matrix = glm::translate( rotate_matrix, pivot );
    rotate_matrix = glm::rotate( rotate_matrix, glm::radians( -( float )rotate.x ), glm::vec3( 1, 0, 0 ) );
    rotate_matrix = glm::rotate( rotate_matrix, glm::radians( -( float )rotate.y ), glm::vec3( 0, 1, 0 ) );
    rotate_matrix = glm::rotate( rotate_matrix, glm::radians( -( float )rotate.z ), glm::vec3( 0, 0, 1 ) );
    rotate_matrix = glm::translate( rotate_matrix, -pivot );

    scale_matrix = glm::translate( scale_matrix, pivot );
    scale_matrix = glm::scale( scale_matrix, glm::vec3( scale, scale, scale ) );
    scale_matrix = glm::translate( scale_matrix, -pivot );

    return scale_matrix * rotate_matrix * translate_matrix;

}


}


#endif //OPENGL_EXAMPLES_COMMON_MATH_HH
