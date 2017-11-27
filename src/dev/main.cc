//
// Created by Eddie Hoyle on 3/11/17.
//

#include <iostream>
#include "../common/transform.hh"
#include <float.h>

void translate() {

    Transform transform;

    glm::vec3 translates( 1.0f, 2.0f, 3.0f );
    transform.setTranslate( translates.x, translates.y, translates.z );
    std::cerr << "translate=" << glm::to_string( transform.getTranslate() ) << std::endl;
    assert( transform.getTranslate() == translates );

    transform.translate( translates.x, translates.y, translates.z );
    std::cerr << "translated=" << glm::to_string( transform.getTranslate() ) << std::endl;
    assert( transform.getTranslate() == ( translates * 2 ) );
}

void rotate() {

    Transform transform;

    glm::vec3 rotates( 45.0f, 35.0f, 0.0f );
    transform.setRotate( rotates.x, rotates.y, rotates.z );
    std::cerr << "rotate=" << glm::to_string( transform.getRotate() ) << std::endl;
    assert( transform.getRotate() == rotates );
}

void scale() {

    Transform transform;

    glm::vec3 scale( 2.0f, 3.0f, 4.0f );
    transform.setScale( scale.x, scale.y, scale.z );
    std::cerr << "scale=" << glm::to_string( transform.getScale() ) << std::endl;
    assert( transform.getScale() == scale );

    float scalar = 2;
    transform.scale( scalar, scalar, scalar );
    std::cerr << "scaled=" << glm::to_string( transform.getScale() ) << std::endl;
    assert( transform.getScale() == ( scale * scalar ) );
}

int main( void ) {

    translate();
    rotate();
    scale();

    return 0;
}