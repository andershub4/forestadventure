/*
 *	Copyright (C) 2021 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#include "MoleEntity.h"

#include <sstream>

#include <SFML/Graphics/RenderWindow.hpp>

#include "Abilities/MoveAbility.h"
#include "Constant/Entity.h"
#include "PropertyConverter.h"
#include "PropertyData.h"
#include "Resource/AnimationData.h"
#include "Resource/SheetId.h"
#include "Sprites/AnimationSprite.h"
#include "State.h"

namespace FA {

namespace Entity {

namespace {

const std::unordered_map<StateType, std::unordered_map<FaceDirection, Shared::AnimationData>> animationDatas = {
    {StateType::Move,
     {{FaceDirection::Left, {Shared::SheetId::MoleWalkSide, {{0, 0}, 4, 0}, true}},
      {FaceDirection::Right, {Shared::SheetId::MoleWalkSide, {{0, 0}, 4, 0}, false}},
      {FaceDirection::Down, {Shared::SheetId::MoleWalkFront, {{0, 0}, 4, 0}, false}},
      {FaceDirection::Up, {Shared::SheetId::MoleWalkBack, {{0, 0}, 4, 0}, false}}}},
    {StateType::Idle,
     {{FaceDirection::Left, {Shared::SheetId::MoleIdleSide, {{0, 0}, 1, 0}, true}},
      {FaceDirection::Right, {Shared::SheetId::MoleIdleSide, {{0, 0}, 1, 0}, false}},
      {FaceDirection::Down, {Shared::SheetId::MoleIdleFront, {{0, 0}, 1, 0}, false}},
      {FaceDirection::Up, {Shared::SheetId::MoleIdleFront, {{0, 0}, 1, 0}, false}}}}};

}  // namespace

const std::string MoleEntity::str = "Mole";

MoleEntity::MoleEntity(EntityId id, const PropertyData& data, const EntityService& service)
    : BasicEntity(id, data, service)
{}

MoleEntity::~MoleEntity() = default;

void MoleEntity::OnBeginMove(MoveDirection moveDirection)
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

void MoleEntity::OnUpdateMove(const sf::Vector2f& delta)
{
    body_.position_ += delta;
}

std::string MoleEntity::AnimationKey() const
{
    std::stringstream ss;
    auto dir = propertyStore_.Get<FaceDirection>("FaceDirection");
    ss << dir;
    return ss.str();
}

std::unordered_map<std::string, Shared::Animation> MoleEntity::GetAnimations(
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

void MoleEntity::RegisterProperties()
{
    propertyStore_.Register<FaceDirection>("FaceDirection", FaceDirection::Down);
}

void MoleEntity::ReadProperties(const std::unordered_map<std::string, std::string>& properties)
{
    for (const auto& p : properties) {
        if (p.first == "FaceDirection") {
            FaceDirection dir = ToValue<FaceDirection>(p.second);
            propertyStore_.Set<FaceDirection>(p.first, dir);
        }
    }
}

void MoleEntity::RegisterStates(std::shared_ptr<State> idleState, std::shared_ptr<State> deadState,
                                const PropertyData& data)
{
    auto idleAnimations = GetAnimations(animationDatas.at(StateType::Idle));
    auto idleAnimation = std::make_shared<AnimationSprite>(std::bind(&MoleEntity::AnimationKey, this), idleAnimations);
    idleState->RegisterSprite(idleAnimation);
    idleState->RegisterEventCB(EventType::StartMove,
                               [this](std::shared_ptr<BasicEvent> event) { ChangeStateTo(StateType::Move, event); });
    idleState->RegisterIgnoreEvents({EventType::StopMove, EventType::Collision});

    auto moveState = RegisterState(StateType::Move);
    auto move = std::make_shared<MoveAbility>(
        Constant::stdVelocity, [this](MoveDirection d) { OnBeginMove(d); },
        [this](const sf::Vector2f& d) { OnUpdateMove(d); });
    auto moveAnimations = GetAnimations(animationDatas.at(StateType::Move));
    auto moveAnimation = std::make_shared<AnimationSprite>(std::bind(&MoleEntity::AnimationKey, this), moveAnimations);
    moveState->RegisterAbility(move);
    moveState->RegisterSprite(moveAnimation);
    moveState->RegisterEventCB(EventType::StopMove,
                               [this](std::shared_ptr<BasicEvent> event) { ChangeStateTo(StateType::Idle, event); });
}

}  // namespace Entity

}  // namespace FA
