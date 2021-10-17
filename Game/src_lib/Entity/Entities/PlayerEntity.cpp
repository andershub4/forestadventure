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
#include "Entity/Attributes/ShapeAttribute.h"
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

PlayerEntity::PlayerEntity(EntityId id, CameraManager& cameraManager, MessageBus& messageBus)
    : BasicEntity(id, EntityType::Player, cameraManager, messageBus)
{}

PlayerEntity::~PlayerEntity() = default;

void PlayerEntity::OnCreate(EntityService& handler, const PropertyData& data)
{
    auto t = handler.AddAttribute<TransformAttribute>();
    t->SetPosition(data.position_);
    t->SetScale(data.scale_);
    std::vector<FaceDirection> dirs = {FaceDirection::Down, FaceDirection::Left, FaceDirection::Right,
                                       FaceDirection::Up};
    auto f = handler.AddAttribute<FaceDirectionAttribute>();
    f->SetAvailableDirections(dirs);
    auto v = handler.AddAttribute<VelocityAttribute>();
    v->SetVelocity(data.velocity_);
    handler.AddBehavior<MovementBehavior>();
    handler.AddBehavior<AttackBehavior>();
    handler.AddBehavior<AttackWeaponBehavior>();
    handler.AddAttribute<CameraAttribute>();
    auto a = handler.AddAttribute<AnimationAttribute>();
    auto s = handler.AddAttribute<ShapeAttribute>();
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
