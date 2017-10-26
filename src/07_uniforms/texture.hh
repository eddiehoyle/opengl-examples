//
// Created by Eddie Hoyle on 24/10/17.
//

#ifndef OPENGL_EXAMPLES_07_TEXTURE_HH
#define OPENGL_EXAMPLES_07_TEXTURE_HH


#include <GL/glew.h>

class ModelTexture {

public:
    explicit ModelTexture( GLuint textureID );
    GLuint getID() const;

private:
    GLuint m_textureID;
};

#endif //OPENGL_EXAMPLES_07_TEXTURE_HH
