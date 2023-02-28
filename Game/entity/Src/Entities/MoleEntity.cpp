/*
 *	Copyright (C) 2021 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#include "MoleEntity.h"

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

const Shared::AnimationData idleLeft{Shared::SheetId::MoleIdleSide, {{0, 0}, 1, 0}, true};
const Shared::AnimationData idleRight{Shared::SheetId::MoleIdleSide, {{0, 0}, 1, 0}, false};
const Shared::AnimationData idleDown{Shared::SheetId::MoleIdleFront, {{0, 0}, 1, 0}, false};
const Shared::AnimationData idleUp{Shared::SheetId::MoleIdleFront, {{0, 0}, 1, 0}, false};

const Shared::AnimationData walkLeft{Shared::SheetId::MoleWalkSide, {{0, 0}, 4, 0}, true};
const Shared::AnimationData walkRight{Shared::SheetId::MoleWalkSide, {{0, 0}, 4, 0}, false};
const Shared::AnimationData walkDown{Shared::SheetId::MoleWalkFront, {{0, 0}, 4, 0}, false};
const Shared::AnimationData walkUp{Shared::SheetId::MoleWalkBack, {{0, 0}, 4, 0}, false};

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
    RegisterIdleState(idleState);
    RegisterMoveState();
}

void MoleEntity::RegisterIdleState(std::shared_ptr<State> idleState)
{
    auto idleSprite = std::make_shared<AnimationSprite<FaceDirection>>(
        [this]() { return propertyStore_.Get<FaceDirection>("FaceDirection"); });
    idleSprite->RegisterResource(FaceDirection::Left, entityService_.MakeAnimation(idleLeft));
    idleSprite->RegisterResource(FaceDirection::Right, entityService_.MakeAnimation(idleRight));
    idleSprite->RegisterResource(FaceDirection::Down, entityService_.MakeAnimation(idleDown));
    idleSprite->RegisterResource(FaceDirection::Up, entityService_.MakeAnimation(idleUp));
    idleState->RegisterSprite(idleSprite);
    idleState->RegisterEventCB(EventType::StartMove,
                               [this](std::shared_ptr<BasicEvent> event) { ChangeStateTo(StateType::Move, event); });
    idleState->RegisterIgnoreEvents({EventType::StopMove, EventType::Collision});
}

void MoleEntity::RegisterMoveState()
{
    auto moveState = RegisterState(StateType::Move);
    auto move = std::make_shared<MoveAbility>(
        Constant::stdVelocity, [this](MoveDirection d) { OnBeginMove(d); },
        [this](const sf::Vector2f& d) { OnUpdateMove(d); });
    auto moveSprite = std::make_shared<AnimationSprite<FaceDirection>>(
        [this]() { return propertyStore_.Get<FaceDirection>("FaceDirection"); });
    moveSprite->RegisterResource(FaceDirection::Left, entityService_.MakeAnimation(walkLeft));
    moveSprite->RegisterResource(FaceDirection::Right, entityService_.MakeAnimation(walkRight));
    moveSprite->RegisterResource(FaceDirection::Down, entityService_.MakeAnimation(walkDown));
    moveSprite->RegisterResource(FaceDirection::Up, entityService_.MakeAnimation(walkUp));
    moveState->RegisterAbility(move);
    moveState->RegisterSprite(moveSprite);
    moveState->RegisterEventCB(EventType::StopMove,
                               [this](std::shared_ptr<BasicEvent> event) { ChangeStateTo(StateType::Idle, event); });
}

}  // namespace Entity

}  // namespace FA
