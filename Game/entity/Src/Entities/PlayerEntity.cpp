/*
 *	Copyright (C) 2021 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#include "PlayerEntity.h"

#include <initializer_list>
#include <memory>

#include <SFML/Graphics/RenderWindow.hpp>

#include "Abilities/DoorMoveAbility.h"
#include "Abilities/MoveAbility.h"
#include "Animation/AnimationIf.h"
#include "Animator/Animator.h"
#include "CameraView.h"
#include "Constant/Entity.h"
#include "Entities/ArrowEntity.h"
#include "Events/AttackEvent.h"
#include "Events/AttackWeaponEvent.h"
#include "Events/CollisionEvent.h"
#include "Events/DeadEvent.h"
#include "Events/StartDoorMoveEvent.h"
#include "Events/StartMoveEvent.h"
#include "Events/StopMoveEvent.h"
#include "Logging.h"
#include "Message/BroadcastMessage/GameOverMessage.h"
#include "Message/BroadcastMessage/IsKeyPressedMessage.h"
#include "Message/BroadcastMessage/KeyPressedMessage.h"
#include "Message/BroadcastMessage/KeyReleasedMessage.h"
#include "Message/MessageType.h"
#include "PropertyConverter.h"
#include "RectangleShape.h"
#include "Resource/ColliderData.h"
#include "Resource/EntityData.h"
#include "Resource/ImageData.h"
#include "Resource/SheetId.h"
#include "Resource/SheetItem.h"
#include "Sprite.h"
#include "State.h"

namespace FA {

namespace Entity {

using ImageSelection = std::pair<const FaceDirection, std::shared_ptr<Shared::AnimationIf<Shared::ImageFrame>>>;
using ColliderSelection = std::pair<const FaceDirection, std::shared_ptr<Shared::AnimationIf<Shared::ColliderFrame>>>;

namespace {

const std::unordered_map<FaceDirection, sf::Vector2f> arrowOffset = {{FaceDirection::Front, {0.0, 15.0}},
                                                                     {FaceDirection::Left, {-15.0, 5.0}},
                                                                     {FaceDirection::Right, {15.0, 5.0}},
                                                                     {FaceDirection::Back, {0.0, -15.0}}};
using namespace Shared::SheetId;

const Shared::SheetItem idleSide1{HeroIdleSide, {0, 0}};
const Shared::SheetItem idleFront1{HeroIdleFront, {0, 0}};
const Shared::SheetItem idleBack1{HeroIdleBack, {0, 0}};

const Shared::SheetItem walkSide1{HeroWalkSide, {0, 0}};
const Shared::SheetItem walkSide2{HeroWalkSide, {1, 0}};
const Shared::SheetItem walkSide3{HeroWalkSide, {2, 0}};
const Shared::SheetItem walkSide4{HeroWalkSide, {3, 0}};
const Shared::SheetItem walkSide5{HeroWalkSide, {4, 0}};
const Shared::SheetItem walkSide6{HeroWalkSide, {5, 0}};

const Shared::SheetItem walkFront1{HeroWalkFront, {0, 0}};
const Shared::SheetItem walkFront2{HeroWalkFront, {1, 0}};
const Shared::SheetItem walkFront3{HeroWalkFront, {2, 0}};
const Shared::SheetItem walkFront4{HeroWalkFront, {3, 0}};
const Shared::SheetItem walkFront5{HeroWalkFront, {4, 0}};
const Shared::SheetItem walkFront6{HeroWalkFront, {5, 0}};

const Shared::SheetItem walkBack1{HeroWalkBack, {0, 0}};
const Shared::SheetItem walkBack2{HeroWalkBack, {1, 0}};
const Shared::SheetItem walkBack3{HeroWalkBack, {2, 0}};
const Shared::SheetItem walkBack4{HeroWalkBack, {3, 0}};
const Shared::SheetItem walkBack5{HeroWalkBack, {4, 0}};
const Shared::SheetItem walkBack6{HeroWalkBack, {5, 0}};

const Shared::SheetItem attackSide1{HeroAttackSide, {0, 0}};
const Shared::SheetItem attackSide2{HeroAttackSide, {1, 0}};
const Shared::SheetItem attackSide3{HeroAttackSide, {2, 0}};

const Shared::SheetItem attackFront1{HeroAttackFront, {0, 0}};
const Shared::SheetItem attackFront2{HeroAttackFront, {1, 0}};
const Shared::SheetItem attackFront3{HeroAttackFront, {2, 0}};

const Shared::SheetItem attackBack1{HeroAttackBack, {0, 0}};
const Shared::SheetItem attackBack2{HeroAttackBack, {1, 0}};
const Shared::SheetItem attackBack3{HeroAttackBack, {2, 0}};

const Shared::SheetItem attackWSide1{HeroAttackWeaponSide, {0, 0}};
const Shared::SheetItem attackWSide2{HeroAttackWeaponSide, {1, 0}};
const Shared::SheetItem attackWSide3{HeroAttackWeaponSide, {2, 0}};

const Shared::SheetItem attackWFront1{HeroAttackWeaponFront, {0, 0}};
const Shared::SheetItem attackWFront2{HeroAttackWeaponFront, {1, 0}};
const Shared::SheetItem attackWFront3{HeroAttackWeaponFront, {2, 0}};

const Shared::SheetItem attackWBack1{HeroAttackWeaponBack, {0, 0}};
const Shared::SheetItem attackWBack2{HeroAttackWeaponBack, {1, 0}};
const Shared::SheetItem attackWBack3{HeroAttackWeaponBack, {2, 0}};

const std::vector<Shared::ImageData> idleLeftImages{{idleSide1, true}};
const std::vector<Shared::ImageData> idleRightImages{idleSide1};
const std::vector<Shared::ImageData> idleFrontImages{idleFront1};
const std::vector<Shared::ImageData> idleBackImages{idleBack1};
const std::vector<Shared::ImageData> walkLeftImages{{walkSide1, true}, {walkSide2, true}, {walkSide3, true},
                                                    {walkSide4, true}, {walkSide5, true}, {walkSide6, true}};
const std::vector<Shared::ImageData> walkRightImages{walkSide1, walkSide2, walkSide3, walkSide4, walkSide5, walkSide6};
const std::vector<Shared::ImageData> walkFrontImages{walkFront1, walkFront2, walkFront3,
                                                     walkFront4, walkFront5, walkFront6};
const std::vector<Shared::ImageData> walkBackImages{walkBack1, walkBack2, walkBack3, walkBack4, walkBack5, walkBack6};

const std::vector<Shared::ImageData> attackLeftImages{{attackSide1, true}, {attackSide2, true}, {attackSide3, true}};
const std::vector<Shared::ImageData> attackRightImages{attackSide1, attackSide2, attackSide3};
const std::vector<Shared::ImageData> attackFrontImages{attackFront1, attackFront2, attackFront3};
const std::vector<Shared::ImageData> attackBackImages{attackBack1, attackBack2, attackBack3};

const std::vector<Shared::ImageData> attackWLeftImages{
    {attackWSide1, true}, {attackWSide2, true}, {attackWSide3, true}};
const std::vector<Shared::ImageData> attackWRightImages{attackWSide1, attackWSide2, attackWSide3};
const std::vector<Shared::ImageData> attackWFrontImages{attackWFront1, attackWFront2, attackWFront3};
const std::vector<Shared::ImageData> attackWBackImages{attackWBack1, attackWBack2, attackWBack3};

// Need to align, otherwise collision will be detected differently when colliding to a wall
const sf::IntRect vrect{11, 10, 10, 18};
const sf::IntRect hrect{11, 10, 10, 18};

const std::vector<Shared::ColliderData> idleLeftColliders{{idleSide1, vrect}};
const std::vector<Shared::ColliderData> idleRightColliders{{idleSide1, vrect}};
const std::vector<Shared::ColliderData> idleFrontColliders{{idleFront1, hrect}};
const std::vector<Shared::ColliderData> idleBackColliders{{idleBack1, hrect}};
const std::vector<Shared::ColliderData> walkLeftColliders{{walkSide1, vrect}, {walkSide2, vrect}, {walkSide3, vrect},
                                                          {walkSide4, vrect}, {walkSide5, vrect}, {walkSide6, vrect}};
const std::vector<Shared::ColliderData> walkRightColliders{{walkSide1, vrect}, {walkSide2, vrect}, {walkSide3, vrect},
                                                           {walkSide4, vrect}, {walkSide5, vrect}, {walkSide6, vrect}};
const std::vector<Shared::ColliderData> walkFrontColliders{{walkFront1, hrect}, {walkFront2, hrect},
                                                           {walkFront3, hrect}, {walkFront4, hrect},
                                                           {walkFront5, hrect}, {walkFront6, hrect}};
const std::vector<Shared::ColliderData> walkBackColliders{{walkBack1, hrect}, {walkBack2, hrect}, {walkBack3, hrect},
                                                          {walkBack4, hrect}, {walkBack5, hrect}, {walkBack6, hrect}};
const std::vector<Shared::ColliderData> attackLeftColliders{
    {attackSide1, vrect}, {attackSide2, vrect}, {attackSide3, vrect}};
const std::vector<Shared::ColliderData> attackRightColliders{
    {attackSide1, vrect}, {attackSide2, vrect}, {attackSide3, vrect}};
const std::vector<Shared::ColliderData> attackFrontColliders{
    {attackFront1, hrect}, {attackFront2, hrect}, {attackFront3, hrect}};
const std::vector<Shared::ColliderData> attackBackColliders{
    {attackBack1, hrect}, {attackBack2, hrect}, {attackBack3, hrect}};
const std::vector<Shared::ColliderData> attackWLeftColliders{
    {attackWSide1, vrect}, {attackWSide2, vrect}, {attackWSide3, vrect}};
const std::vector<Shared::ColliderData> attackWRightColliders{
    {attackWSide1, vrect}, {attackWSide2, vrect}, {attackWSide3, vrect}};
const std::vector<Shared::ColliderData> attackWFrontColliders{
    {attackWFront1, hrect}, {attackWFront2, hrect}, {attackWFront3, hrect}};
const std::vector<Shared::ColliderData> attackWBackColliders{
    {attackWBack1, hrect}, {attackWBack2, hrect}, {attackWBack3, hrect}};

// Need to align, otherwise collision will be detected differently when colliding to a wall
const sf::IntRect vrect2{11, 26, 10, 2};
const sf::IntRect hrect2{11, 26, 10, 2};
const std::vector<Shared::ColliderData> walkLeftColliders2{{walkSide1, vrect2}, {walkSide2, vrect2},
                                                           {walkSide3, vrect2}, {walkSide4, vrect2},
                                                           {walkSide5, vrect2}, {walkSide6, vrect2}};
const std::vector<Shared::ColliderData> walkRightColliders2{{walkSide1, vrect2}, {walkSide2, vrect2},
                                                            {walkSide3, vrect2}, {walkSide4, vrect2},
                                                            {walkSide5, vrect2}, {walkSide6, vrect2}};
const std::vector<Shared::ColliderData> walkFrontColliders2{{walkFront1, hrect2}, {walkFront2, hrect2},
                                                            {walkFront3, hrect2}, {walkFront4, hrect2},
                                                            {walkFront5, hrect2}, {walkFront6, hrect2}};
const std::vector<Shared::ColliderData> walkBackColliders2{{walkBack1, hrect2}, {walkBack2, hrect2},
                                                           {walkBack3, hrect2}, {walkBack4, hrect2},
                                                           {walkBack5, hrect2}, {walkBack6, hrect2}};

FaceDirection MoveDirToFaceDir(MoveDirection moveDirection)
{
    FaceDirection faceDir = FaceDirection::Undefined;

    if (moveDirection == MoveDirection::Down)
        faceDir = FaceDirection::Front;
    else if (moveDirection == MoveDirection::Up)
        faceDir = FaceDirection::Back;
    else if (moveDirection == MoveDirection::Left)
        faceDir = FaceDirection::Left;
    else if (moveDirection == MoveDirection::Right)
        faceDir = FaceDirection::Right;

    return faceDir;
}

}  // namespace

const std::string PlayerEntity::str = "Player";

PlayerEntity::PlayerEntity(EntityId id, const Shared::EntityData& data, std::unique_ptr<EntityService> service)
    : BasicEntity(id, data, std::move(service))
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
    body_.prevPosition_ = body_.position_;
    body_.position_ += delta;
}

void PlayerEntity::OnShoot()
{
    FaceDirection dir;
    propertyStore_.Get("FaceDirection", dir);
    auto position = body_.position_ + arrowOffset.at(dir);
    auto data = ArrowEntity::CreateEntityData(position, dir);
    service_->AddToCreationPool(data);
}

void PlayerEntity::OnBeginDie()
{
    SendMessage(std::make_shared<Shared::GameOverMessage>());
    auto& cameraView = service_->GetCameraView();
    cameraView.SetFixPoint(body_.position_);
}

void PlayerEntity::RegisterProperties()
{
    propertyStore_.Register("FaceDirection", FaceDirection::Front);
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
                                  const Shared::EntityData& data)
{
    DefineIdleState(idleState);
    auto moveState = RegisterState(StateType::Move);
    DefineMoveState(moveState);
    auto doorMoveState = RegisterState(StateType::DoorMove);
    DefineDoorMoveState(doorMoveState);
    auto attackState = RegisterState(StateType::Attack);
    DefineAttackState(attackState);
    auto attackWeaponState = RegisterState(StateType::AttackWeapon);
    DefineAttackWeaponState(attackWeaponState);
}

void PlayerEntity::OnInit()
{
    auto& cameraView = service_->GetCameraView();
    cameraView.SetTrackPoint(body_.position_);
}

void PlayerEntity::DefineIdleState(std::shared_ptr<State> state)
{
    auto sprite = state->RegisterSprite();
    FaceDirection* dir = nullptr;
    propertyStore_.GetPtr("FaceDirection", dir);
    std::initializer_list<ImageSelection> imageSelections{
        {FaceDirection::Left, service_->CreateImageAnimation(idleLeftImages)},
        {FaceDirection::Right, service_->CreateImageAnimation(idleRightImages)},
        {FaceDirection::Front, service_->CreateImageAnimation(idleFrontImages)},
        {FaceDirection::Back, service_->CreateImageAnimation(idleBackImages)}};
    auto imageAnimator = std::make_shared<Animator<Shared::ImageFrame, FaceDirection>>(*sprite, imageSelections, *dir);
    state->RegisterImageAnimator(imageAnimator);
    auto rect = state->RegisterCollider(Shape::ColliderType::Entity);
    std::initializer_list<ColliderSelection> colliderSelections{
        {FaceDirection::Left, service_->CreateColliderAnimation(idleLeftColliders)},
        {FaceDirection::Right, service_->CreateColliderAnimation(idleRightColliders)},
        {FaceDirection::Front, service_->CreateColliderAnimation(idleFrontColliders)},
        {FaceDirection::Back, service_->CreateColliderAnimation(idleBackColliders)}};
    auto colliderAnimator =
        std::make_shared<Animator<Shared::ColliderFrame, FaceDirection>>(*rect, colliderSelections, *dir);
    state->RegisterColliderAnimator(colliderAnimator);
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
    auto sprite = state->RegisterSprite();
    FaceDirection* dir = nullptr;
    propertyStore_.GetPtr("FaceDirection", dir);
    std::initializer_list<ImageSelection> imageSelections{
        {FaceDirection::Left, service_->CreateImageAnimation(walkLeftImages)},
        {FaceDirection::Right, service_->CreateImageAnimation(walkRightImages)},
        {FaceDirection::Front, service_->CreateImageAnimation(walkFrontImages)},
        {FaceDirection::Back, service_->CreateImageAnimation(walkBackImages)}};
    auto imageAnimator = std::make_shared<Animator<Shared::ImageFrame, FaceDirection>>(*sprite, imageSelections, *dir);
    state->RegisterImageAnimator(imageAnimator);
    auto rect = state->RegisterCollider(Shape::ColliderType::Entity);
    std::initializer_list<ColliderSelection> colliderSelections{
        {FaceDirection::Left, service_->CreateColliderAnimation(walkLeftColliders)},
        {FaceDirection::Right, service_->CreateColliderAnimation(walkRightColliders)},
        {FaceDirection::Front, service_->CreateColliderAnimation(walkFrontColliders)},
        {FaceDirection::Back, service_->CreateColliderAnimation(walkBackColliders)}};
    auto colliderAnimator =
        std::make_shared<Animator<Shared::ColliderFrame, FaceDirection>>(*rect, colliderSelections, *dir);
    state->RegisterColliderAnimator(colliderAnimator);
    auto rect2 = state->RegisterCollider(Shape::ColliderType::Wall);
    std::initializer_list<ColliderSelection> colliderSelections2{
        {FaceDirection::Left, service_->CreateColliderAnimation(walkLeftColliders2)},
        {FaceDirection::Right, service_->CreateColliderAnimation(walkRightColliders2)},
        {FaceDirection::Front, service_->CreateColliderAnimation(walkFrontColliders2)},
        {FaceDirection::Back, service_->CreateColliderAnimation(walkBackColliders2)}};
    auto colliderAnimator2 =
        std::make_shared<Animator<Shared::ColliderFrame, FaceDirection>>(*rect2, colliderSelections2, *dir);
    state->RegisterColliderAnimator(colliderAnimator2);
    auto move = std::make_shared<MoveAbility>(
        Constant::stdVelocity, [this](MoveDirection d) { OnBeginMove(d); },
        [this](const sf::Vector2f& d) { OnUpdateMove(d); });
    state->RegisterAbility(move);
    state->RegisterEventCB(EventType::StopMove,
                           [this](std::shared_ptr<BasicEvent> event) { ChangeStateTo(StateType::Idle, event); });
    state->RegisterIgnoreEvents({EventType::StartMove, EventType::Attack, EventType::AttackWeapon});
    state->RegisterEventCB(EventType::Collision, [this](std::shared_ptr<BasicEvent> event) {
        auto collisionEvent = std::dynamic_pointer_cast<CollisionEvent>(event);
        auto& collisionEntity = service_->GetEntity(collisionEvent->id_);
        if (collisionEntity.IsSolid()) {
            body_.position_ = body_.prevPosition_;
        }
        else if (collisionEntity.Type() == EntityType::Coin) {
            coins_++;
        }
        else if (collisionEntity.Type() == EntityType::Entrance) {
            FaceDirection dir;
            propertyStore_.Get("FaceDirection", dir);
            if (dir == FaceDirection::Back) {
                auto& entrance = dynamic_cast<BasicEntity&>(collisionEntity);
                int exitObjId = 0;
                GetProperty(entrance, "ExitId", exitObjId);
                EntityId exitId = service_->ObjIdToEntityId(exitObjId);
                auto& exit = dynamic_cast<BasicEntity&>(service_->GetEntity(exitId));
                auto enterPos = GetPosition(entrance);
                auto exitPos = GetPosition(exit);
                auto event = std::make_shared<StartDoorMoveEvent>(enterPos, exitPos);
                ChangeStateTo(StateType::DoorMove, event);
            }
        }
    });
}

void PlayerEntity::DefineDoorMoveState(std::shared_ptr<State> state)
{
    auto updateCB = [this](Graphic::SpriteIf& drawable, const Shared::AnimationIf<Shared::ImageFrame>& animation) {
        drawable.setColor(sf::Color(255, 255, 255, 128));
    };
    auto sprite = state->RegisterSprite();
    FaceDirection* dir = nullptr;
    propertyStore_.GetPtr("FaceDirection", dir);
    std::initializer_list<ImageSelection> imageSelections{
        {FaceDirection::Front, service_->CreateImageAnimation(walkFrontImages)},
        {FaceDirection::Back, service_->CreateImageAnimation(walkBackImages)}};
    auto imageAnimator =
        std::make_shared<Animator<Shared::ImageFrame, FaceDirection>>(*sprite, imageSelections, *dir, true);
    imageAnimator->RegisterUpdateCb(updateCB);
    state->RegisterImageAnimator(imageAnimator);

    auto doorMove = std::make_shared<DoorMoveAbility>(
        body_, [this](const DoorMoveAbility::State& state, const sf::Vector2f& exitPos) {
            auto& cameraView = service_->GetCameraView();
            if (state == DoorMoveAbility::State::StartMovingToEntrance) {
                cameraView.SetFixPoint(body_.position_);
            }
            else if (state == DoorMoveAbility::State::StartMovingFromExit) {
                propertyStore_.Set("FaceDirection", FaceDirection::Front);
                cameraView.SetFixPoint(exitPos);
            }
            else if (state == DoorMoveAbility::State::Done) {
                cameraView.SetTrackPoint(body_.position_);
                ChangeStateTo(StateType::Idle, nullptr);
            }
        });

    state->RegisterAbility(doorMove);
    state->RegisterIgnoreEvents(
        {EventType::StartMove, EventType::StopMove, EventType::Attack, EventType::AttackWeapon});
}

void PlayerEntity::DefineAttackState(std::shared_ptr<State> state)
{
    auto updateCB = [this](Graphic::SpriteIf& drawable, const Shared::AnimationIf<Shared::ImageFrame>& animation) {
        if (animation.IsCompleted()) {
            ChangeStateTo(StateType::Idle, nullptr);
        }
    };
    auto sprite = state->RegisterSprite();
    FaceDirection* dir = nullptr;
    propertyStore_.GetPtr("FaceDirection", dir);
    std::initializer_list<ImageSelection> imageSelections{
        {FaceDirection::Left, service_->CreateImageAnimation(attackLeftImages)},
        {FaceDirection::Right, service_->CreateImageAnimation(attackRightImages)},
        {FaceDirection::Front, service_->CreateImageAnimation(attackFrontImages)},
        {FaceDirection::Back, service_->CreateImageAnimation(attackBackImages)}};
    auto imageAnimator = std::make_shared<Animator<Shared::ImageFrame, FaceDirection>>(*sprite, imageSelections, *dir);
    imageAnimator->RegisterUpdateCb(updateCB);
    state->RegisterImageAnimator(imageAnimator);
    auto rect = state->RegisterCollider(Shape::ColliderType::Entity);
    std::initializer_list<ColliderSelection> colliderSelections{
        {FaceDirection::Left, service_->CreateColliderAnimation(attackLeftColliders)},
        {FaceDirection::Right, service_->CreateColliderAnimation(attackRightColliders)},
        {FaceDirection::Front, service_->CreateColliderAnimation(attackFrontColliders)},
        {FaceDirection::Back, service_->CreateColliderAnimation(attackBackColliders)}};
    auto colliderAnimator =
        std::make_shared<Animator<Shared::ColliderFrame, FaceDirection>>(*rect, colliderSelections, *dir);
    state->RegisterColliderAnimator(colliderAnimator);
    state->RegisterEventCB(EventType::StartMove,
                           [this](std::shared_ptr<BasicEvent> event) { ChangeStateTo(StateType::Move, event); });
    state->RegisterIgnoreEvents({EventType::Attack, EventType::AttackWeapon});
}

void PlayerEntity::DefineAttackWeaponState(std::shared_ptr<State> state)
{
    auto updateCB = [this](Graphic::SpriteIf& drawable, const Shared::AnimationIf<Shared::ImageFrame>& animation) {
        if (animation.IsCompleted()) {
            OnShoot();
            ChangeStateTo(StateType::Idle, nullptr);
        }
    };
    auto sprite = state->RegisterSprite();
    FaceDirection* dir = nullptr;
    propertyStore_.GetPtr("FaceDirection", dir);
    std::initializer_list<ImageSelection> imageSelections{
        {FaceDirection::Left, service_->CreateImageAnimation(attackWLeftImages)},
        {FaceDirection::Right, service_->CreateImageAnimation(attackWRightImages)},
        {FaceDirection::Front, service_->CreateImageAnimation(attackWFrontImages)},
        {FaceDirection::Back, service_->CreateImageAnimation(attackWBackImages)}};
    auto imageAnimator = std::make_shared<Animator<Shared::ImageFrame, FaceDirection>>(*sprite, imageSelections, *dir);
    imageAnimator->RegisterUpdateCb(updateCB);
    state->RegisterImageAnimator(imageAnimator);
    auto rect = state->RegisterCollider(Shape::ColliderType::Entity);
    std::initializer_list<ColliderSelection> colliderSelections{
        {FaceDirection::Left, service_->CreateColliderAnimation(attackWLeftColliders)},
        {FaceDirection::Right, service_->CreateColliderAnimation(attackWRightColliders)},
        {FaceDirection::Front, service_->CreateColliderAnimation(attackWFrontColliders)},
        {FaceDirection::Back, service_->CreateColliderAnimation(attackWBackColliders)}};
    auto colliderAnimator =
        std::make_shared<Animator<Shared::ColliderFrame, FaceDirection>>(*rect, colliderSelections, *dir);
    state->RegisterColliderAnimator(colliderAnimator);
    state->RegisterEventCB(EventType::StartMove,
                           [this](std::shared_ptr<BasicEvent> event) { ChangeStateTo(StateType::Move, event); });
    state->RegisterIgnoreEvents({EventType::Attack, EventType::AttackWeapon});
}

}  // namespace Entity

}  // namespace FA
