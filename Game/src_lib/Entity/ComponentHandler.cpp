/*
 *	Copyright (C) 2021 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#include "ComponentHandler.h"

#include "Components/AnimationComponent.h"
#include "Components/AttackComponent.h"
#include "Components/AttackWeaponComponent.h"
#include "Components/FaceDirectionComponent.h"
#include "Components/IdleComponent.h"
#include "Components/MovementComponent.h"
#include "Components/SpriteComponent.h"
#include "Components/TransformComponent.h"

#include "AnimationDb.h"

namespace FA {

namespace Entity {

ComponentHandler::ComponentHandler(const ComponentData& data)
    : data_(data)
{
    auto position = data.position_;
    auto scale = data.scale_;
    compStore_.AddComponent<TransformComponent>(position, scale);
    compStore_.AddComponent<IdleComponent>();
    frameTypes_.push_back(FrameType::Idle);
}

ComponentHandler::~ComponentHandler() = default;

template <>
std::shared_ptr<MovementComponent> ComponentHandler::AddComponent<MovementComponent>()
{
    frameTypes_.push_back(FrameType::Move);
    auto t = compStore_.GetComponent<TransformComponent>();
    auto velocity = data_.velocity_;
    return compStore_.AddComponent<MovementComponent>(*t, velocity);
}

template <>
std::shared_ptr<AttackComponent> ComponentHandler::AddComponent<AttackComponent>()
{
    frameTypes_.push_back(FrameType::Attack);
    return compStore_.AddComponent<AttackComponent>();
}

template <>
std::shared_ptr<AttackWeaponComponent> ComponentHandler::AddComponent<AttackWeaponComponent>()
{
    frameTypes_.push_back(FrameType::AttackWeapon);
    return compStore_.AddComponent<AttackWeaponComponent>();
}

template <>
std::shared_ptr<SpriteComponent> ComponentHandler::AddComponent<SpriteComponent>()
{
    auto t = compStore_.GetComponent<TransformComponent>();
    auto d = compStore_.GetComponent<FaceDirectionComponent>();
    return compStore_.AddComponent<SpriteComponent>(*t, *d);
}

void ComponentHandler::InitComponents(const AnimationDb& animationDb)
{
    auto dirs = compStore_.GetComponent<FaceDirectionComponent>()->GetAvailableDirections();

    for (auto f : frameTypes_) {
        for (auto face : dirs) {
            auto animation = animationDb.GetAnimation(data_.entityType_, f, face);
            compStore_.GetComponent<AnimationComponent>()->AddAnimation(f, face, animation);
        }
    }
}

}  // namespace Entity

}  // namespace FA
