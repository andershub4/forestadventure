/*
 *	Copyright (C) 2021 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#include "PlayerEntity.h"

#include <sstream>

#include <SFML/Graphics/RenderWindow.hpp>

#include "Abilities/MoveAbility.h"
#include "AnimationTable.h"
#include "Camera.h"
#include "Constant/Entity.h"
#include "Entities/ArrowEntity.h"
#include "Events/AttackEvent.h"
#include "Events/AttackWeaponEvent.h"
#include "Events/DeadEvent.h"
#include "Events/StartMoveEvent.h"
#include "Events/StopMoveEvent.h"
#include "Message/BroadcastMessage/GameOverMessage.h"
#include "Message/BroadcastMessage/IsKeyPressedMessage.h"
#include "Message/BroadcastMessage/KeyPressedMessage.h"
#include "Message/BroadcastMessage/KeyReleasedMessage.h"
#include "Message/MessageType.h"
#include "PropertyConverter.h"
#include "PropertyData.h"
#include "Resource/AnimationData.h"
#include "Resource/SheetId.h"
#include "Sprites/AnimationSprite.h"
#include "State.h"

namespace FA {

namespace Entity {

namespace {

const std::unordered_map<FaceDirection, sf::Vector2f> arrowOffset = {{FaceDirection::Down, {0.0, 15.0}},
                                                                     {FaceDirection::Left, {-15.0, 5.0}},
                                                                     {FaceDirection::Right, {15.0, 5.0}},
                                                                     {FaceDirection::Up, {0.0, -15.0}}};

const Shared::AnimationData idleLeft{Shared::SheetId::HeroIdleSide, {{0, 0}, 1, 0}, true};
const Shared::AnimationData idleRight{Shared::SheetId::HeroIdleSide, {{0, 0}, 1, 0}, false};
const Shared::AnimationData idleDown{Shared::SheetId::HeroIdleFront, {{0, 0}, 1, 0}, false};
const Shared::AnimationData idleUp{Shared::SheetId::HeroIdleBack, {{0, 0}, 1, 0}, false};

const Shared::AnimationData walkLeft{Shared::SheetId::HeroWalkSide, {{0, 0}, 6, 0}, true};
const Shared::AnimationData walkRight{Shared::SheetId::HeroWalkSide, {{0, 0}, 6, 0}, false};
const Shared::AnimationData walkDown{Shared::SheetId::HeroWalkFront, {{0, 0}, 6, 0}, false};
const Shared::AnimationData walkUp{Shared::SheetId::HeroWalkBack, {{0, 0}, 6, 0}, false};

const Shared::AnimationData attackLeft{Shared::SheetId::HeroAttackSide, {{0, 0}, 3, 0}, true};
const Shared::AnimationData attackRight{Shared::SheetId::HeroAttackSide, {{0, 0}, 3, 0}, false};
const Shared::AnimationData attackDown{Shared::SheetId::HeroAttackFront, {{0, 0}, 3, 0}, false};
const Shared::AnimationData attackUp{Shared::SheetId::HeroAttackBack, {{0, 0}, 3, 0}, false};

const Shared::AnimationData attackWeaponLeft{Shared::SheetId::HeroAttackWeaponSide, {{0, 0}, 3, 0}, true};
const Shared::AnimationData attackWeaponRight{Shared::SheetId::HeroAttackWeaponSide, {{0, 0}, 3, 0}, false};
const Shared::AnimationData attackWeaponDown{Shared::SheetId::HeroAttackWeaponFront, {{0, 0}, 3, 0}, false};
const Shared::AnimationData attackWeaponUp{Shared::SheetId::HeroAttackWeaponBack, {{0, 0}, 3, 0}, false};

}  // namespace

const std::string PlayerEntity::str = "Player";

PlayerEntity::PlayerEntity(EntityId id, const PropertyData& data, const EntityService& service)
    : BasicEntity(id, data, service)
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
            HandleEvent(std::make_shared<AttackWeaponEvent>());
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

void PlayerEntity::OnShoot()
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
    auto& camera = entityService_.GetCamera();
    camera.Set(body_.position_);
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
    AnimationTable idleTable([this]() { return AnimationKey(); });
    idleTable.RegisterAnimation("Left", entityService_.MakeAnimation(idleLeft));
    idleTable.RegisterAnimation("Right", entityService_.MakeAnimation(idleRight));
    idleTable.RegisterAnimation("Down", entityService_.MakeAnimation(idleDown));
    idleTable.RegisterAnimation("Up", entityService_.MakeAnimation(idleUp));
    auto idleSprite = std::make_shared<AnimationSprite>(idleTable);

    idleState->RegisterSprite(idleSprite);
    idleState->RegisterEventCB(EventType::StartMove,
                               [this](std::shared_ptr<BasicEvent> event) { ChangeStateTo(StateType::Move, event); });
    idleState->RegisterEventCB(EventType::StopMove, [this](std::shared_ptr<BasicEvent> event) {});
    idleState->RegisterEventCB(EventType::Attack,
                               [this](std::shared_ptr<BasicEvent> event) { ChangeStateTo(StateType::Attack, event); });
    idleState->RegisterEventCB(EventType::AttackWeapon, [this](std::shared_ptr<BasicEvent> event) {
        ChangeStateTo(StateType::AttackWeapon, event);
    });
    idleState->RegisterIgnoreEvents({EventType::Collision});

    deadState->RegisterSprite(idleSprite);

    auto moveState = RegisterState(StateType::Move);
    auto move = std::make_shared<MoveAbility>(
        Constant::stdVelocity, [this](MoveDirection d) { OnBeginMove(d); },
        [this](const sf::Vector2f& d) { OnUpdateMove(d); });
    AnimationTable moveTable([this]() { return AnimationKey(); });
    moveTable.RegisterAnimation("Left", entityService_.MakeAnimation(walkLeft));
    moveTable.RegisterAnimation("Right", entityService_.MakeAnimation(walkRight));
    moveTable.RegisterAnimation("Down", entityService_.MakeAnimation(walkDown));
    moveTable.RegisterAnimation("Up", entityService_.MakeAnimation(walkUp));
    auto moveSprite = std::make_shared<AnimationSprite>(moveTable);
    moveState->RegisterAbility(move);
    moveState->RegisterSprite(moveSprite);
    moveState->RegisterEventCB(EventType::StopMove,
                               [this](std::shared_ptr<BasicEvent> event) { ChangeStateTo(StateType::Idle, event); });
    moveState->RegisterIgnoreEvents({EventType::StartMove, EventType::Attack, EventType::AttackWeapon});

    auto attackState = RegisterState(StateType::Attack);
    auto updateAnimationAndComplete = [this](const Shared::Animation& animation) {
        if (animation.IsCompleted()) {
            ChangeStateTo(StateType::Idle, nullptr);
        }
    };
    AnimationTable attackTable([this]() { return AnimationKey(); });
    attackTable.RegisterAnimation("Left", entityService_.MakeAnimation(attackLeft));
    attackTable.RegisterAnimation("Right", entityService_.MakeAnimation(attackRight));
    attackTable.RegisterAnimation("Down", entityService_.MakeAnimation(attackDown));
    attackTable.RegisterAnimation("Up", entityService_.MakeAnimation(attackUp));
    auto attackSprite = std::make_shared<AnimationSprite>(attackTable, updateAnimationAndComplete);
    attackState->RegisterSprite(attackSprite);
    attackState->RegisterEventCB(EventType::StartMove,
                                 [this](std::shared_ptr<BasicEvent> event) { ChangeStateTo(StateType::Move, event); });
    attackState->RegisterIgnoreEvents({EventType::Attack, EventType::AttackWeapon});

    auto attackWeaponState = RegisterState(StateType::AttackWeapon);
    attackWeaponState->RegisterExitCB([this]() { OnShoot(); });
    auto updateAnimationAndShoot = [this](const Shared::Animation& animation) {
        if (animation.IsCompleted()) {
            propertyStore_.Set<bool>("Shoot", true);
            ChangeStateTo(StateType::Idle, nullptr);
        }
    };
    AnimationTable attackWeaponTable([this]() { return AnimationKey(); });
    attackWeaponTable.RegisterAnimation("Left", entityService_.MakeAnimation(attackWeaponLeft));
    attackWeaponTable.RegisterAnimation("Right", entityService_.MakeAnimation(attackWeaponRight));
    attackWeaponTable.RegisterAnimation("Down", entityService_.MakeAnimation(attackWeaponDown));
    attackWeaponTable.RegisterAnimation("Up", entityService_.MakeAnimation(attackWeaponUp));
    auto attackWeaponSprite = std::make_shared<AnimationSprite>(attackWeaponTable, updateAnimationAndShoot);
    attackWeaponState->RegisterSprite(attackWeaponSprite);
    attackWeaponState->RegisterEventCB(
        EventType::StartMove, [this](std::shared_ptr<BasicEvent> event) { ChangeStateTo(StateType::Move, event); });
    attackWeaponState->RegisterIgnoreEvents({EventType::Attack, EventType::AttackWeapon});
}

void PlayerEntity::OnInit()
{
    auto& camera = entityService_.GetCamera();
    camera.Track(body_.position_);
}

}  // namespace Entity

}  // namespace FA
