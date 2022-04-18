/*
 *	Copyright (C) 2021 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#include "MoleEntity.h"

#include <SFML/Graphics/RenderWindow.hpp>

#include "Constant/Entity.h"
#include "Entity/PropertyData.h"
#include "Entity/States/IdleState.h"
#include "Entity/States/MoveState.h"
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

void MoleEntity::RegisterStates(StateMachine& stateMachine)
{
    auto idleState = stateMachine.RegisterState<IdleState>(true);
    idleState->BindAction(Action::ChangeTo(StateType::Move), EventType::StartMove);
    idleState->BindAction(Action::Ignore(), EventType::Collision);

    auto moveState = stateMachine.RegisterState<MoveState>();
    moveState->BindAction(Action::ChangeTo(StateType::Idle), EventType::StopMove);
}

void MoleEntity::RegisterProperties(EntityService& entityService)
{
    entityService.RegisterProperty<float>("Rotation", 0.0);
    entityService.RegisterProperty<float>("Scale", 1.0);
    entityService.RegisterProperty<sf::Vector2f>("Position", {0.0, 0.0});
    entityService.RegisterProperty<float>("Velocity", constant::Entity::stdVelocity);
    entityService.RegisterProperty<FaceDirection>("FaceDirection", FaceDirection::Down);
    entityService.RegisterProperty<std::vector<FaceDirection>>(
        "FaceDirections", {FaceDirection::Down, FaceDirection::Up, FaceDirection::Left, FaceDirection::Right});
}

void MoleEntity::BuildAnimations(const EntityService& entityService, StateType stateType)
{
    auto directions = entityService.GetProperty<std::vector<FaceDirection>>("FaceDirections");
    auto stateData = animationDatas.at(stateType);
    auto& m = animations_[stateType];

    for (auto direction : directions) {
        m[direction] = entityService.MakeAnimation(stateData.at(direction));
    }
}

Animation MoleEntity::GetAnimation(const EntityService& entityService, StateType stateType) const
{
    auto dir = entityService.GetProperty<FaceDirection>("FaceDirection");

    return animations_.at(stateType).at(dir);
}

void MoleEntity::InitState(std::shared_ptr<BasicState> state, const std::vector<FaceDirection>& directions,
                           const EntityService& entityService)
{
    auto stateType = state->GetStateType();

    BuildAnimations(entityService, stateType);
    state->SetAnimationFn(
        [this, stateType](const EntityService& entityService) { return GetAnimation(entityService, stateType); });
}

void MoleEntity::InitStates(const StateMachine& stateMachine, const EntityService& entityService,
                            const PropertyData& data)
{
    auto directions = entityService.GetProperty<std::vector<FaceDirection>>("FaceDirections");

    InitState(stateMachine.GetState(StateType::Idle), directions, entityService);
    InitState(stateMachine.GetState(StateType::Move), directions, entityService);
}

}  // namespace Entity

}  // namespace FA
