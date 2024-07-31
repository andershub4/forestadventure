/*
 *	Copyright (C) 2021 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#include "PlayerEntity.h"

#include <memory>

#include <SFML/Graphics/RenderWindow.hpp>

#include "Abilities/MoveAbility.h"
#include "Animation/ColliderAnimation.h"
#include "CameraView.h"
#include "Constant/Entity.h"
#include "Entities/ArrowEntity.h"
#include "Events/AttackEvent.h"
#include "Events/AttackWeaponEvent.h"
#include "Events/CollisionEvent.h"
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
#include "RectangleShape.h"
#include "Resource/SheetId.h"
#include "Resource/SheetItem.h"
#include "Selections/MultiSelection.h"
#include "ShapeParts/AnimationPart.h"
#include "Sprite.h"
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

const std::vector<Shared::ImageData> idleLeftImages{{idleSide1, true}};
const std::vector<Shared::ImageData> idleRightImages{idleSide1};
const std::vector<Shared::ImageData> idleFrontImages{idleFront1};
const std::vector<Shared::ImageData> idleBackImages{idleBack1};
const std::vector<Shared::ImageData> moveLeftImages{{moveSide1, true}, {moveSide2, true}, {moveSide3, true},
                                                    {moveSide4, true}, {moveSide5, true}, {moveSide6, true}};
const std::vector<Shared::ImageData> moveRightImages{moveSide1, moveSide2, moveSide3, moveSide4, moveSide5, moveSide6};
const std::vector<Shared::ImageData> moveDownImages{moveDown1, moveDown2, moveDown3, moveDown4, moveDown5, moveDown6};
const std::vector<Shared::ImageData> moveUpImages{moveUp1, moveUp2, moveUp3, moveUp4, moveUp5, moveUp6};

const std::vector<Shared::ImageData> attackLeftImages{{attackSide1, true}, {attackSide2, true}, {attackSide3, true}};
const std::vector<Shared::ImageData> attackRightImages{attackSide1, attackSide2, attackSide3};
const std::vector<Shared::ImageData> attackDownImages{attackDown1, attackDown2, attackDown3};
const std::vector<Shared::ImageData> attackUpImages{attackUp1, attackUp2, attackUp3};

const std::vector<Shared::ImageData> attackWLeftImages{
    {attackWSide1, true}, {attackWSide2, true}, {attackWSide3, true}};
const std::vector<Shared::ImageData> attackWRightImages{attackWSide1, attackWSide2, attackWSide3};
const std::vector<Shared::ImageData> attackWDownImages{attackWDown1, attackWDown2, attackWDown3};
const std::vector<Shared::ImageData> attackWUpImages{attackWUp1, attackWUp2, attackWUp3};

const std::unordered_map<FaceDirection, std::vector<Shared::ImageData>> idleFaceDirImages{
    {FaceDirection::Left, idleLeftImages},
    {FaceDirection::Right, idleRightImages},
    {FaceDirection::Down, idleFrontImages},
    {FaceDirection::Up, idleBackImages}};
const std::unordered_map<FaceDirection, std::vector<Shared::ImageData>> moveFaceDirImages{
    {FaceDirection::Left, moveLeftImages},
    {FaceDirection::Right, moveRightImages},
    {FaceDirection::Down, moveDownImages},
    {FaceDirection::Up, moveUpImages}};
const std::unordered_map<FaceDirection, std::vector<Shared::ImageData>> attackFaceDirImages{
    {FaceDirection::Left, attackLeftImages},
    {FaceDirection::Right, attackRightImages},
    {FaceDirection::Down, attackDownImages},
    {FaceDirection::Up, attackUpImages}};
const std::unordered_map<FaceDirection, std::vector<Shared::ImageData>> attackWFaceDirImages{
    {FaceDirection::Left, attackWLeftImages},
    {FaceDirection::Right, attackWRightImages},
    {FaceDirection::Down, attackWDownImages},
    {FaceDirection::Up, attackWUpImages}};

const sf::IntRect vrect{11, 9, 10, 20};
const sf::IntRect hrect{10, 10, 12, 19};

const std::vector<Shared::ColliderData> idleLeftColliders{{idleSide1, vrect}};
const std::vector<Shared::ColliderData> idleRightColliders{{idleSide1, vrect}};
const std::vector<Shared::ColliderData> idleFrontColliders{{idleFront1, hrect}};
const std::vector<Shared::ColliderData> idleBackColliders{{idleBack1, hrect}};
const std::vector<Shared::ColliderData> moveLeftColliders{{moveSide1, vrect}, {moveSide2, vrect}, {moveSide3, vrect},
                                                          {moveSide4, vrect}, {moveSide5, vrect}, {moveSide6, vrect}};
const std::vector<Shared::ColliderData> moveRightColliders{{moveSide1, vrect}, {moveSide2, vrect}, {moveSide3, vrect},
                                                           {moveSide4, vrect}, {moveSide5, vrect}, {moveSide6, vrect}};
const std::vector<Shared::ColliderData> moveDownColliders{{moveDown1, hrect}, {moveDown2, hrect}, {moveDown3, hrect},
                                                          {moveDown4, hrect}, {moveDown5, hrect}, {moveDown6, hrect}};
const std::vector<Shared::ColliderData> moveUpColliders{{moveUp1, hrect}, {moveUp2, hrect}, {moveUp3, hrect},
                                                        {moveUp4, hrect}, {moveUp5, hrect}, {moveUp6, hrect}};
const std::vector<Shared::ColliderData> attackLeftColliders{
    {attackSide1, vrect}, {attackSide2, vrect}, {attackSide3, vrect}};
const std::vector<Shared::ColliderData> attackRightColliders{
    {attackSide1, vrect}, {attackSide2, vrect}, {attackSide3, vrect}};
const std::vector<Shared::ColliderData> attackDownColliders{
    {attackDown1, hrect}, {attackDown2, hrect}, {attackDown3, hrect}};
const std::vector<Shared::ColliderData> attackUpColliders{{attackUp1, hrect}, {attackUp2, hrect}, {attackUp3, hrect}};
const std::vector<Shared::ColliderData> attackWLeftColliders{
    {attackWSide1, vrect}, {attackWSide2, vrect}, {attackWSide3, vrect}};
const std::vector<Shared::ColliderData> attackWRightColliders{
    {attackWSide1, vrect}, {attackWSide2, vrect}, {attackWSide3, vrect}};
const std::vector<Shared::ColliderData> attackWDownColliders{
    {attackWDown1, hrect}, {attackWDown2, hrect}, {attackWDown3, hrect}};
const std::vector<Shared::ColliderData> attackWUpColliders{{attackWUp1, hrect}, {attackWUp2, hrect}, {attackWUp3, hrect}};

const std::unordered_map<FaceDirection, std::vector<Shared::ColliderData>> idleFaceDirColliders{
    {FaceDirection::Left, idleLeftColliders},
    {FaceDirection::Right, idleRightColliders},
    {FaceDirection::Down, idleFrontColliders},
    {FaceDirection::Up, idleBackColliders}};
const std::unordered_map<FaceDirection, std::vector<Shared::ColliderData>> moveFaceDirColliders{
    {FaceDirection::Left, moveLeftColliders},
    {FaceDirection::Right, moveRightColliders},
    {FaceDirection::Down, moveDownColliders},
    {FaceDirection::Up, moveUpColliders}};
const std::unordered_map<FaceDirection, std::vector<Shared::ColliderData>> attackFaceDirColliders{
    {FaceDirection::Left, attackLeftColliders},
    {FaceDirection::Right, attackRightColliders},
    {FaceDirection::Down, attackDownColliders},
    {FaceDirection::Up, attackUpColliders}};
const std::unordered_map<FaceDirection, std::vector<Shared::ColliderData>> attackWFaceDirColliders{
    {FaceDirection::Left, attackWLeftColliders},
    {FaceDirection::Right, attackWRightColliders},
    {FaceDirection::Down, attackWDownColliders},
    {FaceDirection::Up, attackWUpColliders}};

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
    auto updateCB = [](const Shared::ImageAnimationIf& animation) {};
    auto shapePart = MakeShapePart(idleFaceDirImages, updateCB);
    state->RegisterShapePart(shapePart);
    auto colliderPart = MakeColliderPart(idleFaceDirColliders);
    state->RegisterColliderPart(colliderPart);
    state->RegisterEventCB(EventType::StartMove,
                           [this](std::shared_ptr<BasicEvent> event) { ChangeStateTo(StateType::Move, event); });
    state->RegisterEventCB(EventType::StopMove, [this](std::shared_ptr<BasicEvent> event) {});
    state->RegisterEventCB(EventType::Attack,
                           [this](std::shared_ptr<BasicEvent> event) { ChangeStateTo(StateType::Attack, event); });
    state->RegisterEventCB(EventType::AttackWeapon, [this](std::shared_ptr<BasicEvent> event) {
        ChangeStateTo(StateType::AttackWeapon, event);
    });
}

void PlayerEntity::DefineMoveState(std::shared_ptr<State> state)
{
    auto updateCB = [](const Shared::ImageAnimationIf& animation) {};
    auto shapePart = MakeShapePart(moveFaceDirImages, updateCB);
    state->RegisterShapePart(shapePart);
    auto colliderPart = MakeColliderPart(moveFaceDirColliders);
    state->RegisterColliderPart(colliderPart);
    auto move = std::make_shared<MoveAbility>(
        Constant::stdVelocity, [this](MoveDirection d) { OnBeginMove(d); },
        [this](const sf::Vector2f& d) { OnUpdateMove(d); });
    state->RegisterAbility(move);
    state->RegisterEventCB(EventType::StopMove,
                           [this](std::shared_ptr<BasicEvent> event) { ChangeStateTo(StateType::Idle, event); });
    state->RegisterIgnoreEvents({EventType::StartMove, EventType::Attack, EventType::AttackWeapon});
    state->RegisterEventCB(EventType::Collision, [this](std::shared_ptr<BasicEvent> event) {
        auto collisionEvent = std::dynamic_pointer_cast<CollisionEvent>(event);
        if (service_.GetType(collisionEvent->id_) == EntityType::Coin) {
            coins_++;
        }
    });
}

void PlayerEntity::DefineAttackState(std::shared_ptr<State> state)
{
    auto updateCB = [this](const Shared::ImageAnimationIf& animation) {
        if (animation.IsCompleted()) {
            ChangeStateTo(StateType::Idle, nullptr);
        }
    };
    auto shapePart = MakeShapePart(attackFaceDirImages, updateCB);
    state->RegisterShapePart(shapePart);
    auto colliderPart = MakeColliderPart(attackFaceDirColliders);
    state->RegisterColliderPart(colliderPart);
    state->RegisterEventCB(EventType::StartMove,
                           [this](std::shared_ptr<BasicEvent> event) { ChangeStateTo(StateType::Move, event); });
    state->RegisterIgnoreEvents({EventType::Attack, EventType::AttackWeapon});
}

void PlayerEntity::DefineAttackWeaponState(std::shared_ptr<State> state)
{
    auto updateCB = [this](const Shared::ImageAnimationIf& animation) {
        if (animation.IsCompleted()) {
            OnShoot();
            ChangeStateTo(StateType::Idle, nullptr);
        }
    };
    auto shapePart = MakeShapePart(attackWFaceDirImages, updateCB);
    state->RegisterShapePart(shapePart);
    auto colliderPart = MakeColliderPart(attackWFaceDirColliders);
    state->RegisterColliderPart(colliderPart);
    state->RegisterEventCB(EventType::StartMove,
                           [this](std::shared_ptr<BasicEvent> event) { ChangeStateTo(StateType::Move, event); });
    state->RegisterIgnoreEvents({EventType::Attack, EventType::AttackWeapon});
}

std::shared_ptr<AnimationPart<Shared::ImageAnimation>> PlayerEntity::MakeShapePart(
    const std::unordered_map<FaceDirection, std::vector<Shared::ImageData>>& faceDirImages,
    std::function<void(const Shared::ImageAnimationIf&)> updateCB)
{
    FaceDirection* dir = nullptr;
    propertyStore_.GetPtr("FaceDirection", dir);
    auto selection = std::make_shared<MultiSelection<Shared::ImageAnimation, FaceDirection>>(dir);
    for (const auto& entry : faceDirImages) {
        auto animation = std::make_shared<Shared::ImageAnimation>(std::make_shared<Graphic::Sprite>(),
                                                                  service_.CreateSequence(entry.second));
        animation->Center();
        animation->RegisterUpdateCB(updateCB);
        selection->RegisterSelection(entry.first, animation);
    }

    auto part = std::make_shared<AnimationPart<Shared::ImageAnimation>>(selection);
    return part;
}

std::shared_ptr<AnimationPart<Shared::ColliderAnimation>> PlayerEntity::MakeColliderPart(
    const std::unordered_map<FaceDirection, std::vector<Shared::ColliderData>>& faceDirColliders)
{
    FaceDirection* dir = nullptr;
    propertyStore_.GetPtr<FaceDirection>("FaceDirection", dir);
    auto selection = std::make_shared<MultiSelection<Shared::ColliderAnimation, FaceDirection>>(dir);
    for (const auto& entry : faceDirColliders) {
        auto animation = std::make_shared<Shared::ColliderAnimation>(std::make_shared<Graphic::RectangleShape>(),
                                                                     service_.CreateSequence(entry.second));
        animation->Center();
        selection->RegisterSelection(entry.first, animation);
    }

    auto part = std::make_shared<AnimationPart<Shared::ColliderAnimation>>(selection);
    return part;
}

}  // namespace Entity

}  // namespace FA
