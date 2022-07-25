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
#include "Entity/Events/AttackWeaponEvent.h"
#include "Entity/Events/DeadEvent.h"
#include "Entity/Events/StartMoveEvent.h"
#include "Entity/Events/StopMoveEvent.h"
#include "Entity/PropertyData.h"
#include "Entity/State.h"
#include "Enum/MessageType.h"
#include "Message/BroadcastMessage/GameOverMessage.h"
#include "Message/BroadcastMessage/IsKeyPressedMessage.h"
#include "Message/BroadcastMessage/KeyPressedMessage.h"
#include "Message/BroadcastMessage/KeyReleasedMessage.h"
#include "Resource/AnimationData.h"
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
                           EntityManager& entityManager, MessageBus& messageBus, const sf::Vector2u& mapSize)
    : BasicEntity(id, cameraManager, sheetManager, entityManager, messageBus, mapSize)
{}

PlayerEntity::~PlayerEntity() = default;

std::vector<MessageType> PlayerEntity::Messages() const
{
    return {MessageType::IsKeyPressed, MessageType::KeyReleased, MessageType::KeyPressed};
}

void PlayerEntity::OnMessage(std::shared_ptr<Message> msg)
{
    if (msg->GetMessageType() == MessageType::IsKeyPressed) {
        auto m = std::dynamic_pointer_cast<IsKeyPressedMessage>(msg);
        auto key = m->GetKey();
        if (key == sf::Keyboard::Key::Right) {
            HandleEvent(std::make_shared<StartMoveEvent>(MoveDirection::Right, FaceDirection::Right));
        }
        else if (key == sf::Keyboard::Key::Left) {
            HandleEvent(std::make_shared<StartMoveEvent>(MoveDirection::Left, FaceDirection::Left));
        }
        else if (key == sf::Keyboard::Key::Down) {
            HandleEvent(std::make_shared<StartMoveEvent>(MoveDirection::Down, FaceDirection::Down));
        }
        else if (key == sf::Keyboard::Key::Up) {
            HandleEvent(std::make_shared<StartMoveEvent>(MoveDirection::Up, FaceDirection::Up));
        }
        else if (key == sf::Keyboard::Key::RControl) {
            HandleEvent(std::make_shared<AttackEvent>());
        }
        else if (key == sf::Keyboard::Key::Space) {
            HandleEvent(std::make_shared<AttackWeaponEvent>(EntityType::Arrow));
        }
    }
    else if (msg->GetMessageType() == MessageType::KeyReleased) {
        auto m = std::dynamic_pointer_cast<KeyReleasedMessage>(msg);
        auto key = m->GetKey();
        if (key == sf::Keyboard::Key::Right || key == sf::Keyboard::Key::Left || key == sf::Keyboard::Key::Down ||
            key == sf::Keyboard::Key::Up) {
            HandleEvent(std::make_shared<StopMoveEvent>());
        }
    }
    else if (msg->GetMessageType() == MessageType::KeyPressed) {
        auto m = std::dynamic_pointer_cast<KeyPressedMessage>(msg);
        auto key = m->GetKey();
        if (key == sf::Keyboard::Key::Num1) {
            HandleEvent(std::make_shared<DeadEvent>());
        }
    }
}

void PlayerEntity::OnBeginMove(FaceDirection faceDirection)
{
    propertyManager_.Set("FaceDirection", faceDirection);
}

void PlayerEntity::OnUpdateMove(const sf::Vector2f& delta)
{
    position_ += delta;
}

void PlayerEntity::OnExitShoot()
{
    bool shoot = propertyManager_.Get<bool>("Shoot");
    if (shoot) {
        propertyManager_.Set<bool>("Shoot", false);
        auto dir = propertyManager_.Get<FaceDirection>("FaceDirection");
        auto position = position_ + arrowOffset.at(dir);
        entityService_.SpawnEntity(EntityType::Arrow, dir, position);
    }
}

void PlayerEntity::OnUpdateAnimation(const Animation& animation)
{
    auto& sprite = shape_.GetSprite("Main");
    animation.ApplyTo(sprite);
    sprite.setOrigin(sprite.getLocalBounds().width / 2, sprite.getLocalBounds().height / 2);
}

void PlayerEntity::OnDying()
{
    SendMessage(std::make_shared<GameOverMessage>());
}

void PlayerEntity::RegisterProperties()
{
    propertyManager_.Register<FaceDirection>("FaceDirection", FaceDirection::Down);
    propertyManager_.Register<bool>("Shoot", false);
}

