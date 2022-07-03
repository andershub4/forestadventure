/*
 *	Copyright (C) 2021 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#include "MoleEntity.h"

#include <sstream>

#include <SFML/Graphics/RenderWindow.hpp>

#include "Constant/Entity.h"
#include "Entity/Abilities/AnimationAbility.h"
#include "Entity/Abilities/MoveAbility.h"
#include "Entity/PropertyData.h"
#include "Entity/State.h"
#include "Resource/SheetId.h"

namespace FA {

namespace Entity {

namespace {

const std::unordered_map<StateType, std::unordered_map<FaceDirection, AnimationData>> animationDatas = {
    {StateType::Move,
     {{FaceDirection::Left, {SheetId::MoleWalkSide, {{0, 0}, 4, 0}, true}},
      {FaceDirection::Right, {SheetId::MoleWalkSide, {{0, 0}, 4, 0}, false}},
      {FaceDirection::Down, {SheetId::MoleWalkFront, {{0, 0}, 4, 0}, false}},
      {FaceDirection::Up, {SheetId::MoleWalkBack, {{0, 0}, 4, 0}, false}}}},
    {StateType::Idle,
     {{FaceDirection::Left, {SheetId::MoleIdleSide, {{0, 0}, 1, 0}, true}},
      {FaceDirection::Right, {SheetId::MoleIdleSide, {{0, 0}, 1, 0}, false}},
      {FaceDirection::Down, {SheetId::MoleIdleFront, {{0, 0}, 1, 0}, false}},
      {FaceDirection::Up, {SheetId::MoleIdleFront, {{0, 0}, 1, 0}, false}}}}};

}  // namespace

MoleEntity::MoleEntity(EntityId id, CameraManager& cameraManager, const SheetManager& sheetManager,
                       EntityManager& entityManager, MessageBus& messageBus, const sf::Vector2u& mapSize)
    : BasicEntity(id, cameraManager, sheetManager, entityManager, messageBus, mapSize)
{}

MoleEntity::~MoleEntity() = default;

void MoleEntity::OnBeginMove(FaceDirection faceDirection)
{
    propertyManager_.Set("FaceDirection", faceDirection);
}

void MoleEntity::OnUpdateMove(const sf::Vector2f& delta)
{
    position_ += delta;
}

void MoleEntity::OnUpdateAnimation(const Animation& animation)
{
    auto& sprite = shape_.GetSprite("Main");
    animation.ApplyTo(sprite);
    sprite.setOrigin(sprite.getLocalBounds().width / 2, sprite.getLocalBounds().height / 2);
}

void MoleEntity::RegisterProperties()
{
    propertyManager_.Register<FaceDirection>("FaceDirection", FaceDirection::Down);
}

void MoleEntity::RegisterShape()
{
    shape_ = CreateShape();
    shape_.AddSprite("Main");
}

void MoleEntity::RegisterStates(const PropertyData& data)
{
    auto getKey = [this]() {
        std::stringstream ss;
        auto dir = propertyManager_.Get<FaceDirection>("FaceDirection");
        ss << dir;
        return ss.str();
    };
    auto updateAnimation = [this](const Animation& animation) { OnUpdateAnimation(animation); };

    auto idleState = RegisterState(StateType::Idle, true);
    auto idleAnimation = std::make_shared<AnimationAbility>(getKey, updateAnimation);
    for (const auto& dir : animationDatas.at(StateType::Idle)) {
        std::stringstream ss;
        ss << dir.first;
        auto a = entityService_.MakeAnimation(dir.second);
        idleAnimation->RegisterAnimation(ss.str(), a);
    }
    idleState->RegisterAbility(idleAnimation);
    idleState->RegisterEventCB(EventType::StartMove,
                               [this](std::shared_ptr<BasicEvent> event) { ChangeState(StateType::Move, event); });
    idleState->RegisterEventCB(EventType::StopMove, [this](std::shared_ptr<BasicEvent> event) {});
    idleState->RegisterEventCB(EventType::Collision, [this](std::shared_ptr<BasicEvent> event) {});

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
                               [this](std::shared_ptr<BasicEvent> event) { ChangeState(StateType::Idle, event); });
}

}  // namespace Entity

}  // namespace FA
