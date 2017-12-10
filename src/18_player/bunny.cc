//
// Created by Eddie Hoyle on 10/12/17.
//

#include "bunny.hh"
#include "entity.hh"
#include "../common/components/transformComponent.hh"
#include "../common/resources.hh"
#include "../common/components/moveComponent.hh"
#include "OBJLoader.hh"

Bunny::Bunny() {
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
    Model bunnyModel = OBJLoader::loadObjModel( bunnyModelPath, loader );
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

const Entity& Bunny::getEntity() const {
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
        transformComponent->moveForward( velocity );
    }
    if ( moveStateComponent->isBackward() ) {
        transformComponent->moveForward( -velocity );
    }
    if ( moveStateComponent->isStrafeLeft() ) {
        transformComponent->moveRight( -velocity );
    }
    if ( moveStateComponent->isStrafeRight() ) {
        transformComponent->moveRight( velocity );
    }
}
