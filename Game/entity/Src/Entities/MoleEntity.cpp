/*
 *	Copyright (C) 2021 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#include "MoleEntity.h"

#include <initializer_list>
#include <memory>

#include <SFML/Graphics/RenderWindow.hpp>

#include "Abilities/MoveAbility.h"
#include "Animation/AnimationIf.h"
#include "Animator/Animator.h"
#include "Constant/Entity.h"
#include "Events/CollisionEvent.h"
#include "Events/DeadEvent.h"
#include "Logging.h"
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

using namespace Shared::SheetId;

const Shared::SheetItem idleSide1{MoleIdleSide, {0, 0}};
const Shared::SheetItem idleFront1{MoleIdleFront, {0, 0}};
const Shared::SheetItem idleBack1{MoleIdleBack, {0, 0}};

const Shared::SheetItem moveSide1{MoleWalkSide, {0, 0}};
const Shared::SheetItem moveSide2{MoleWalkSide, {1, 0}};
const Shared::SheetItem moveSide3{MoleWalkSide, {2, 0}};
const Shared::SheetItem moveSide4{MoleWalkSide, {3, 0}};

const Shared::SheetItem moveDown1{MoleWalkFront, {0, 0}};
const Shared::SheetItem moveDown2{MoleWalkFront, {1, 0}};
const Shared::SheetItem moveDown3{MoleWalkFront, {2, 0}};
const Shared::SheetItem moveDown4{MoleWalkFront, {3, 0}};

const Shared::SheetItem moveUp1{MoleWalkBack, {0, 0}};
const Shared::SheetItem moveUp2{MoleWalkBack, {1, 0}};
const Shared::SheetItem moveUp3{MoleWalkBack, {2, 0}};
const Shared::SheetItem moveUp4{MoleWalkBack, {3, 0}};

const Shared::SheetItem collision1{Death, {0, 0}};
const Shared::SheetItem collision2{Death, {1, 0}};
const Shared::SheetItem collision3{Death, {2, 0}};
const Shared::SheetItem collision4{Death, {3, 0}};
const Shared::SheetItem collision5{Death, {4, 0}};
const Shared::SheetItem collision6{Death, {5, 0}};

const std::vector<Shared::ImageData> idleLeftImages{{idleSide1, true}};
const std::vector<Shared::ImageData> idleRightImages{idleSide1};
const std::vector<Shared::ImageData> idleFrontImages{idleFront1};
const std::vector<Shared::ImageData> idleBackImages{idleBack1};
const std::vector<Shared::ImageData> moveLeftImages{
    {moveSide1, true}, {moveSide2, true}, {moveSide3, true}, {moveSide4, true}};
const std::vector<Shared::ImageData> moveRightImages{moveSide1, moveSide2, moveSide3, moveSide4};
const std::vector<Shared::ImageData> moveDownImages{moveDown1, moveDown2, moveDown3, moveDown4};
const std::vector<Shared::ImageData> moveUpImages{moveUp1, moveUp2, moveUp3, moveUp4};

const std::vector<Shared::ImageData> collisionImages{collision1, collision2, collision3,
                                                     collision4, collision5, collision6};

const sf::IntRect rect{6, 4, 12, 18};

const std::vector<Shared::ColliderData> idleLeftColliders{{idleSide1, rect}};
const std::vector<Shared::ColliderData> idleRightColliders{{idleSide1, rect}};
const std::vector<Shared::ColliderData> idleFrontColliders{{idleFront1, rect}};
const std::vector<Shared::ColliderData> idleBackColliders{{idleBack1, rect}};
const std::vector<Shared::ColliderData> moveLeftColliders{
    {moveSide1, rect}, {moveSide2, rect}, {moveSide3, rect}, {moveSide4, rect}};
const std::vector<Shared::ColliderData> moveRightColliders{
    {moveSide1, rect}, {moveSide2, rect}, {moveSide3, rect}, {moveSide4, rect}};
const std::vector<Shared::ColliderData> moveDownColliders{
    {moveDown1, rect}, {moveDown2, rect}, {moveDown3, rect}, {moveDown4, rect}};
const std::vector<Shared::ColliderData> moveUpColliders{
    {moveUp1, rect}, {moveUp2, rect}, {moveUp3, rect}, {moveUp4, rect}};

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

const std::string MoleEntity::str = "Mole";

MoleEntity::MoleEntity(EntityId id, const Shared::EntityData& data, std::unique_ptr<EntityService> service)
    : BasicEntity(id, data, std::move(service))
{}

MoleEntity::~MoleEntity() = default;

void MoleEntity::OnBeginMove(MoveDirection moveDirection)
{
    FaceDirection faceDir = MoveDirToFaceDir(moveDirection);
    propertyStore_.Set("FaceDirection", faceDir);
}

void MoleEntity::OnUpdateMove(const sf::Vector2f& delta)
{
    body_.position_ += delta;
}

void MoleEntity::RegisterProperties()
{
    propertyStore_.Register("FaceDirection", FaceDirection::Down);
}

void MoleEntity::ReadProperties(const std::unordered_map<std::string, std::string>& properties)
{
    for (const auto& p : properties) {
        if (p.first == "FaceDirection") {
            FaceDirection dir = ToValue<FaceDirection>(p.second);
            propertyStore_.Set(p.first, dir);
        }
    }
}

void MoleEntity::RegisterStates(std::shared_ptr<State> idleState, std::shared_ptr<State> deadState,
                                const Shared::EntityData& data)
{
    DefineIdleState(idleState);
    auto moveState = RegisterState(StateType::Move);
    DefineMoveState(moveState);
    auto collisionState = RegisterState(StateType::Collision);
    DefineCollisionState(collisionState);
}

void MoleEntity::DefineIdleState(std::shared_ptr<State> state)
{
    auto sprite = state->RegisterSprite();
    FaceDirection* dir = nullptr;
    propertyStore_.GetPtr("FaceDirection", dir);
    std::initializer_list<ImageSelection> imageSelections{
        {FaceDirection::Left, service_->CreateImageAnimation(idleLeftImages)},
        {FaceDirection::Right, service_->CreateImageAnimation(idleRightImages)},
        {FaceDirection::Down, service_->CreateImageAnimation(idleFrontImages)},
        {FaceDirection::Up, service_->CreateImageAnimation(idleBackImages)}};
    auto imageAnimator = std::make_shared<Animator<Shared::ImageFrame, FaceDirection>>(*sprite, imageSelections, *dir);
    state->RegisterImageAnimator(imageAnimator);
    auto rect = state->RegisterCollider(Shape::ColliderType::Entity);
    std::initializer_list<ColliderSelection> colliderSelections{
        {FaceDirection::Left, service_->CreateColliderAnimation(idleLeftColliders)},
        {FaceDirection::Right, service_->CreateColliderAnimation(idleRightColliders)},
        {FaceDirection::Down, service_->CreateColliderAnimation(idleFrontColliders)},
        {FaceDirection::Up, service_->CreateColliderAnimation(idleBackColliders)}};
    auto colliderAnimator =
        std::make_shared<Animator<Shared::ColliderFrame, FaceDirection>>(*rect, colliderSelections, *dir);
    state->RegisterColliderAnimator(colliderAnimator);
    state->RegisterEventCB(EventType::StartMove,
                           [this](std::shared_ptr<BasicEvent> event) { ChangeStateTo(StateType::Move, event); });
    state->RegisterEventCB(EventType::Collision, [this](std::shared_ptr<BasicEvent> event) {
        auto collisionEvent = std::dynamic_pointer_cast<CollisionEvent>(event);
        if (service_->GetEntity(collisionEvent->id_).Type() == EntityType::Arrow) {
            ChangeStateTo(StateType::Collision, event);
        }
    });
    state->RegisterIgnoreEvents({EventType::StopMove});
}

void MoleEntity::DefineMoveState(std::shared_ptr<State> state)
{
    auto sprite = state->RegisterSprite();
    FaceDirection* dir = nullptr;
    propertyStore_.GetPtr("FaceDirection", dir);
    std::initializer_list<ImageSelection> imageSelections{
        {FaceDirection::Left, service_->CreateImageAnimation(moveLeftImages)},
        {FaceDirection::Right, service_->CreateImageAnimation(moveRightImages)},
        {FaceDirection::Down, service_->CreateImageAnimation(moveDownImages)},
        {FaceDirection::Up, service_->CreateImageAnimation(moveUpImages)}};
    auto imageAnimator = std::make_shared<Animator<Shared::ImageFrame, FaceDirection>>(*sprite, imageSelections, *dir);
    state->RegisterImageAnimator(imageAnimator);
    auto rect = state->RegisterCollider(Shape::ColliderType::Entity);
    std::initializer_list<ColliderSelection> colliderSelections{
        {FaceDirection::Left, service_->CreateColliderAnimation(moveLeftColliders)},
        {FaceDirection::Right, service_->CreateColliderAnimation(moveRightColliders)},
        {FaceDirection::Down, service_->CreateColliderAnimation(moveDownColliders)},
        {FaceDirection::Up, service_->CreateColliderAnimation(moveUpColliders)}};
    auto colliderAnimator =
        std::make_shared<Animator<Shared::ColliderFrame, FaceDirection>>(*rect, colliderSelections, *dir);
    state->RegisterColliderAnimator(colliderAnimator);
    auto move = std::make_shared<MoveAbility>(
        Constant::stdVelocity, [this](MoveDirection d) { OnBeginMove(d); },
        [this](const sf::Vector2f& d) { OnUpdateMove(d); });
    state->RegisterAbility(move);
    state->RegisterEventCB(EventType::StopMove,
                           [this](std::shared_ptr<BasicEvent> event) { ChangeStateTo(StateType::Idle, event); });
    state->RegisterEventCB(EventType::Collision, [this](std::shared_ptr<BasicEvent> event) {
        auto collisionEvent = std::dynamic_pointer_cast<CollisionEvent>(event);
        if (service_->GetEntity(collisionEvent->id_).Type() == EntityType::Arrow) {
            ChangeStateTo(StateType::Collision, event);
        }
    });
}

void MoleEntity::DefineCollisionState(std::shared_ptr<State> state)
{
    auto updateCB = [this](Graphic::SpriteIf& drawable, const Shared::AnimationIf<Shared::ImageFrame>& animation) {
        if (animation.IsCompleted()) {
            HandleEvent(std::make_shared<DeadEvent>());
        }
    };
    auto animation = service_->CreateImageAnimation(collisionImages);
    auto sprite = state->RegisterSprite();
    auto imageAnimator = std::make_shared<Animator<Shared::ImageFrame>>(*sprite, animation);
    imageAnimator->RegisterUpdateCb(updateCB);
    state->RegisterImageAnimator(imageAnimator);
}

}  // namespace Entity

}  // namespace FA
