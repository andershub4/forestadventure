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
#include "Resource/SheetItem.h"
#include "ShapeParts/AnimationPart.h"
#include "ShapeParts/ColliderPart.h"
#include "State.h"

namespace FA {

namespace Entity {

namespace {

const std::unordered_map<FaceDirection, sf::Vector2f> arrowOffset = {{FaceDirection::Down, {0.0, 15.0}},
                                                                     {FaceDirection::Left, {-15.0, 5.0}},
                                                                     {FaceDirection::Right, {15.0, 5.0}},
                                                                     {FaceDirection::Up, {0.0, -15.0}}};
using namespace Shared::SheetId;

const Shared::SheetItem idleSide1{HeroIdleSide, {0, 0}};
const Shared::SheetItem idleFront1{HeroIdleFront, {0, 0}};
const Shared::SheetItem idleBack1{HeroIdleBack, {0, 0}};

const Shared::SheetItem moveSide1{HeroWalkSide, {0, 0}};
const Shared::SheetItem moveSide2{HeroWalkSide, {1, 0}};
const Shared::SheetItem moveSide3{HeroWalkSide, {2, 0}};
const Shared::SheetItem moveSide4{HeroWalkSide, {3, 0}};
const Shared::SheetItem moveSide5{HeroWalkSide, {4, 0}};
const Shared::SheetItem moveSide6{HeroWalkSide, {5, 0}};

const Shared::SheetItem moveDown1{HeroWalkFront, {0, 0}};
const Shared::SheetItem moveDown2{HeroWalkFront, {1, 0}};
const Shared::SheetItem moveDown3{HeroWalkFront, {2, 0}};
const Shared::SheetItem moveDown4{HeroWalkFront, {3, 0}};
const Shared::SheetItem moveDown5{HeroWalkFront, {4, 0}};
const Shared::SheetItem moveDown6{HeroWalkFront, {5, 0}};

const Shared::SheetItem moveUp1{HeroWalkBack, {0, 0}};
const Shared::SheetItem moveUp2{HeroWalkBack, {1, 0}};
const Shared::SheetItem moveUp3{HeroWalkBack, {2, 0}};
const Shared::SheetItem moveUp4{HeroWalkBack, {3, 0}};
const Shared::SheetItem moveUp5{HeroWalkBack, {4, 0}};
const Shared::SheetItem moveUp6{HeroWalkBack, {5, 0}};

const Shared::SheetItem attackSide1{HeroAttackSide, {0, 0}};
const Shared::SheetItem attackSide2{HeroAttackSide, {1, 0}};
const Shared::SheetItem attackSide3{HeroAttackSide, {2, 0}};

const Shared::SheetItem attackDown1{HeroAttackFront, {0, 0}};
const Shared::SheetItem attackDown2{HeroAttackFront, {1, 0}};
const Shared::SheetItem attackDown3{HeroAttackFront, {2, 0}};

const Shared::SheetItem attackUp1{HeroAttackBack, {0, 0}};
const Shared::SheetItem attackUp2{HeroAttackBack, {1, 0}};
const Shared::SheetItem attackUp3{HeroAttackBack, {2, 0}};

const Shared::SheetItem attackWSide1{HeroAttackWeaponSide, {0, 0}};
const Shared::SheetItem attackWSide2{HeroAttackWeaponSide, {1, 0}};
const Shared::SheetItem attackWSide3{HeroAttackWeaponSide, {2, 0}};

const Shared::SheetItem attackWDown1{HeroAttackWeaponFront, {0, 0}};
const Shared::SheetItem attackWDown2{HeroAttackWeaponFront, {1, 0}};
const Shared::SheetItem attackWDown3{HeroAttackWeaponFront, {2, 0}};

const Shared::SheetItem attackWUp1{HeroAttackWeaponBack, {0, 0}};
const Shared::SheetItem attackWUp2{HeroAttackWeaponBack, {1, 0}};
const Shared::SheetItem attackWUp3{HeroAttackWeaponBack, {2, 0}};

const std::vector<Shared::ImageData> idleLeft{{idleSide1, true}};
const std::vector<Shared::ImageData> idleRight{idleSide1};
const std::vector<Shared::ImageData> idleFront{idleFront1};
const std::vector<Shared::ImageData> idleBack{idleBack1};
const std::vector<Shared::ImageData> moveLeft{{moveSide1, true}, {moveSide2, true}, {moveSide3, true},
                                              {moveSide4, true}, {moveSide5, true}, {moveSide6, true}};
const std::vector<Shared::ImageData> moveRight{moveSide1, moveSide2, moveSide3, moveSide4, moveSide5, moveSide6};
const std::vector<Shared::ImageData> moveDown{moveDown1, moveDown2, moveDown3, moveDown4, moveDown5, moveDown6};
const std::vector<Shared::ImageData> moveUp{moveUp1, moveUp2, moveUp3, moveUp4, moveUp5, moveUp6};

const std::vector<Shared::ImageData> attackLeft{{attackSide1, true}, {attackSide2, true}, {attackSide3, true}};
const std::vector<Shared::ImageData> attackRight{attackSide1, attackSide2, attackSide3};
const std::vector<Shared::ImageData> attackDown{attackDown1, attackDown2, attackDown3};
const std::vector<Shared::ImageData> attackUp{attackUp1, attackUp2, attackUp3};

const std::vector<Shared::ImageData> attackWLeft{{attackWSide1, true}, {attackWSide2, true}, {attackWSide3, true}};
const std::vector<Shared::ImageData> attackWRight{attackWSide1, attackWSide2, attackWSide3};
const std::vector<Shared::ImageData> attackWDown{attackWDown1, attackWDown2, attackWDown3};
const std::vector<Shared::ImageData> attackWUp{attackWUp1, attackWUp2, attackWUp3};

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

const std::vector<Shared::ColliderData> colliderIdleLeft{idleSide1};
const std::vector<Shared::ColliderData> colliderIdleRight{idleSide1};
const std::vector<Shared::ColliderData> colliderIdleFront{idleFront1};
const std::vector<Shared::ColliderData> colliderIdleBack{idleBack1};
const std::vector<Shared::ColliderData> colliderMoveLeft{moveSide1, moveSide2, moveSide3,
                                                         moveSide4, moveSide5, moveSide6};
const std::vector<Shared::ColliderData> colliderMoveRight{moveSide1, moveSide2, moveSide3,
                                                          moveSide4, moveSide5, moveSide6};
const std::vector<Shared::ColliderData> colliderMoveDown{moveDown1, moveDown2, moveDown3,
                                                         moveDown4, moveDown5, moveDown6};
const std::vector<Shared::ColliderData> colliderMoveUp{moveUp1, moveUp2, moveUp3, moveUp4, moveUp5, moveUp6};
const std::vector<Shared::ColliderData> colliderAttackLeft{attackSide1, attackSide2, attackSide3};
const std::vector<Shared::ColliderData> colliderAttackRight{attackSide1, attackSide2, attackSide3};
const std::vector<Shared::ColliderData> colliderAttackDown{attackDown1, attackDown2, attackDown3};
const std::vector<Shared::ColliderData> colliderAttackUp{attackUp1, attackUp2, attackUp3};
const std::vector<Shared::ColliderData> colliderAttackWLeft{attackWSide1, attackWSide2, attackWSide3};
const std::vector<Shared::ColliderData> colliderAttackWRight{attackWSide1, attackWSide2, attackWSide3};
const std::vector<Shared::ColliderData> colliderAttackWDown{attackWDown1, attackWDown2, attackWDown3};
const std::vector<Shared::ColliderData> colliderAttackWUp{attackWUp1, attackWUp2, attackWUp3};

const std::unordered_map<FaceDirection, std::vector<Shared::ColliderData>> colliderIdleData{
    {FaceDirection::Left, colliderIdleLeft},
    {FaceDirection::Right, colliderIdleRight},
    {FaceDirection::Down, colliderIdleFront},
    {FaceDirection::Up, colliderIdleBack}};
const std::unordered_map<FaceDirection, std::vector<Shared::ColliderData>> colliderMoveData{
    {FaceDirection::Left, colliderMoveLeft},
    {FaceDirection::Right, colliderMoveRight},
    {FaceDirection::Down, colliderMoveDown},
    {FaceDirection::Up, colliderMoveUp}};
const std::unordered_map<FaceDirection, std::vector<Shared::ColliderData>> colliderAttackData{
    {FaceDirection::Left, colliderAttackLeft},
    {FaceDirection::Right, colliderAttackRight},
    {FaceDirection::Down, colliderAttackDown},
    {FaceDirection::Up, colliderAttackUp}};
const std::unordered_map<FaceDirection, std::vector<Shared::ColliderData>> colliderAttackWData{
    {FaceDirection::Left, colliderAttackWLeft},
    {FaceDirection::Right, colliderAttackWRight},
    {FaceDirection::Down, colliderAttackWDown},
    {FaceDirection::Up, colliderAttackWUp}};

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
    auto shapePart = MakeShapePart(idleData);
    state->RegisterShapePart(shapePart);
    auto colliderPart = MakeColliderPart(colliderIdleData);
    state->RegisterColliderPart(colliderPart);
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
    auto shapePart = MakeShapePart(moveData);
    state->RegisterShapePart(shapePart);
    auto colliderPart = MakeColliderPart(colliderMoveData);
    state->RegisterColliderPart(colliderPart);
    auto move = std::make_shared<MoveAbility>(
        Constant::stdVelocity, [this](MoveDirection d) { OnBeginMove(d); },
        [this](const sf::Vector2f& d) { OnUpdateMove(d); });
    state->RegisterAbility(move);

