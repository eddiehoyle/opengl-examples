//
// Created by Eddie Hoyle on 13/01/18.
//

#ifndef OPENGL_EXAMPLES_GUIS_HH
#define OPENGL_EXAMPLES_GUIS_HH


#include <glm/vec2.hpp>

class GuiTexture {

public:
    GuiTexture( int texture,
                const glm::vec2& position,
                const glm::vec2& scale );

    int getTextureID() const;
    const glm::vec2& getPosition() const;
    const glm::vec2& getScale() const;

private:
    int m_texture;
    glm::vec2 m_position;
    glm::vec2 m_scale;
};


#endif //OPENGL_EXAMPLES_GUIS_HH
