/*
 *	Copyright (C) 2021 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#include "PlayerEntity.h"

#include <SFML/Graphics/RenderWindow.hpp>

#include "Entity/Components/AnimationComponent.h"
#include "Entity/Components/AttackComponent.h"
#include "Entity/Components/AttackWeaponComponent.h"
#include "Entity/Components/FaceDirectionComponent.h"
#include "Entity/Components/SpriteComponent.h"
#include "Enum/KeyboardKey.h"
#include "Message/BroadcastMessage/IsKeyPressedMessage.h"
#include "Message/BroadcastMessage/IsKeyReleasedMessage.h"
#include "Message/BroadcastMessage/KeyPressedMessage.h"
#include "Message/MessageBus.h"

namespace FA {

namespace Entity {

PlayerEntity::PlayerEntity(EntityId id, const ComponentHandler& componentHandler, MessageBus& messageBus)
    : BasicEntity(id, componentHandler, messageBus)
{}

PlayerEntity::~PlayerEntity() = default;

void PlayerEntity::OnCreate()
{
    AddComponent<FaceDirectionComponent>();
    AddComponent<MovementComponent>();
    AddComponent<AttackComponent>();
    AddComponent<AttackWeaponComponent>();
    auto a = AddComponent<AnimationComponent>();
    auto s = AddComponent<SpriteComponent>();
    s->AddAnimation(a);

    Subscribe({MessageType::IsKeyPressed, MessageType::IsKeyReleased, MessageType::KeyPressed});
}

void PlayerEntity::OnInit(const AnimationDb& animationDb)
{
    InitStateData(animationDb);
}

void PlayerEntity::OnDestroy()
{
    Unsubscribe({MessageType::IsKeyPressed, MessageType::IsKeyReleased, MessageType::KeyPressed});
}

void PlayerEntity::OnIsKeyPressed(Keyboard::Key key)
{
    if (key == Keyboard::Key::Right) {
        StartMove(MoveDirection::Right, FaceDirection::Right);
    }
    else if (key == Keyboard::Key::Left) {
        StartMove(MoveDirection::Left, FaceDirection::Left);
    }
    else if (key == Keyboard::Key::Up) {
        StartMove(MoveDirection::Up, FaceDirection::Up);
    }
    else if (key == Keyboard::Key::Down) {
        StartMove(MoveDirection::Down, FaceDirection::Down);
    }
}

void PlayerEntity::OnIsKeyReleased(Keyboard::Key key)
{
    StopMove();
}

void PlayerEntity::OnKeyPressed(Keyboard::Key key)
{
    if (key == Keyboard::Key::RControl) {
        Attack();
    }
    else if (key == Keyboard::Key::Space) {
        AttackWeapon();
    }
}

}  // namespace Entity

}  // namespace FA
