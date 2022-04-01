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
#include "Message/BroadcastMessage/IsKeyPressedMessage.h"
#include "Message/BroadcastMessage/IsKeyReleasedMessage.h"
#include "Message/BroadcastMessage/KeyPressedMessage.h"
#include "Resource/SheetId.h"

namespace FA {

namespace Entity {

namespace {

const std::unordered_map<FaceDirection, sf::Vector2f> arrowOffset = {{FaceDirection::Down, {0.0, 30.0}},
                                                                     {FaceDirection::Left, {-10.0, 10.0}},
                                                                     {FaceDirection::Right, {10.0, 10.0}},
                                                                     {FaceDirection::Up, {0.0, -30.0}}};

const std::unordered_map<ModeType, std::unordered_map<FaceDirection, AnimationData>> animationDatas = {
    {ModeType::Move,
     {{FaceDirection::Left, {SheetId::HeroWalkSide, {{0, 0}, 6, 0}, true}},
      {FaceDirection::Right, {SheetId::HeroWalkSide, {{0, 0}, 6, 0}, false}},
      {FaceDirection::Down, {SheetId::HeroWalkFront, {{0, 0}, 6, 0}, false}},
      {FaceDirection::Up, {SheetId::HeroWalkBack, {{0, 0}, 6, 0}, false}}}},
    {ModeType::Idle,
     {{FaceDirection::Left, {SheetId::HeroIdleSide, {{0, 0}, 1, 0}, true}},
      {FaceDirection::Right, {SheetId::HeroIdleSide, {{0, 0}, 1, 0}, false}},
      {FaceDirection::Down, {SheetId::HeroIdleFront, {{0, 0}, 1, 0}, false}},
      {FaceDirection::Up, {SheetId::HeroIdleBack, {{0, 0}, 1, 0}, false}}}},
    {ModeType::Attack,
     {{FaceDirection::Left, {SheetId::HeroAttackSide, {{0, 0}, 3, 0}, true}},
      {FaceDirection::Right, {SheetId::HeroAttackSide, {{0, 0}, 3, 0}, false}},
      {FaceDirection::Down, {SheetId::HeroAttackFront, {{0, 0}, 3, 0}, false}},
      {FaceDirection::Up, {SheetId::HeroAttackBack, {{0, 0}, 3, 0}, false}}}},
    {ModeType::AttackWeapon,
     {{FaceDirection::Left, {SheetId::HeroAttackWeaponSide, {{0, 0}, 3, 0}, true}},
      {FaceDirection::Right, {SheetId::HeroAttackWeaponSide, {{0, 0}, 3, 0}, false}},
      {FaceDirection::Down, {SheetId::HeroAttackWeaponFront, {{0, 0}, 3, 0}, false}},
      {FaceDirection::Up, {SheetId::HeroAttackWeaponBack, {{0, 0}, 3, 0}, false}}}}};

}  // namespace

PlayerEntity::PlayerEntity(EntityId id, CameraManager& cameraManager, const SheetManager& sheetManager,
                           EntityManager& entityManager, MessageBus& messageBus)
    : BasicEntity(id, cameraManager, sheetManager, entityManager, messageBus)
{}

PlayerEntity::~PlayerEntity() = default;

std::vector<MessageType> PlayerEntity::Messages() const
{
    return {MessageType::IsKeyPressed, MessageType::IsKeyReleased, MessageType::KeyPressed};
}

void PlayerEntity::OnMessage(std::shared_ptr<Message> msg)
{
    if (msg->GetMessageType() == MessageType::IsKeyPressed) {
        auto m = std::dynamic_pointer_cast<IsKeyPressedMessage>(msg);
        auto key = m->GetKey();
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
    else if (msg->GetMessageType() == MessageType::IsKeyReleased) {
        auto m = std::dynamic_pointer_cast<IsKeyReleasedMessage>(msg);
        auto key = m->GetKey();
        if (key == Keyboard::Key::Right || key == Keyboard::Key::Left || key == Keyboard::Key::Down ||
            key == Keyboard::Key::Up) {
            HandleEvent(std::make_shared<StopMoveEvent>());
        }
    }
    else if (msg->GetMessageType() == MessageType::KeyPressed) {
        auto m = std::dynamic_pointer_cast<KeyPressedMessage>(msg);
        auto key = m->GetKey();
        if (key == Keyboard::Key::RControl) {
            HandleEvent(std::make_shared<AttackEvent>());
        }
        else if (key == Keyboard::Key::Space) {
            float velocity = constant::Entity::stdVelocity * 8.0f;
            HandleEvent(std::make_shared<AttackWeaponEvent>(EntityType::Arrow, arrowOffset, velocity));
        }
    }
}

void PlayerEntity::RegisterModes(ModeController& modeController)
{
    auto idleMode = modeController.RegisterMode<IdleMode>(true);
    idleMode->BindAction(Action::ChangeTo(ModeType::Move), EventType::StartMove);
    idleMode->BindAction(Action::ChangeTo(ModeType::Attack), EventType::Attack);
    idleMode->BindAction(Action::ChangeTo(ModeType::AttackWeapon), EventType::AttackWeapon);
    idleMode->BindAction(Action::Ignore(), EventType::Collision);

    auto moveMode = modeController.RegisterMode<MoveMode>();
    moveMode->BindAction(Action::ChangeTo(ModeType::Idle), EventType::StopMove);
    moveMode->BindAction(Action::Ignore(), EventType::StartMove);
    moveMode->BindAction(Action::Ignore(), EventType::Attack);
    moveMode->BindAction(Action::Ignore(), EventType::AttackWeapon);

    auto condition = [](std::shared_ptr<Shape> shape) { return shape->AnimationIsCompleted(); };

    auto attackMode = modeController.RegisterMode<AttackMode>();
    attackMode->BindAction(Action::ChangeTo(ModeType::Move), EventType::StartMove);
    attackMode->BindAction(Action::Ignore(), EventType::Attack);
    attackMode->BindAction(Action::Ignore(), EventType::AttackWeapon);
    attackMode->BindActionDuringUpdate(Action::ChangeTo(ModeType::Idle), condition);

    auto attackWeaponMode = modeController.RegisterMode<AttackWeaponMode>();
    attackWeaponMode->BindAction(Action::ChangeTo(ModeType::Move), EventType::StartMove);
    attackWeaponMode->BindAction(Action::Ignore(), EventType::Attack);
    attackWeaponMode->BindAction(Action::Ignore(), EventType::AttackWeapon);
    attackWeaponMode->BindActionDuringUpdate(Action::ChangeTo(ModeType::Idle), condition);
}

void PlayerEntity::RegisterAttributes(EntityService& entityService)
{
    entityService.RegisterProperty<float>("Scale", 1.0);
    entityService.RegisterProperty<sf::Vector2f>("Position", {0.0, 0.0});
    entityService.RegisterProperty<float>("Velocity", constant::Entity::stdVelocity);
    entityService.RegisterProperty<FaceDirection>("FaceDirection", FaceDirection::Down);
    entityService.RegisterProperty<std::vector<FaceDirection>>(
        "FaceDirections", {FaceDirection::Down, FaceDirection::Up, FaceDirection::Left, FaceDirection::Right});
    entityService.AddAttribute<CameraAttribute>();
}

void PlayerEntity::InitMode(std::shared_ptr<BasicMode> mode, const std::vector<FaceDirection>& directions,
                            const EntityService& entityService)
{
    auto modeType = mode->GetModeType();
    auto modeData = animationDatas.at(modeType);

    for (auto direction : directions) {
        auto& d = mode->AddDirection(direction);
        d.animation_ = entityService.MakeAnimation(modeData.at(direction));
    }
}

void PlayerEntity::InitModes(const ModeController& modeController, const EntityService& entityService,
                             const AttributeData& data)
{
    auto directions = entityService.GetProperty<std::vector<FaceDirection>>("FaceDirections");

    InitMode(modeController.GetMode(ModeType::Idle), directions, entityService);
    InitMode(modeController.GetMode(ModeType::Move), directions, entityService);
    InitMode(modeController.GetMode(ModeType::Attack), directions, entityService);
    InitMode(modeController.GetMode(ModeType::AttackWeapon), directions, entityService);
}

}  // namespace Entity

}  // namespace FA
