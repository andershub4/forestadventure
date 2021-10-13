/*
 *	Copyright (C) 2021 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#include "PlayerEntity.h"

#include <SFML/Graphics/RenderWindow.hpp>

#include "Entity/Attributes/AnimationAttribute.h"
#include "Entity/Attributes/CameraAttribute.h"
#include "Entity/Attributes/FaceDirectionAttribute.h"
#include "Entity/Attributes/SpriteAttribute.h"
#include "Entity/Attributes/TransformAttribute.h"
#include "Entity/Attributes/VelocityAttribute.h"
#include "Entity/Behaviors/AttackBehavior.h"
#include "Entity/Behaviors/AttackWeaponBehavior.h"
#include "Entity/PropertyData.h"
#include "Enum/KeyboardKey.h"
#include "Message/BroadcastMessage/IsKeyPressedMessage.h"
#include "Message/BroadcastMessage/IsKeyReleasedMessage.h"
#include "Message/BroadcastMessage/KeyPressedMessage.h"
#include "Message/MessageBus.h"

namespace FA {

namespace Entity {

PlayerEntity::PlayerEntity(EntityId id, const PropertyHandler& propertyHandler, MessageBus& messageBus)
    : BasicEntity(id, propertyHandler, messageBus)
{}

PlayerEntity::~PlayerEntity() = default;

void PlayerEntity::OnCreate(const PropertyData& data)
{
    auto t = AddAttribute<TransformAttribute>();
    t->SetPosition(data.position_);
    t->SetScale(data.scale_);
    std::vector<FaceDirection> dirs = {FaceDirection::Down, FaceDirection::Left, FaceDirection::Right,
                                       FaceDirection::Up};
    auto f = AddAttribute<FaceDirectionAttribute>();
    f->SetAvailableDirections(dirs);
    auto v = AddAttribute<VelocityAttribute>();
    v->SetVelocity(data.velocity_);
    AddBehavior<MovementBehavior>();
    AddBehavior<AttackBehavior>();
    AddBehavior<AttackWeaponBehavior>();
    AddAttribute<CameraAttribute>();
    auto a = AddAttribute<AnimationAttribute>();
    auto s = AddAttribute<SpriteAttribute>();
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
