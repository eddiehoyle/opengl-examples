//
// Created by Eddie Hoyle on 13/01/18.
//

#include "guis.hh"

GuiTexture::GuiTexture( int texture,
                        const glm::vec2& position,
                        const glm::vec2& scale )
    : m_texture( texture ),
      m_position( position ),
      m_scale( scale ) {
}

int GuiTexture::getTextureID() const {
    return m_texture;
}

const glm::vec2& GuiTexture::getPosition() const {
    return m_position;
}

const glm::vec2& GuiTexture::getScale() const {
    return m_scale;
}
