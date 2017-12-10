//
// Created by Eddie Hoyle on 28/10/17.
//

#ifndef OPENGL_EXAMPLES_17_ENTITY_HH
#define OPENGL_EXAMPLES_17_ENTITY_HH


#include <glm/vec3.hpp>
#include "model.hh"
#include "../common/components/component.hh"

class Entity {

public:
    explicit  Entity( const TexturedModel& model,
                      const glm::vec3& position,
                      const glm::vec3& rotation,
                      float scale );

    TexturedModel getTexturedModel() const;
    void setModel( const TexturedModel& model );

    void increasePosition( float x, float y, float z );

    void increaseRotation( float x, float y, float z );

    void setPosition( const glm::vec3& position );
    glm::vec3 getPosition() const;

    void setRotation( const glm::vec3& rotation );
    glm::vec3 getRotation() const;

    void setScale( float scale );
    float getScale() const;

    /// Temp
    bool operator<( const Entity& rhs ) const{
        return getTexturedModel().getModel().getVaoID() < rhs.getTexturedModel().getModel().getVaoID();
    }

private:
    TexturedModel m_model;
    glm::vec3 m_position;
    glm::vec3 m_rotation;
    float m_scale;

};

// ------------------------------------------------------------

/// A simple
class EntityComponent : public common::Component {
public:
    explicit EntityComponent( const Entity& entity );
    const Entity& getEntity() const;
private:
    Entity m_entity;
};


#endif //OPENGL_EXAMPLES_17_ENTITY_HH
