//
// Created by Eddie Hoyle on 10/12/17.
//

#include "bunny.hh"
#include "entity.hh"
#include "../common/components/transformComponent.hh"
#include "../common/resources.hh"
#include "../common/components/moveComponent.hh"
#include "OBJLoader.hh"

const float kJumpVelocity = 4.0f;
const float kGravity = -500.0f;
const float kTerrainHeight = 0.0f;


Bunny::Bunny()
    : m_upwardsSpeed( 0 ) {

    addComponent( new common::MoveStateComponent );
    addComponent( new common::TransformComponent );

    // Bunny
    bool result;
    const std::string bunnyModelPath = common::getResource( "bunny.obj", result );
    assert( result );
    const std::string bunnyTexturePath = common::getResource( "white.png", result );
    assert( result );

    Loader loader = Loader();

    // Model, texture, entity
    RawModel bunnyModel = OBJLoader::loadObjModel( bunnyModelPath, loader );
    ModelTexture bunnyTexture( loader.loadTexture( bunnyTexturePath ) );
    bunnyTexture.setShineDamper( 10.0f );
    bunnyTexture.setReflectivity( 1.0f );
    bunnyTexture.setHasTransparency( false );
    bunnyTexture.setUseFakeLighting( false );
    TexturedModel bunnyTexturedModel( bunnyModel, bunnyTexture );
    Entity bunnyEntity( bunnyTexturedModel,
                        glm::vec3( 0, 0, 0 ),
                        glm::vec3( 0, 0, 0 ),
                        1 );

    // Add entity
    addComponent( new EntityComponent( bunnyEntity ) );
}

Entity& Bunny::getEntity() const {
    EntityComponent* entityComponent =
            getComponent( common::ComponentType::Entity )->asType< EntityComponent >();
    assert( entityComponent );
    return entityComponent->getEntity();
}

void Bunny::update( double elapsed ) {

    common::MoveStateComponent *moveStateComponent =
            getComponent( common::ComponentType::MoveState )->asType< common::MoveStateComponent >();
    assert( moveStateComponent );


    common::TransformComponent *transformComponent =
            getComponent( common::ComponentType::Transform )->asType< common::TransformComponent >();
    assert( transformComponent );

    double velocity = 100.0 * elapsed;
    if ( moveStateComponent->isForward() ) {
        transformComponent->moveForward( -velocity );
    }
    if ( moveStateComponent->isBackward() ) {
        transformComponent->moveForward( velocity );
    }
    if ( moveStateComponent->isTurningLeft() ) {
        transformComponent->rotate( 0, -velocity * 3, 0 );
    }
    if ( moveStateComponent->isTurningRight() ) {
        transformComponent->rotate( 0, velocity * 3, 0 );
    }


// bunny.cc update()
// add logic
    if ( moveStateComponent->isJumping() && ( transformComponent->getTranslate().y == kTerrainHeight ) ) {
        m_upwardsSpeed = kJumpVelocity * 30.0f; // <-- fix
    }

    m_upwardsSpeed += kGravity * elapsed;
    transformComponent->translate( 0.0f, m_upwardsSpeed * elapsed, 0.0f );

// reset
    if ( transformComponent->getTranslate().y < kTerrainHeight ) {
        transformComponent->setTranslate( transformComponent->getTranslate().x, kTerrainHeight,
                                          transformComponent->getTranslate().z );
    }
}
