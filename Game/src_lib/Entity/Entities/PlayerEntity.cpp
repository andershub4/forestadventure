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
#include "Enum/MessageType.h"
#include "Resource/SheetId.h"

namespace FA {

namespace Entity {

namespace {

FrameType ModeTypeToFrameType(ModeType modeType)
{
    switch (modeType) {
        case ModeType::Attack:
            return FrameType::Attack;
        case ModeType::AttackWeapon:
            return FrameType::AttackWeapon;
        case ModeType::Idle:
            return FrameType::Idle;
        case ModeType::Move:
            return FrameType::Move;
        default:
            return FrameType::Undefined;
    }
}

}  // namespace

PlayerEntity::PlayerEntity(EntityId id, CameraManager& cameraManager, SheetManager& sheetManager,
                           MessageBus& messageBus)
    : BasicEntity(id, cameraManager, sheetManager, messageBus)
{}

PlayerEntity::~PlayerEntity() = default;

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

std::vector<MessageType> PlayerEntity::Messages() const
{
    return {MessageType::IsKeyPressed, MessageType::IsKeyReleased, MessageType::KeyPressed};
}

std::vector<AnimationData> PlayerEntity::Animations() const
{
    std::vector<AnimationData> data = {
        {SheetId::HeroWalkSide, {{0, 0}, 6, 0}, true, FrameType::Move, FaceDirection::Left},
        {SheetId::HeroWalkSide, {{0, 0}, 6, 0}, false, FrameType::Move, FaceDirection::Right},
        {SheetId::HeroWalkFront, {{0, 0}, 6, 0}, false, FrameType::Move, FaceDirection::Down},
        {SheetId::HeroWalkBack, {{0, 0}, 6, 0}, false, FrameType::Move, FaceDirection::Up},
        {SheetId::HeroIdleSide, {{0, 0}, 1, 0}, true, FrameType::Idle, FaceDirection::Left},
        {SheetId::HeroIdleSide, {{0, 0}, 1, 0}, false, FrameType::Idle, FaceDirection::Right},
        {SheetId::HeroIdleFront, {{0, 0}, 1, 0}, false, FrameType::Idle, FaceDirection::Down},
        {SheetId::HeroIdleBack, {{0, 0}, 1, 0}, false, FrameType::Idle, FaceDirection::Up},
        {SheetId::HeroAttackSide, {{0, 0}, 3, 0}, true, FrameType::Attack, FaceDirection::Left},
        {SheetId::HeroAttackSide, {{0, 0}, 3, 0}, false, FrameType::Attack, FaceDirection::Right},
        {SheetId::HeroAttackFront, {{0, 0}, 3, 0}, false, FrameType::Attack, FaceDirection::Down},
        {SheetId::HeroAttackBack, {{0, 0}, 3, 0}, false, FrameType::Attack, FaceDirection::Up},
        {SheetId::HeroAttackWeaponSide, {{0, 0}, 3, 0}, true, FrameType::AttackWeapon, FaceDirection::Left},
        {SheetId::HeroAttackWeaponSide, {{0, 0}, 3, 0}, false, FrameType::AttackWeapon, FaceDirection::Right},
        {SheetId::HeroAttackWeaponFront, {{0, 0}, 3, 0}, false, FrameType::AttackWeapon, FaceDirection::Down},
        {SheetId::HeroAttackWeaponBack, {{0, 0}, 3, 0}, false, FrameType::AttackWeapon, FaceDirection::Up}};

    return data;
}

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
}

void PlayerEntity::DefineModes(ModeController& modeController)
{
    auto idleMode = modeController.AddMode<IdleMode>(true);
    idleMode->BindAction(Action::ChangeTo(ModeType::Move), EventType::StartMove);
    idleMode->BindAction(Action::ChangeTo(ModeType::Attack), EventType::Attack);
    idleMode->BindAction(Action::ChangeTo(ModeType::AttackWeapon), EventType::AttackWeapon);
    idleMode->BindAction(Action::Ignore(), EventType::Collision);

    auto moveMode = modeController.AddMode<MoveMode>();
    moveMode->BindAction(Action::ChangeTo(ModeType::Idle), EventType::StopMove);
    moveMode->BindAction(Action::Ignore(), EventType::StartMove);
    moveMode->BindAction(Action::Ignore(), EventType::Attack);
    moveMode->BindAction(Action::Ignore(), EventType::AttackWeapon);

    auto condition = [](std::shared_ptr<Shape> shape) { return shape->AnimationIsCompleted(); };

    auto attackMode = modeController.AddMode<AttackMode>();
    attackMode->BindAction(Action::ChangeTo(ModeType::Move), EventType::StartMove);
    attackMode->BindAction(Action::Ignore(), EventType::Attack);
    attackMode->BindAction(Action::Ignore(), EventType::AttackWeapon);
    attackMode->BindActionDuringUpdate(Action::ChangeTo(ModeType::Idle), condition);

    auto attackWeaponMode = modeController.AddMode<AttackWeaponMode>();
    attackWeaponMode->BindAction(Action::ChangeTo(ModeType::Move), EventType::StartMove);
    attackWeaponMode->BindAction(Action::Ignore(), EventType::Attack);
    attackWeaponMode->BindAction(Action::Ignore(), EventType::AttackWeapon);
    attackWeaponMode->BindActionDuringUpdate(Action::ChangeTo(ModeType::Idle), condition);
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

    for (auto modeType : entityService.GetModeTypes()) {
        auto frameType = ModeTypeToFrameType(modeType);
        if (frameType == FrameType::Undefined) continue;
        for (auto faceDir : dirs) {
            auto animation = entityService.GetAnimation(Type(), frameType, faceDir);
            a->AddAnimation(frameType, faceDir, animation);
        }
    }

    shape.AddAnimationShape(a);

#ifdef _DEBUG
    auto r = std::make_shared<RectangleShape>();
    r->SetSize({1.0, 1.0});

    shape.AddBasicShape(r);
#endif
}

}  // namespace Entity

}  // namespace FA
