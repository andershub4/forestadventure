/*
 *	Copyright (C) 2021 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#include "MoleEntity.h"

#include <sstream>

#include <SFML/Graphics/RenderWindow.hpp>

#include "Constant/Entity.h"
#include "Entity/Abilities/MoveAbility.h"
#include "Entity/AnimationSprite.h"
#include "Entity/PropertyData.h"
#include "Entity/States/BasicState.h"
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
                       EntityManager& entityManager, MessageBus& messageBus)
    : BasicEntity(id, cameraManager, sheetManager, entityManager, messageBus)
{}

MoleEntity::~MoleEntity() = default;

void MoleEntity::OnBeginMove(FaceDirection faceDirection)
{
    propertyManager_.Set("FaceDirection", faceDirection);
}

void MoleEntity::OnUpdateMove(const sf::Vector2f& delta)
{
    auto current = propertyManager_.Get<sf::Vector2f>("Position");
    auto n = current + delta;
    propertyManager_.Set<sf::Vector2f>("Position", n);
}

void MoleEntity::RegisterAbilities()
{
    auto move = std::make_shared<MoveAbility>(
        constant::Entity::stdVelocity, [this](FaceDirection f) { OnBeginMove(f); },
        [this](const sf::Vector2f& d) { OnUpdateMove(d); });

    RegisterAbility(MoveAbility::Type(), move);
}

void MoleEntity::RegisterProperties()
{
    propertyManager_.Register<sf::Vector2f>("Position", {0.0, 0.0});
    propertyManager_.Register<FaceDirection>("FaceDirection", FaceDirection::Down);
}

void MoleEntity::OnUpdateShape(Shape& shape)
{
    shape.SetPosition(propertyManager_.Get<sf::Vector2f>("Position"));
}

void MoleEntity::RegisterShapes(const PropertyData& data)
{
    auto shape = std::make_shared<Shape>([this](Shape& shape) { OnUpdateShape(shape); });

    auto getKey = [this](StateType stateType) {
        std::stringstream ss;
        auto dir = propertyManager_.Get<FaceDirection>("FaceDirection");
        ss << stateType << dir;
        return ss.str();
    };

    auto sprite = std::make_shared<AnimationSprite>(getKey);

    for (const auto& stateData : animationDatas) {
        auto stateType = stateData.first;
        auto dirData = stateData.second;
        for (const auto& dir : dirData) {
            std::stringstream ss;
            ss << stateType << dir.first;
            auto a = entityService_.MakeAnimation(dir.second);
            sprite->RegisterAnimation(ss.str(), a);
        }
    }

    shape->RegisterAnimationSprite("Main", sprite);

    RegisterShape("Main", shape);
}

void MoleEntity::RegisterStates()
{
    auto idleState = RegisterState(StateType::Idle, true);
    idleState->AddShape("Main", nullptr);
    idleState->BindAction(Action::ChangeTo(StateType::Move), EventType::StartMove);
    idleState->BindAction(Action::Ignore(), EventType::Collision);

    auto moveState = RegisterState(StateType::Move);
    moveState->AddShape("Main", nullptr);
    moveState->AddAbility(MoveAbility::Type());
    moveState->BindAction(Action::ChangeTo(StateType::Idle), EventType::StopMove);
}

}  // namespace Entity

}  // namespace FA
