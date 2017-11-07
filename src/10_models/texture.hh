//
// Created by Eddie Hoyle on 24/10/17.
//

#ifndef OPENGL_EXAMPLES_10_TEXTURE_HH
#define OPENGL_EXAMPLES_10_TEXTURE_HH


#include <GL/glew.h>

class ModelTexture {

public:
    explicit ModelTexture( GLuint textureID );
    GLuint getID() const;

    GLfloat getShineDamper() const;

    void setShineDamper( GLfloat value );

    GLfloat getReflectivity() const;

    void setReflectivity( GLfloat value );

private:
    GLuint m_textureID;
    GLfloat m_shineDamper;
    GLfloat m_reflectivity;
};

#endif //OPENGL_EXAMPLES_10_TEXTURE_HH