    state->RegisterEventCB(EventType::StopMove,
                           [this](std::shared_ptr<BasicEvent> event) { ChangeStateTo(StateType::Idle, event); });
    state->RegisterIgnoreEvents({EventType::StartMove, EventType::Attack, EventType::AttackWeapon});
}

void PlayerEntity::DefineAttackState(std::shared_ptr<State> state)
{
    auto updateCB = [this](const Shared::ImageAnimation& animation) {
        if (animation.IsCompleted()) {
            ChangeStateTo(StateType::Idle, nullptr);
        }
    };
    auto shapePart = MakeShapePart(attackData);
    state->RegisterShapePart(shapePart);
    auto colliderPart = MakeColliderPart(colliderAttackData);
    state->RegisterColliderPart(colliderPart);
    shapePart->RegisterUpdateCB(updateCB);
    state->RegisterEventCB(EventType::StartMove,
                           [this](std::shared_ptr<BasicEvent> event) { ChangeStateTo(StateType::Move, event); });
    state->RegisterIgnoreEvents({EventType::Attack, EventType::AttackWeapon});
}

void PlayerEntity::DefineAttackWeaponState(std::shared_ptr<State> state)
{
    auto updateCB = [this](const Shared::ImageAnimation& animation) {
        if (animation.IsCompleted()) {
            OnShoot();
            ChangeStateTo(StateType::Idle, nullptr);
        }
    };
    auto shapePart = MakeShapePart(attackWData);
    state->RegisterShapePart(shapePart);
    auto colliderPart = MakeColliderPart(colliderAttackWData);
    state->RegisterColliderPart(colliderPart);
    shapePart->RegisterUpdateCB(updateCB);
    state->RegisterEventCB(EventType::StartMove,
                           [this](std::shared_ptr<BasicEvent> event) { ChangeStateTo(StateType::Move, event); });
    state->RegisterIgnoreEvents({EventType::Attack, EventType::AttackWeapon});
}

std::shared_ptr<AnimationPartWith<FaceDirection>> PlayerEntity::MakeShapePart(
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

std::shared_ptr<ColliderPartWith<FaceDirection>> PlayerEntity::MakeColliderPart(
    const std::unordered_map<FaceDirection, std::vector<Shared::ColliderData>>& data)
{
    FaceDirection* dir = nullptr;
    propertyStore_.GetPtr<FaceDirection>("FaceDirection", dir);
    auto part = ColliderPartWith<FaceDirection>::Create(*dir);
    for (const auto& entry : data) {
        part->RegisterCollider(entry.first, service_.MakeAnimation(entry.second));
    }

    return part;
}

}  // namespace Entity

}  // namespace FA
