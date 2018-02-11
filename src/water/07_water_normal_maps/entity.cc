#include "entity.hh"

Entity::Entity( const TexturedModel& model,
                const glm::vec3& position,
                const glm::vec3& rotation,
                float scale )
        : m_model( model ),
          m_position( position ),
          m_rotation( rotation ),
          m_scale( scale ),
          m_textureGrid( glm::vec2( 0, 0 ) ) {
}

Entity::Entity( const TexturedModel& model,
                const glm::vec3& position,
                const glm::vec3& rotation,
                float scale,
                const glm::vec2& textureGrid )
        : m_model( model ),
          m_position( position ),
          m_rotation( rotation ),
          m_scale( scale ),
          m_textureGrid( textureGrid ) {
}


TexturedModel Entity::getTexturedModel() const {
    return m_model;
}

void Entity::setModel( const TexturedModel& model ) {
    m_model = model;
}

void Entity::increasePosition( float x, float y, float z ) {
    m_position.x += x;
    m_position.y += y;
    m_position.z += z;
}

void Entity::increaseRotation( float x, float y, float z ) {
    m_rotation.x += x;
    m_rotation.y += y;
    m_rotation.z += z;
}

void Entity::setPosition( const glm::vec3& position ) {
    m_position = position;
}

glm::vec3 Entity::getPosition() const {
    return m_position;
}

void Entity::setRotation( const glm::vec3& rotation ) {
    m_rotation = rotation;
}

glm::vec3 Entity::getRotation() const {
    return m_rotation;
}

void Entity::setScale( float scale ) {
    m_scale = scale;
}

float Entity::getScale() const {
    return m_scale;
}

float Entity::getTextureXOffset() const {
    int column = ( int )m_textureGrid.x % m_model.getTexture().getNumberOfRows();
    return ( float )column / ( float )m_model.getTexture().getNumberOfRows();
}

float Entity::getTextureYOffset() const {
    int row = ( int )m_textureGrid.y % m_model.getTexture().getNumberOfRows();
    return ( float )row / ( float )m_model.getTexture().getNumberOfRows();
}

// ------------------------------------------------------------

EntityComponent::EntityComponent( const Entity& entity )
        : m_entity( entity ),
          Component( common::ComponentType::Entity ){
}

Entity& EntityComponent::getEntity() {
    return m_entity;
}
