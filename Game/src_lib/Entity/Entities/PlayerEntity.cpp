/*
 *	Copyright (C) 2021 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#include "PlayerEntity.h"

#include <sstream>

#include <SFML/Graphics/RenderWindow.hpp>

#include "Entity/Attributes/CameraAttribute.h"
#include "Entity/Attributes/FaceDirectionAttribute.h"
#include "Entity/Attributes/TransformAttribute.h"
#include "Entity/Attributes/VelocityAttribute.h"
#include "Entity/Modes/AttackMode.h"
#include "Entity/Modes/AttackWeaponMode.h"
#include "Entity/Modes/IdleMode.h"
#include "Entity/Modes/MovementMode.h"
#include "Entity/PropertyData.h"
#include "Entity/Shapes/AnimationShape.h"
#include "Entity/Shapes/RectangleShape.h"
#include "Entity/Shapes/Shape.h"
#include "Enum/KeyboardKey.h"
#include "Message/BroadcastMessage/IsKeyPressedMessage.h"
#include "Message/BroadcastMessage/IsKeyReleasedMessage.h"
#include "Message/BroadcastMessage/KeyPressedMessage.h"
#include "Message/MessageBus.h"

namespace FA {

namespace Entity {

PlayerEntity::PlayerEntity(EntityId id, CameraManager& cameraManager, const AnimationDb& animationDb,
                           MessageBus& messageBus)
    : BasicEntity(id, EntityType::Player, cameraManager, animationDb, messageBus)
{}

PlayerEntity::~PlayerEntity() = default;

void PlayerEntity::OnAddProperties(EntityService& entityService, const PropertyData& data)
{
    auto t = entityService.AddAttribute<TransformAttribute>();
    t->SetPosition(data.position_);
    t->SetScale(data.scale_);
    std::vector<FaceDirection> dirs = {FaceDirection::Down, FaceDirection::Left, FaceDirection::Right,
                                       FaceDirection::Up};
    auto f = entityService.AddAttribute<FaceDirectionAttribute>();
    f->SetAvailableDirections(dirs);
    auto v = entityService.AddAttribute<VelocityAttribute>();
    v->SetVelocity(data.velocity_);
    entityService.AddMode<IdleMode>();
    entityService.AddMode<MovementMode>();
    entityService.AddMode<AttackMode>();
    entityService.AddMode<AttackWeaponMode>();
    entityService.AddAttribute<CameraAttribute>();

    Subscribe({MessageType::IsKeyPressed, MessageType::IsKeyReleased, MessageType::KeyPressed});
}

void PlayerEntity::OnAddShape(EntityService& entityService, Shape& shape)
{
    auto lookupKeyFunc = [](FrameType frameType, FaceDirection faceDir) {
        std::stringstream ss;
        ss << frameType << "_" << faceDir;
        return ss.str();
    };

    auto a = std::make_shared<AnimationShape>(lookupKeyFunc);
    auto dirs = entityService.GetAttribute<FaceDirectionAttribute>()->GetAvailableDirections();

    for (auto frameType : entityService.GetFrameTypes()) {
        if (frameType == FrameType::Undefined) continue;
        for (auto faceDir : dirs) {
            auto animation = entityService.GetAnimation(frameType, faceDir);
            a->AddAnimation(frameType, faceDir, animation);
        }
    }

    shape.AddAnimationShape(a);

    auto r = std::make_shared<RectangleShape>();
    r->SetSize({1.0, 1.0});

    shape.AddBasicShape(r);
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
