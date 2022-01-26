/*
 *	Copyright (C) 2021 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#include "PlayerEntity.h"

#include <SFML/Graphics/RenderWindow.hpp>

#include "Constant/Entity.h"
#include "Entity/AttributeData.h"
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
#include "Entity/Shape.h"
#include "Enum/KeyboardKey.h"
#include "Enum/MessageType.h"
#include "Resource/SheetId.h"

namespace FA {

namespace Entity {

namespace {

const std::unordered_map<FaceDirection, sf::Vector2f> arrowOffset = {{FaceDirection::Down, {0.0, 30.0}},
                                                                     {FaceDirection::Left, {-10.0, 10.0}},
                                                                     {FaceDirection::Right, {10.0, 10.0}},
                                                                     {FaceDirection::Up, {0.0, -30.0}}};

}  // namespace

PlayerEntity::PlayerEntity(EntityId id, CameraManager& cameraManager, const SheetManager& sheetManager,
                           EntityManager& entityManager, MessageBus& messageBus)
    : BasicEntity(id, cameraManager, sheetManager, entityManager, messageBus)
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
        float velocity = constant::Entity::stdVelocity * 8.0f;
        HandleEvent(std::make_shared<AttackWeaponEvent>(EntityType::Arrow, arrowOffset, velocity));
    }
}

std::vector<MessageType> PlayerEntity::Messages() const
{
    return {MessageType::IsKeyPressed, MessageType::IsKeyReleased, MessageType::KeyPressed};
}

std::vector<AnimationData> PlayerEntity::AnimationDataStore() const
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

void PlayerEntity::AddAttributes(EntityService& entityService, const AttributeData& data)
{
    auto t = entityService.AddAttribute<TransformAttribute>();
    t->SetPosition(data.position_);
    t->SetScale(data.scale_);
    auto f = entityService.AddAttribute<FaceDirectionAttribute>();
    f->SetDirection(data.faceDir_);
    auto v = entityService.AddAttribute<VelocityAttribute>();
    v->SetVelocity(data.velocity_);
    entityService.AddAttribute<CameraAttribute>();
}

void PlayerEntity::RegisterModes(ModeController& modeController, const EntityService& entityService)
{
    auto idleMode = modeController.RegisterMode<IdleMode>(true);
    idleMode->BindAction(Action::ChangeTo(ModeType::Move), EventType::StartMove);
    idleMode->BindAction(Action::ChangeTo(ModeType::Attack), EventType::Attack);
    idleMode->BindAction(Action::ChangeTo(ModeType::AttackWeapon), EventType::AttackWeapon);
    idleMode->BindAction(Action::Ignore(), EventType::Collision);

    auto& ileft = idleMode->AddDirection(FaceDirection::Left);
    auto& iright = idleMode->AddDirection(FaceDirection::Right);
    auto& iup = idleMode->AddDirection(FaceDirection::Up);
    auto& idown = idleMode->AddDirection(FaceDirection::Down);
    ileft.animation_ = entityService.GetAnimation(Type(), FrameType::Idle, FaceDirection::Left);
    iright.animation_ = entityService.GetAnimation(Type(), FrameType::Idle, FaceDirection::Right);
    iup.animation_ = entityService.GetAnimation(Type(), FrameType::Idle, FaceDirection::Up);
    idown.animation_ = entityService.GetAnimation(Type(), FrameType::Idle, FaceDirection::Down);

    auto moveMode = modeController.RegisterMode<MoveMode>();
    moveMode->BindAction(Action::ChangeTo(ModeType::Idle), EventType::StopMove);
    moveMode->BindAction(Action::Ignore(), EventType::StartMove);
    moveMode->BindAction(Action::Ignore(), EventType::Attack);
    moveMode->BindAction(Action::Ignore(), EventType::AttackWeapon);

    auto& mleft = moveMode->AddDirection(FaceDirection::Left);
    auto& mright = moveMode->AddDirection(FaceDirection::Right);
    auto& mup = moveMode->AddDirection(FaceDirection::Up);
    auto& mdown = moveMode->AddDirection(FaceDirection::Down);
    mleft.animation_ = entityService.GetAnimation(Type(), FrameType::Move, FaceDirection::Left);
    mright.animation_ = entityService.GetAnimation(Type(), FrameType::Move, FaceDirection::Right);
    mup.animation_ = entityService.GetAnimation(Type(), FrameType::Move, FaceDirection::Up);
    mdown.animation_ = entityService.GetAnimation(Type(), FrameType::Move, FaceDirection::Down);

    auto condition = [](std::shared_ptr<Shape> shape) { return shape->AnimationIsCompleted(); };

    auto attackMode = modeController.RegisterMode<AttackMode>();
    attackMode->BindAction(Action::ChangeTo(ModeType::Move), EventType::StartMove);
    attackMode->BindAction(Action::Ignore(), EventType::Attack);
    attackMode->BindAction(Action::Ignore(), EventType::AttackWeapon);
    attackMode->BindActionDuringUpdate(Action::ChangeTo(ModeType::Idle), condition);

    auto& aleft = attackMode->AddDirection(FaceDirection::Left);
    auto& aright = attackMode->AddDirection(FaceDirection::Right);
    auto& aup = attackMode->AddDirection(FaceDirection::Up);
    auto& adown = attackMode->AddDirection(FaceDirection::Down);
    aleft.animation_ = entityService.GetAnimation(Type(), FrameType::Attack, FaceDirection::Left);
    aright.animation_ = entityService.GetAnimation(Type(), FrameType::Attack, FaceDirection::Right);
    aup.animation_ = entityService.GetAnimation(Type(), FrameType::Attack, FaceDirection::Up);
    adown.animation_ = entityService.GetAnimation(Type(), FrameType::Attack, FaceDirection::Down);

    auto attackWeaponMode = modeController.RegisterMode<AttackWeaponMode>();
    attackWeaponMode->BindAction(Action::ChangeTo(ModeType::Move), EventType::StartMove);
    attackWeaponMode->BindAction(Action::Ignore(), EventType::Attack);
    attackWeaponMode->BindAction(Action::Ignore(), EventType::AttackWeapon);
    attackWeaponMode->BindActionDuringUpdate(Action::ChangeTo(ModeType::Idle), condition);

    auto& awleft = attackWeaponMode->AddDirection(FaceDirection::Left);
    auto& awright = attackWeaponMode->AddDirection(FaceDirection::Right);
    auto& awup = attackWeaponMode->AddDirection(FaceDirection::Up);
    auto& awdown = attackWeaponMode->AddDirection(FaceDirection::Down);
    awleft.animation_ = entityService.GetAnimation(Type(), FrameType::AttackWeapon, FaceDirection::Left);
    awright.animation_ = entityService.GetAnimation(Type(), FrameType::AttackWeapon, FaceDirection::Right);
    awup.animation_ = entityService.GetAnimation(Type(), FrameType::AttackWeapon, FaceDirection::Up);
    awdown.animation_ = entityService.GetAnimation(Type(), FrameType::AttackWeapon, FaceDirection::Down);
}

}  // namespace Entity

}  // namespace FA
