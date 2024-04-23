/*
 *	Copyright (C) 2021 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#include "PlayerEntity.h"

#include <SFML/Graphics/RenderWindow.hpp>

#include "Abilities/MoveAbility.h"
#include "CameraView.h"
#include "Constant/Entity.h"
#include "Entities/ArrowEntity.h"
#include "Events/AttackEvent.h"
#include "Events/AttackWeaponEvent.h"
#include "Events/DeadEvent.h"
#include "Events/StartMoveEvent.h"
#include "Events/StopMoveEvent.h"
#include "MapData.h"
#include "Message/BroadcastMessage/GameOverMessage.h"
#include "Message/BroadcastMessage/IsKeyPressedMessage.h"
#include "Message/BroadcastMessage/KeyPressedMessage.h"
#include "Message/BroadcastMessage/KeyReleasedMessage.h"
#include "Message/MessageType.h"
#include "PropertyConverter.h"
#include "PropertyData.h"
#include "Resource/SheetId.h"
#include "ShapeParts/AnimationPart.h"
#include "State.h"

namespace FA {

namespace Entity {

namespace {

const std::unordered_map<FaceDirection, sf::Vector2f> arrowOffset = {{FaceDirection::Down, {0.0, 15.0}},
                                                                     {FaceDirection::Left, {-15.0, 5.0}},
                                                                     {FaceDirection::Right, {15.0, 5.0}},
                                                                     {FaceDirection::Up, {0.0, -15.0}}};
using namespace Shared::SheetId;

const std::vector<Shared::ImageData> idleLeft{{HeroIdleSide, {0, 0}, true}};
const std::vector<Shared::ImageData> idleRight{{HeroIdleSide, {0, 0}}};
const std::vector<Shared::ImageData> idleFront{{HeroIdleFront, {0, 0}}};
const std::vector<Shared::ImageData> idleBack{{HeroIdleBack, {0, 0}}};
const std::vector<Shared::ImageData> moveLeft{{HeroWalkSide, {0, 0}, true}, {HeroWalkSide, {1, 0}, true},
                                              {HeroWalkSide, {2, 0}, true}, {HeroWalkSide, {3, 0}, true},
                                              {HeroWalkSide, {4, 0}, true}, {HeroWalkSide, {5, 0}, true}};
const std::vector<Shared::ImageData> moveRight{{HeroWalkSide, {0, 0}}, {HeroWalkSide, {1, 0}}, {HeroWalkSide, {2, 0}},
                                               {HeroWalkSide, {3, 0}}, {HeroWalkSide, {4, 0}}, {HeroWalkSide, {5, 0}}};
const std::vector<Shared::ImageData> moveDown{{HeroWalkFront, {0, 0}}, {HeroWalkFront, {1, 0}},
                                              {HeroWalkFront, {2, 0}}, {HeroWalkFront, {3, 0}},
                                              {HeroWalkFront, {4, 0}}, {HeroWalkFront, {5, 0}}};
const std::vector<Shared::ImageData> moveUp{{HeroWalkBack, {0, 0}}, {HeroWalkBack, {1, 0}}, {HeroWalkBack, {2, 0}},
                                            {HeroWalkBack, {3, 0}}, {HeroWalkBack, {4, 0}}, {HeroWalkBack, {5, 0}}};
const std::vector<Shared::ImageData> attackLeft{
    {HeroAttackSide, {0, 0}, true}, {HeroAttackSide, {1, 0}, true}, {HeroAttackSide, {2, 0}, true}};
const std::vector<Shared::ImageData> attackRight{
    {HeroAttackSide, {0, 0}}, {HeroAttackSide, {1, 0}}, {HeroAttackSide, {2, 0}}};
const std::vector<Shared::ImageData> attackDown{
    {HeroAttackFront, {0, 0}}, {HeroAttackFront, {1, 0}}, {HeroAttackFront, {2, 0}}};
const std::vector<Shared::ImageData> attackUp{
    {HeroAttackBack, {0, 0}}, {HeroAttackBack, {1, 0}}, {HeroAttackBack, {2, 0}}};
const std::vector<Shared::ImageData> attackWLeft{
    {HeroAttackWeaponSide, {0, 0}, true}, {HeroAttackWeaponSide, {1, 0}, true}, {HeroAttackWeaponSide, {2, 0}, true}};
const std::vector<Shared::ImageData> attackWRight{
    {HeroAttackWeaponSide, {0, 0}}, {HeroAttackWeaponSide, {1, 0}}, {HeroAttackWeaponSide, {2, 0}}};
const std::vector<Shared::ImageData> attackWDown{
    {HeroAttackWeaponFront, {0, 0}}, {HeroAttackWeaponFront, {1, 0}}, {HeroAttackWeaponFront, {2, 0}}};
const std::vector<Shared::ImageData> attackWUp{
    {HeroAttackWeaponBack, {0, 0}}, {HeroAttackWeaponBack, {1, 0}}, {HeroAttackWeaponBack, {2, 0}}};

const std::unordered_map<FaceDirection, std::vector<Shared::ImageData>> idleData{{FaceDirection::Left, idleLeft},
                                                                                 {FaceDirection::Right, idleRight},
                                                                                 {FaceDirection::Down, idleFront},
                                                                                 {FaceDirection::Up, idleBack}};
const std::unordered_map<FaceDirection, std::vector<Shared::ImageData>> moveData{{FaceDirection::Left, moveLeft},
                                                                                 {FaceDirection::Right, moveRight},
                                                                                 {FaceDirection::Down, moveDown},
                                                                                 {FaceDirection::Up, moveUp}};
const std::unordered_map<FaceDirection, std::vector<Shared::ImageData>> attackData{{FaceDirection::Left, attackLeft},
                                                                                   {FaceDirection::Right, attackRight},
                                                                                   {FaceDirection::Down, attackDown},
                                                                                   {FaceDirection::Up, attackUp}};
const std::unordered_map<FaceDirection, std::vector<Shared::ImageData>> attackWData{
    {FaceDirection::Left, attackWLeft},
    {FaceDirection::Right, attackWRight},
    {FaceDirection::Down, attackWDown},
    {FaceDirection::Up, attackWUp}};

FaceDirection MoveDirToFaceDir(MoveDirection moveDirection)
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

    return faceDir;
}

}  // namespace

const std::string PlayerEntity::str = "Player";

PlayerEntity::PlayerEntity(EntityId id, const PropertyData& data, const Shared::MapData& mapData,
                           const EntityService& service)
    : BasicEntity(id, data, mapData, service)
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
    FaceDirection faceDir = MoveDirToFaceDir(moveDirection);
    propertyStore_.Set("FaceDirection", faceDir);
}

void PlayerEntity::OnUpdateMove(const sf::Vector2f& delta)
{
    body_.position_ += delta;
}

void PlayerEntity::OnShoot()
{
    FaceDirection dir;
    propertyStore_.Get("FaceDirection", dir);
    auto position = body_.position_ + arrowOffset.at(dir);
    auto data = ArrowEntity::CreatePropertyData(position, dir);
    Shared::MapData mapData;
    mapData.size_.x = static_cast<unsigned int>(mapRect_.width);
    mapData.size_.y = static_cast<unsigned int>(mapRect_.height);
    service_.CreateEntity(data, mapData);
}

void PlayerEntity::OnBeginDie()
{
    SendMessage(std::make_shared<Shared::GameOverMessage>());
    auto& cameraView = service_.GetCameraView();
    cameraView.SetFixPoint(body_.position_);
}

void PlayerEntity::RegisterProperties()
{
    propertyStore_.Register("FaceDirection", FaceDirection::Down);
}

void PlayerEntity::ReadProperties(const std::unordered_map<std::string, std::string>& properties)
{
    for (const auto& p : properties) {
        if (p.first == "FaceDirection") {
            FaceDirection dir = ToValue<FaceDirection>(p.second);
            propertyStore_.Set(p.first, dir);
        }
    }
}

void PlayerEntity::RegisterStates(std::shared_ptr<State> idleState, std::shared_ptr<State> deadState,
                                  const PropertyData& data)
{
    DefineIdleState(idleState);
    auto moveState = RegisterState(StateType::Move);
    DefineMoveState(moveState);
    auto attackState = RegisterState(StateType::Attack);
    DefineAttackState(attackState);
    auto attackWeaponState = RegisterState(StateType::AttackWeapon);
    DefineAttackWeaponState(attackWeaponState);
}

void PlayerEntity::OnInit()
{
    auto& cameraView = service_.GetCameraView();
    cameraView.SetTrackPoint(body_.position_);
}

void PlayerEntity::DefineIdleState(std::shared_ptr<State> state)
{
    auto part = MakePart(idleData);
    state->RegisterShapePart(part);
    state->RegisterEventCB(EventType::StartMove,
                           [this](std::shared_ptr<BasicEvent> event) { ChangeStateTo(StateType::Move, event); });
    state->RegisterEventCB(EventType::StopMove, [this](std::shared_ptr<BasicEvent> event) {});
    state->RegisterEventCB(EventType::Attack,
                           [this](std::shared_ptr<BasicEvent> event) { ChangeStateTo(StateType::Attack, event); });
    state->RegisterEventCB(EventType::AttackWeapon, [this](std::shared_ptr<BasicEvent> event) {
        ChangeStateTo(StateType::AttackWeapon, event);
    });
    state->RegisterIgnoreEvents({EventType::Collision});
}

void PlayerEntity::DefineMoveState(std::shared_ptr<State> state)
{
    auto move = std::make_shared<MoveAbility>(
        Constant::stdVelocity, [this](MoveDirection d) { OnBeginMove(d); },
        [this](const sf::Vector2f& d) { OnUpdateMove(d); });
    auto part = MakePart(moveData);
    state->RegisterAbility(move);
    state->RegisterShapePart(part);
    state->RegisterEventCB(EventType::StopMove,
                           [this](std::shared_ptr<BasicEvent> event) { ChangeStateTo(StateType::Idle, event); });
    state->RegisterIgnoreEvents({EventType::StartMove, EventType::Attack, EventType::AttackWeapon});
}

void PlayerEntity::DefineAttackState(std::shared_ptr<State> state)
{
    auto updateCB = [this](const Shared::AnimationSprite& animation) {
        if (animation.IsCompleted()) {
            ChangeStateTo(StateType::Idle, nullptr);
        }
    };
    auto part = MakePart(attackData);
    part->RegisterUpdateCB(updateCB);
    state->RegisterShapePart(part);
    state->RegisterEventCB(EventType::StartMove,
                           [this](std::shared_ptr<BasicEvent> event) { ChangeStateTo(StateType::Move, event); });
    state->RegisterIgnoreEvents({EventType::Attack, EventType::AttackWeapon});
}

void PlayerEntity::DefineAttackWeaponState(std::shared_ptr<State> state)
{
    auto updateCB = [this](const Shared::AnimationSprite& animation) {
        if (animation.IsCompleted()) {
            OnShoot();
            ChangeStateTo(StateType::Idle, nullptr);
        }
    };
    auto part = MakePart(attackWData);
    part->RegisterUpdateCB(updateCB);
    state->RegisterShapePart(part);
    state->RegisterEventCB(EventType::StartMove,
                           [this](std::shared_ptr<BasicEvent> event) { ChangeStateTo(StateType::Move, event); });
    state->RegisterIgnoreEvents({EventType::Attack, EventType::AttackWeapon});
}

std::shared_ptr<AnimationPartWith<FaceDirection>> PlayerEntity::MakePart(
    const std::unordered_map<FaceDirection, std::vector<Shared::ImageData>>& data)
{
    FaceDirection* dir = nullptr;
    propertyStore_.GetPtr("FaceDirection", dir);
    auto part = AnimationPartWith<FaceDirection>::Create(*dir);
    for (const auto& entry : data) {
        part->RegisterAnimation(entry.first, service_.MakeAnimation(entry.second));
    }

    return part;
}

}  // namespace Entity

}  // namespace FA
