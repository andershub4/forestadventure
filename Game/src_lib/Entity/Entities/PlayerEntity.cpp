/*
 *	Copyright (C) 2021 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#include "PlayerEntity.h"

#include <sstream>

#include <SFML/Graphics/RenderWindow.hpp>

#include "Constant/Entity.h"
#include "Entity/Abilities/AnimationAbility.h"
#include "Entity/Abilities/MoveAbility.h"
#include "Entity/Abilities/ShootAbility.h"
#include "Entity/Events/AttackEvent.h"
#include "Entity/Events/AttackWeapon.h"
#include "Entity/Events/StartMoveEvent.h"
#include "Entity/Events/StopMoveEvent.h"
#include "Entity/PropertyData.h"
#include "Entity/States/BasicState.h"
#include "Enum/KeyboardKey.h"
#include "Enum/MessageType.h"
#include "Message/BroadcastMessage/IsKeyPressedMessage.h"
#include "Message/BroadcastMessage/IsKeyReleasedMessage.h"
#include "Message/BroadcastMessage/KeyPressedMessage.h"
#include "Resource/SheetId.h"

namespace FA {

namespace Entity {

namespace {

const std::unordered_map<FaceDirection, sf::Vector2f> arrowOffset = {{FaceDirection::Down, {0.0, 15.0}},
                                                                     {FaceDirection::Left, {-15.0, 5.0}},
                                                                     {FaceDirection::Right, {15.0, 5.0}},
                                                                     {FaceDirection::Up, {0.0, -15.0}}};

const std::unordered_map<StateType, std::unordered_map<FaceDirection, AnimationData>> animationDatas = {
    {StateType::Move,
     {{FaceDirection::Left, {SheetId::HeroWalkSide, {{0, 0}, 6, 0}, true}},
      {FaceDirection::Right, {SheetId::HeroWalkSide, {{0, 0}, 6, 0}, false}},
      {FaceDirection::Down, {SheetId::HeroWalkFront, {{0, 0}, 6, 0}, false}},
      {FaceDirection::Up, {SheetId::HeroWalkBack, {{0, 0}, 6, 0}, false}}}},
    {StateType::Idle,
     {{FaceDirection::Left, {SheetId::HeroIdleSide, {{0, 0}, 1, 0}, true}},
      {FaceDirection::Right, {SheetId::HeroIdleSide, {{0, 0}, 1, 0}, false}},
      {FaceDirection::Down, {SheetId::HeroIdleFront, {{0, 0}, 1, 0}, false}},
      {FaceDirection::Up, {SheetId::HeroIdleBack, {{0, 0}, 1, 0}, false}}}},
    {StateType::Attack,
     {{FaceDirection::Left, {SheetId::HeroAttackSide, {{0, 0}, 3, 0}, true}},
      {FaceDirection::Right, {SheetId::HeroAttackSide, {{0, 0}, 3, 0}, false}},
      {FaceDirection::Down, {SheetId::HeroAttackFront, {{0, 0}, 3, 0}, false}},
      {FaceDirection::Up, {SheetId::HeroAttackBack, {{0, 0}, 3, 0}, false}}}},
    {StateType::AttackWeapon,
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
            HandleEvent(std::make_shared<AttackWeaponEvent>(EntityType::Arrow));
        }
    }
}

void PlayerEntity::OnBeginMove(FaceDirection faceDirection)
{
    propertyManager_.Set("FaceDirection", faceDirection);
}

void PlayerEntity::OnUpdateMove(const sf::Vector2f& delta)
{
    propertyManager_.GetRef<sf::Vector2f>("Position") += delta;
}

void PlayerEntity::OnExitShoot()
{
    auto dir = propertyManager_.Get<FaceDirection>("FaceDirection");
    auto position = propertyManager_.Get<sf::Vector2f>("Position") + arrowOffset.at(dir);

    entityService_.SpawnEntity(EntityType::Arrow, dir, position);
}

void PlayerEntity::RegisterProperties()
{
    propertyManager_.Register<sf::Vector2f>("Position", {0.0, 0.0});
    propertyManager_.Register<float>("Rotation", 0.0);
    propertyManager_.Register<FaceDirection>("FaceDirection", FaceDirection::Down);
}

void PlayerEntity::RegisterShape()
{
    shape_ = CreateShape();
    shape_.AddSprite("Main");
}

void PlayerEntity::UpdateAnimation(const Animation& animation)
{
    auto& sprite = shape_.GetSprite("Main");
    animation.ApplyTo(sprite);
}

void PlayerEntity::RegisterStates(const PropertyData& data)
{
    auto getKey = [this]() {
        std::stringstream ss;
        auto dir = propertyManager_.Get<FaceDirection>("FaceDirection");
        ss << dir;
        return ss.str();
    };
    auto updateAnimation = [this](const Animation& animation) { UpdateAnimation(animation); };
    auto updateAnimationAndComplete = [this](const Animation& animation) {
        UpdateAnimation(animation);
        if (animation.IsCompleted()) {
            ChangeState(StateType::Idle, nullptr);
        }
    };

    auto idleState = RegisterState(StateType::Idle, true);
    auto idleAnimation = std::make_shared<AnimationAbility>(getKey, updateAnimation);
    for (const auto& dir : animationDatas.at(StateType::Idle)) {
        std::stringstream ss;
        ss << dir.first;
        auto a = entityService_.MakeAnimation(dir.second);
        idleAnimation->RegisterAnimation(ss.str(), a);
    }
    idleState->RegisterAbility(idleAnimation);
    idleState->BindAction(Action::ChangeTo(StateType::Move), EventType::StartMove);
    idleState->BindAction(Action::ChangeTo(StateType::Attack), EventType::Attack);
    idleState->BindAction(Action::ChangeTo(StateType::AttackWeapon), EventType::AttackWeapon);
    idleState->BindAction(Action::Ignore(), EventType::Collision);

    auto moveState = RegisterState(StateType::Move);
    auto move = std::make_shared<MoveAbility>(
        constant::Entity::stdVelocity, [this](FaceDirection f) { OnBeginMove(f); },
        [this](const sf::Vector2f& d) { OnUpdateMove(d); });
    auto moveAnimation = std::make_shared<AnimationAbility>(getKey, updateAnimation);
    for (const auto& dir : animationDatas.at(StateType::Move)) {
        std::stringstream ss;
        ss << dir.first;
        auto a = entityService_.MakeAnimation(dir.second);
        moveAnimation->RegisterAnimation(ss.str(), a);
    }
    moveState->RegisterAbility(move);
    moveState->RegisterAbility(moveAnimation);
    moveState->BindAction(Action::ChangeTo(StateType::Idle), EventType::StopMove);
    moveState->BindAction(Action::Ignore(), EventType::StartMove);
    moveState->BindAction(Action::Ignore(), EventType::Attack);
    moveState->BindAction(Action::Ignore(), EventType::AttackWeapon);

    auto attackState = RegisterState(StateType::Attack);
    auto attackAnimation = std::make_shared<AnimationAbility>(getKey, updateAnimationAndComplete);
    for (const auto& dir : animationDatas.at(StateType::Attack)) {
        std::stringstream ss;
        ss << dir.first;
        auto a = entityService_.MakeAnimation(dir.second);
        attackAnimation->RegisterAnimation(ss.str(), a);
    }
    attackState->RegisterAbility(attackAnimation);
    attackState->BindAction(Action::ChangeTo(StateType::Move), EventType::StartMove);
    attackState->BindAction(Action::Ignore(), EventType::Attack);
    attackState->BindAction(Action::Ignore(), EventType::AttackWeapon);

    auto attackWeaponState = RegisterState(StateType::AttackWeapon);
    auto shoot = std::make_shared<ShootAbility>(
        nullptr, [this]() { OnExitShoot(); }, nullptr);
    auto attackWeaponAnimation = std::make_shared<AnimationAbility>(getKey, updateAnimationAndComplete);
    for (const auto& dir : animationDatas.at(StateType::AttackWeapon)) {
        std::stringstream ss;
        ss << dir.first;
        auto a = entityService_.MakeAnimation(dir.second);
        attackWeaponAnimation->RegisterAnimation(ss.str(), a);
    }
    attackWeaponState->RegisterAbility(attackWeaponAnimation);
    attackWeaponState->RegisterAbility(shoot);
    attackWeaponState->BindAction(Action::ChangeTo(StateType::Move), EventType::StartMove);
    attackWeaponState->BindAction(Action::Ignore(), EventType::Attack);
    attackWeaponState->BindAction(Action::Ignore(), EventType::AttackWeapon);
}

void PlayerEntity::Start(EntityService& entityService)
{
    entityService.AddCamera(propertyManager_.GetRef<sf::Vector2f>("Position"));
}

}  // namespace Entity

}  // namespace FA
