/*
 *	Copyright (C) 2021 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#include "PlayerEntity.h"

#include <sstream>

#include <SFML/Graphics/RenderWindow.hpp>

#include "Constant/Entity.h"
#include "Entity/Abilities/MoveAbility.h"
#include "Entity/Abilities/ShootAbility.h"
#include "Entity/Entities/ArrowEntity.h"
#include "Entity/Events/AttackEvent.h"
#include "Entity/Events/AttackWeaponEvent.h"
#include "Entity/Events/DeadEvent.h"
#include "Entity/Events/StartMoveEvent.h"
#include "Entity/Events/StopMoveEvent.h"
#include "Entity/PropertyConverter.h"
#include "Entity/PropertyData.h"
#include "Entity/Sprites/AnimationSprite.h"
#include "Entity/State.h"
#include "Level/Camera.h"
#include "Message/BroadcastMessage/GameOverMessage.h"
#include "Message/BroadcastMessage/IsKeyPressedMessage.h"
#include "Message/BroadcastMessage/KeyPressedMessage.h"
#include "Message/BroadcastMessage/KeyReleasedMessage.h"
#include "Message/MessageType.h"
#include "Resource/AnimationData.h"
#include "Resource/SheetId.h"

namespace FA {

namespace Entity {

namespace {

const std::unordered_map<FaceDirection, sf::Vector2f> arrowOffset = {{FaceDirection::Down, {0.0, 15.0}},
                                                                     {FaceDirection::Left, {-15.0, 5.0}},
                                                                     {FaceDirection::Right, {15.0, 5.0}},
                                                                     {FaceDirection::Up, {0.0, -15.0}}};

const std::unordered_map<StateType, std::unordered_map<FaceDirection, Shared::AnimationData>> animationDatas = {
    {StateType::Move,
     {{FaceDirection::Left, {Shared::SheetId::HeroWalkSide, {{0, 0}, 6, 0}, true}},
      {FaceDirection::Right, {Shared::SheetId::HeroWalkSide, {{0, 0}, 6, 0}, false}},
      {FaceDirection::Down, {Shared::SheetId::HeroWalkFront, {{0, 0}, 6, 0}, false}},
      {FaceDirection::Up, {Shared::SheetId::HeroWalkBack, {{0, 0}, 6, 0}, false}}}},
    {StateType::Idle,
     {{FaceDirection::Left, {Shared::SheetId::HeroIdleSide, {{0, 0}, 1, 0}, true}},
      {FaceDirection::Right, {Shared::SheetId::HeroIdleSide, {{0, 0}, 1, 0}, false}},
      {FaceDirection::Down, {Shared::SheetId::HeroIdleFront, {{0, 0}, 1, 0}, false}},
      {FaceDirection::Up, {Shared::SheetId::HeroIdleBack, {{0, 0}, 1, 0}, false}}}},
    {StateType::Attack,
     {{FaceDirection::Left, {Shared::SheetId::HeroAttackSide, {{0, 0}, 3, 0}, true}},
      {FaceDirection::Right, {Shared::SheetId::HeroAttackSide, {{0, 0}, 3, 0}, false}},
      {FaceDirection::Down, {Shared::SheetId::HeroAttackFront, {{0, 0}, 3, 0}, false}},
      {FaceDirection::Up, {Shared::SheetId::HeroAttackBack, {{0, 0}, 3, 0}, false}}}},
    {StateType::AttackWeapon,
     {{FaceDirection::Left, {Shared::SheetId::HeroAttackWeaponSide, {{0, 0}, 3, 0}, true}},
      {FaceDirection::Right, {Shared::SheetId::HeroAttackWeaponSide, {{0, 0}, 3, 0}, false}},
      {FaceDirection::Down, {Shared::SheetId::HeroAttackWeaponFront, {{0, 0}, 3, 0}, false}},
      {FaceDirection::Up, {Shared::SheetId::HeroAttackWeaponBack, {{0, 0}, 3, 0}, false}}}}};

}  // namespace

const std::string PlayerEntity::str = "Player";

PlayerEntity::PlayerEntity(EntityId id, const EntityService& service)
    : BasicEntity(id, service)
{}

PlayerEntity::~PlayerEntity() = default;

std::vector<Shared::MessageType> PlayerEntity::Messages() const
{
    return {Shared::MessageType::IsKeyPressed, Shared::MessageType::KeyReleased, Shared::MessageType::KeyPressed};
}

void PlayerEntity::OnMessage(std::shared_ptr<Shared::Message> msg)
{
    if (msg->GetMessageType() == Shared::MessageType::IsKeyPressed) {
        auto m = std::dynamic_pointer_cast<Shared::IsKeyPressedMessage>(msg);
        auto key = m->GetKey();
        if (key == sf::Keyboard::Key::Right) {
            HandleEvent(std::make_shared<StartMoveEvent>(MoveDirection::Right));
        }
        else if (key == sf::Keyboard::Key::Left) {
            HandleEvent(std::make_shared<StartMoveEvent>(MoveDirection::Left));
        }
        else if (key == sf::Keyboard::Key::Down) {
            HandleEvent(std::make_shared<StartMoveEvent>(MoveDirection::Down));
        }
        else if (key == sf::Keyboard::Key::Up) {
            HandleEvent(std::make_shared<StartMoveEvent>(MoveDirection::Up));
        }
        else if (key == sf::Keyboard::Key::RControl) {
            HandleEvent(std::make_shared<AttackEvent>());
        }
        else if (key == sf::Keyboard::Key::Space) {
            HandleEvent(std::make_shared<AttackWeaponEvent>(EntityType::Arrow));
        }
    }
    else if (msg->GetMessageType() == Shared::MessageType::KeyReleased) {
        auto m = std::dynamic_pointer_cast<Shared::KeyReleasedMessage>(msg);
        auto key = m->GetKey();
        if (key == sf::Keyboard::Key::Right || key == sf::Keyboard::Key::Left || key == sf::Keyboard::Key::Down ||
            key == sf::Keyboard::Key::Up) {
            HandleEvent(std::make_shared<StopMoveEvent>());
        }
    }
    else if (msg->GetMessageType() == Shared::MessageType::KeyPressed) {
        auto m = std::dynamic_pointer_cast<Shared::KeyPressedMessage>(msg);
        auto key = m->GetKey();
        if (key == sf::Keyboard::Key::Num1) {
            HandleEvent(std::make_shared<DeadEvent>());
        }
    }
}

void PlayerEntity::OnBeginMove(MoveDirection moveDirection)
{
    FaceDirection faceDir = FaceDirection::Undefined;
    if (moveDirection == MoveDirection::Down)
        faceDir = FaceDirection::Down;
    else if (moveDirection == MoveDirection::Up)
        faceDir = FaceDirection::Up;
    else if (moveDirection == MoveDirection::Left)
        faceDir = FaceDirection::Left;
    else if (moveDirection == MoveDirection::Right)
        faceDir = FaceDirection::Right;
    propertyStore_.Set("FaceDirection", faceDir);
}

void PlayerEntity::OnUpdateMove(const sf::Vector2f& delta)
{
    body_.position_ += delta;
}

void PlayerEntity::OnExitShoot()
{
    bool shoot = propertyStore_.Get<bool>("Shoot");
    if (shoot) {
        propertyStore_.Set<bool>("Shoot", false);
        auto dir = propertyStore_.Get<FaceDirection>("FaceDirection");
        auto position = body_.position_ + arrowOffset.at(dir);
        MoveDirection moveDir = MoveDirection::None;
        if (dir == FaceDirection::Down)
            moveDir = MoveDirection::Down;
        else if (dir == FaceDirection::Up)
            moveDir = MoveDirection::Up;
        else if (dir == FaceDirection::Left)
            moveDir = MoveDirection::Left;
        else if (dir == FaceDirection::Right)
            moveDir = MoveDirection::Right;
        auto data = ArrowEntity::CreatePropertyData(position, moveDir);
        entityService_.CreateEntity(data);
    }
}

void PlayerEntity::OnBeginDie()
{
    SendMessage(std::make_shared<Shared::GameOverMessage>());
}

std::string PlayerEntity::AnimationKey() const
{
    std::stringstream ss;
    auto dir = propertyStore_.Get<FaceDirection>("FaceDirection");
    ss << dir;
    return ss.str();
}

std::unordered_map<std::string, Shared::Animation> PlayerEntity::GetAnimations(
    const std::unordered_map<FaceDirection, Shared::AnimationData>& data) const
{
    std::unordered_map<std::string, Shared::Animation> animations;
    for (const auto& dir : data) {
        std::stringstream ss;
        ss << dir.first;
        auto a = entityService_.MakeAnimation(dir.second);
        animations[ss.str()] = a;
    }
    return animations;
}

void PlayerEntity::RegisterProperties()
{
    propertyStore_.Register<FaceDirection>("FaceDirection", FaceDirection::Down);
    propertyStore_.Register<bool>("Shoot", false);
}

void PlayerEntity::ReadProperties(const std::unordered_map<std::string, std::string>& properties)
{
    for (const auto& p : properties) {
        if (p.first == "FaceDirection") {
            FaceDirection dir = ToValue<FaceDirection>(p.second);
            propertyStore_.Set<FaceDirection>(p.first, dir);
        }
    }
}

void PlayerEntity::RegisterStates(std::shared_ptr<State> idleState, std::shared_ptr<State> deadState,
                                  const PropertyData& data)
{
    auto updateAnimationAndComplete = [this](const Shared::Animation& animation) {
        if (animation.IsCompleted()) {
            ChangeStateTo(StateType::Idle, nullptr);
        }
    };
    auto updateAnimationAndShoot = [this](const Shared::Animation& animation) {
        if (animation.IsCompleted()) {
            propertyStore_.Set<bool>("Shoot", true);
            ChangeStateTo(StateType::Idle, nullptr);
        }
    };

    auto idleAnimations = GetAnimations(animationDatas.at(StateType::Idle));
    auto idleAnimation =
        std::make_shared<AnimationSprite>(std::bind(&PlayerEntity::AnimationKey, this), idleAnimations);
    idleState->RegisterSprite(idleAnimation);
    idleState->RegisterEventCB(EventType::StartMove,
                               [this](std::shared_ptr<BasicEvent> event) { ChangeStateTo(StateType::Move, event); });
    idleState->RegisterEventCB(EventType::StopMove, [this](std::shared_ptr<BasicEvent> event) {});
    idleState->RegisterEventCB(EventType::Attack,
                               [this](std::shared_ptr<BasicEvent> event) { ChangeStateTo(StateType::Attack, event); });
    idleState->RegisterEventCB(EventType::AttackWeapon, [this](std::shared_ptr<BasicEvent> event) {
        ChangeStateTo(StateType::AttackWeapon, event);
    });
    idleState->RegisterIgnoreEvents({EventType::Collision});

    deadState->RegisterSprite(idleAnimation);

    auto moveState = RegisterState(StateType::Move);
    auto move = std::make_shared<MoveAbility>(
        Constant::stdVelocity, [this](MoveDirection d) { OnBeginMove(d); },
        [this](const sf::Vector2f& d) { OnUpdateMove(d); });
    auto moveAnimations = GetAnimations(animationDatas.at(StateType::Move));
    auto moveAnimation =
        std::make_shared<AnimationSprite>(std::bind(&PlayerEntity::AnimationKey, this), moveAnimations);
    moveState->RegisterAbility(move);
    moveState->RegisterSprite(moveAnimation);
    moveState->RegisterEventCB(EventType::StopMove,
                               [this](std::shared_ptr<BasicEvent> event) { ChangeStateTo(StateType::Idle, event); });
    moveState->RegisterIgnoreEvents({EventType::StartMove, EventType::Attack, EventType::AttackWeapon});

    auto attackState = RegisterState(StateType::Attack);
    auto attackAnimations = GetAnimations(animationDatas.at(StateType::Attack));
    auto attackAnimation = std::make_shared<AnimationSprite>(std::bind(&PlayerEntity::AnimationKey, this),
                                                             attackAnimations, updateAnimationAndComplete);
    attackState->RegisterSprite(attackAnimation);
    attackState->RegisterEventCB(EventType::StartMove,
                                 [this](std::shared_ptr<BasicEvent> event) { ChangeStateTo(StateType::Move, event); });
    attackState->RegisterIgnoreEvents({EventType::Attack, EventType::AttackWeapon});

    auto attackWeaponState = RegisterState(StateType::AttackWeapon);
    auto shoot = std::make_shared<ShootAbility>(
        nullptr, [this]() { OnExitShoot(); }, nullptr);
    auto attackWeaponAnimations = GetAnimations(animationDatas.at(StateType::AttackWeapon));
    auto attackWeaponAnimation = std::make_shared<AnimationSprite>(std::bind(&PlayerEntity::AnimationKey, this),
                                                                   attackWeaponAnimations, updateAnimationAndShoot);
    attackWeaponState->RegisterAbility(shoot);
    attackWeaponState->RegisterSprite(attackWeaponAnimation);
    attackWeaponState->RegisterEventCB(
        EventType::StartMove, [this](std::shared_ptr<BasicEvent> event) { ChangeStateTo(StateType::Move, event); });
    attackWeaponState->RegisterIgnoreEvents({EventType::Attack, EventType::AttackWeapon});
}

void PlayerEntity::Start()
{
    auto& camera = entityService_.GetCamera();
    camera.Track(body_.position_);
}

}  // namespace Entity

}  // namespace FA
