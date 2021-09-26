/*
 *	Copyright (C) 2021 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#include "ComponentHandler.h"

#include "Components/AnimationComponent.h"
#include "Components/AttackComponent.h"
#include "Components/AttackWeaponComponent.h"
#include "Components/CameraComponent.h"
#include "Components/FaceDirectionComponent.h"
#include "Components/IdleComponent.h"
#include "Components/MovementComponent.h"
#include "Components/TransformComponent.h"
#include "Level/CameraManager.h"
#include "Resource/AnimationDb.h"

namespace FA {

namespace Entity {

ComponentHandler::ComponentHandler(const ComponentData& data, CameraManager& cameraManager)
    : data_(data)
    , cameraManager_(cameraManager)
{
    auto t = compStore_.AddComponent<TransformComponent>(this);
    t->SetPosition(data.position_);
    t->SetScale(data.scale_);
    compStore_.AddComponent<IdleComponent>(this);
    frameTypes_.push_back(FrameType::Idle);
}

ComponentHandler::~ComponentHandler() = default;

template <>
std::shared_ptr<MovementComponent> ComponentHandler::AddComponent<MovementComponent>()
{
    frameTypes_.push_back(FrameType::Move);
    auto m = compStore_.AddComponent<MovementComponent>(this);
    m->SetVelocity(data_.velocity_);
    return m;
}

template <>
std::shared_ptr<AttackComponent> ComponentHandler::AddComponent<AttackComponent>()
{
    frameTypes_.push_back(FrameType::Attack);
    return compStore_.AddComponent<AttackComponent>(this);
}

template <>
std::shared_ptr<AttackWeaponComponent> ComponentHandler::AddComponent<AttackWeaponComponent>()
{
    frameTypes_.push_back(FrameType::AttackWeapon);
    return compStore_.AddComponent<AttackWeaponComponent>(this);
}

template <>
std::shared_ptr<CameraComponent> ComponentHandler::AddComponent<CameraComponent>()
{
    auto t = compStore_.GetComponent<TransformComponent>();
    cameraManager_.Track(t->GetPosition());
    return compStore_.AddComponent<CameraComponent>(this);
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
