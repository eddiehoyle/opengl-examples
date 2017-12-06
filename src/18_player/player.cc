//
// Created by Eddie Hoyle on 6/12/17.
//

#include "player.hh"
#include "../common/components/component.hh"

namespace common {

static const double kMoveSpeed = 100.0;
static const double kRotateSpeed = 5.0;

Player::Player() {
    addComponent( new common::MoveStateComponent );
    addComponent( new common::TransformComponent );
}

void Player::update( double elapsed ) {

    Component *moveStatecomponent = getComponent( ComponentType::MoveState );
    assert( moveStatecomponent );

    MoveStateComponent *moveComponent = moveStatecomponent->asType< MoveStateComponent >();
    assert( moveComponent );

    Component *transformBaseComponent = getComponent( ComponentType::Transform );
    assert( transformBaseComponent );

    TransformComponent *transformComponent = transformBaseComponent->asType< TransformComponent >();
    assert( transformComponent );

    double velocity = kMoveSpeed * elapsed;
    if ( moveComponent->isForward() ) {
        transformComponent->moveForward( velocity );
    }
    if ( moveComponent->isBackward() ) {
        transformComponent->moveForward( -velocity );
    }
    if ( moveComponent->isTurningLeft() ) {
        transformComponent->rotate( 0, -kRotateSpeed, 0 );
    }
    if ( moveComponent->isTurningRight() ) {
        transformComponent->rotate( 0, kRotateSpeed, 0 );
    }
}

}