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
#include "Entity/Events/AttackEvent.h"
#include "Entity/Events/AttackWeapon.h"
#include "Entity/Events/StartMoveEvent.h"
#include "Entity/Events/StopMoveEvent.h"
#include "Entity/Modes/AttackMode.h"
#include "Entity/Modes/AttackWeaponMode.h"
#include "Entity/Modes/IdleMode.h"
#include "Entity/Modes/MoveMode.h"
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

void PlayerEntity::DefineProperties(EntityService& entityService, const PropertyData& data)
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
    entityService.AddAttribute<CameraAttribute>();

    Subscribe({MessageType::IsKeyPressed, MessageType::IsKeyReleased, MessageType::KeyPressed});
}

void PlayerEntity::DefineModes(ModeController& modeController)
{
    auto idleMode = modeController.AddMode<IdleMode>(true);
    idleMode->BindAction(Action(ModeType::Move), EventType::StartMove);
    idleMode->BindAction(Action(ModeType::Attack), EventType::Attack);
    idleMode->BindAction(Action(ModeType::AttackWeapon), EventType::AttackWeapon);
    idleMode->BindAction(Action(), EventType::Collision);

    auto moveMode = modeController.AddMode<MoveMode>();
    moveMode->BindAction(Action(ModeType::Idle), EventType::StopMove);

    auto attackMode = modeController.AddMode<AttackMode>();
    attackMode->BindAction(Action(ModeType::Move), EventType::StartMove);
    attackMode->AddUpdateFn([](std::shared_ptr<Shape> shape) { return shape->AnimationIsCompleted(); }, ModeType::Idle);

    auto attackWeaponMode = modeController.AddMode<AttackWeaponMode>();
    attackWeaponMode->BindAction(Action(ModeType::Move), EventType::StartMove);
    attackWeaponMode->AddUpdateFn([](std::shared_ptr<Shape> shape) { return shape->AnimationIsCompleted(); },
                                  ModeType::Idle);
}

void PlayerEntity::HandleIsKeyPressed(Keyboard::Key key)
{
    if (key == Keyboard::Key::Right) {
        HandleEvent(std::make_shared<StartMoveEvent>(MoveDirection::Right, FaceDirection::Right));
    }
    else if (key == Keyboard::Key::Left) {
        HandleEvent(std::make_shared<StartMoveEvent>(MoveDirection::Left, FaceDirection::Left));
    }
    else if (key == Keyboard::Key::Down) {
        HandleEvent(std::make_shared<StartMoveEvent>(MoveDirection::Down, FaceDirection::Down));
    }
    else if (key == Keyboard::Key::Up) {
        HandleEvent(std::make_shared<StartMoveEvent>(MoveDirection::Up, FaceDirection::Up));
    }
}

void PlayerEntity::HandleIsKeyReleased(Keyboard::Key key)
{
    if (key == Keyboard::Key::Right || key == Keyboard::Key::Left || key == Keyboard::Key::Down ||
        key == Keyboard::Key::Up) {
        HandleEvent(std::make_shared<StopMoveEvent>());
    }
}

void PlayerEntity::HandleKeyPressed(Keyboard::Key key)
{
    if (key == Keyboard::Key::RControl) {
        HandleEvent(std::make_shared<AttackEvent>());
    }
    else if (key == Keyboard::Key::Space) {
        HandleEvent(std::make_shared<AttackWeaponEvent>());
    }
}

void PlayerEntity::DefineShape(EntityService& entityService, Shape& shape)
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

}  // namespace Entity

}  // namespace FA