void PlayerEntity::RegisterShape()
{
    shape_ = CreateShape();
    shape_.AddSprite("Main");
}

void PlayerEntity::RegisterStates(std::shared_ptr<State> idleState, const PropertyData& data)
{
    auto getKey = [this]() {
        std::stringstream ss;
        auto dir = propertyManager_.Get<FaceDirection>("FaceDirection");
        ss << dir;
        return ss.str();
    };
    auto updateAnimation = [this](const Animation& animation) { OnUpdateAnimation(animation); };
    auto updateAnimationAndComplete = [this](const Animation& animation) {
        OnUpdateAnimation(animation);
        if (animation.IsCompleted()) {
            ChangeStateTo(StateType::Idle, nullptr);
        }
    };
    auto updateAnimationAndShoot = [this](const Animation& animation) {
        OnUpdateAnimation(animation);
        if (animation.IsCompleted()) {
            propertyManager_.Set<bool>("Shoot", true);
            ChangeStateTo(StateType::Idle, nullptr);
        }
    };

    auto idleAnimation = std::make_shared<AnimationAbility>(getKey, updateAnimation);
    for (const auto& dir : animationDatas.at(StateType::Idle)) {
        std::stringstream ss;
        ss << dir.first;
        auto a = entityService_.MakeAnimation(dir.second);
        idleAnimation->RegisterAnimation(ss.str(), a);
    }
    idleState->RegisterAbility(idleAnimation);
    idleState->RegisterEventCB(EventType::StartMove,
                               [this](std::shared_ptr<BasicEvent> event) { ChangeStateTo(StateType::Move, event); });
    idleState->RegisterEventCB(EventType::StopMove, [this](std::shared_ptr<BasicEvent> event) {});
    idleState->RegisterEventCB(EventType::Attack,
                               [this](std::shared_ptr<BasicEvent> event) { ChangeStateTo(StateType::Attack, event); });
    idleState->RegisterEventCB(EventType::AttackWeapon, [this](std::shared_ptr<BasicEvent> event) {
        ChangeStateTo(StateType::AttackWeapon, event);
    });
    idleState->RegisterIgnoreEvents({EventType::Collision});

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
    moveState->RegisterAbility(moveAnimation);  // register animation after move
    moveState->RegisterEventCB(EventType::StopMove,
                               [this](std::shared_ptr<BasicEvent> event) { ChangeStateTo(StateType::Idle, event); });
    moveState->RegisterIgnoreEvents({EventType::StartMove, EventType::Attack, EventType::AttackWeapon});

    auto attackState = RegisterState(StateType::Attack);
    auto attackAnimation = std::make_shared<AnimationAbility>(getKey, updateAnimationAndComplete);
    for (const auto& dir : animationDatas.at(StateType::Attack)) {
        std::stringstream ss;
        ss << dir.first;
        auto a = entityService_.MakeAnimation(dir.second);
        attackAnimation->RegisterAnimation(ss.str(), a);
    }
    attackState->RegisterAbility(attackAnimation);
    attackState->RegisterEventCB(EventType::StartMove,
                                 [this](std::shared_ptr<BasicEvent> event) { ChangeStateTo(StateType::Move, event); });
    attackState->RegisterIgnoreEvents({EventType::Attack, EventType::AttackWeapon});

    auto attackWeaponState = RegisterState(StateType::AttackWeapon);
    auto shoot = std::make_shared<ShootAbility>(
        nullptr, [this]() { OnExitShoot(); }, nullptr);
    auto attackWeaponAnimation = std::make_shared<AnimationAbility>(getKey, updateAnimationAndShoot);
    for (const auto& dir : animationDatas.at(StateType::AttackWeapon)) {
        std::stringstream ss;
        ss << dir.first;
        auto a = entityService_.MakeAnimation(dir.second);
        attackWeaponAnimation->RegisterAnimation(ss.str(), a);
    }
    attackWeaponState->RegisterAbility(shoot);
    attackWeaponState->RegisterAbility(attackWeaponAnimation);  // register animation after shoot
    attackWeaponState->RegisterEventCB(
        EventType::StartMove, [this](std::shared_ptr<BasicEvent> event) { ChangeStateTo(StateType::Move, event); });
    attackWeaponState->RegisterIgnoreEvents({EventType::Attack, EventType::AttackWeapon});
}

void PlayerEntity::Start()
{
    entityService_.AddCamera(position_);
}

}  // namespace Entity

}  // namespace FA
