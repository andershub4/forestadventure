/*
 *	Copyright (C) 2021 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#include "EntityService.h"

#include "Attributes//CameraAttribute.h"
#include "Attributes//FaceDirectionAttribute.h"
#include "Attributes//TransformAttribute.h"
#include "Attributes/AnimationAttribute.h"
#include "Behaviors/AttackBehavior.h"
#include "Behaviors/AttackWeaponBehavior.h"
#include "Behaviors/MovementBehavior.h"
#include "Behaviors/IdleBehavior.h"
#include "Level/CameraManager.h"
#include "Resource/AnimationDb.h"

namespace FA {

namespace Entity {

EntityService::EntityService(EntityType entityType, CameraManager& cameraManager)
    : cameraManager_(cameraManager)
    , entityType_(entityType)
{}

EntityService::~EntityService() = default;

template <>
std::shared_ptr<IdleBehavior> EntityService::AddBehavior<IdleBehavior>()
{
    frameTypes_.push_back(FrameType::Idle);
    return behaviorStore_.AddProperty<IdleBehavior>(this);
}

template <>
std::shared_ptr<MovementBehavior> EntityService::AddBehavior<MovementBehavior>()
{
    frameTypes_.push_back(FrameType::Move);
    return behaviorStore_.AddProperty<MovementBehavior>(this);
}

template <>
std::shared_ptr<AttackBehavior> EntityService::AddBehavior<AttackBehavior>()
{
    frameTypes_.push_back(FrameType::Attack);
    return behaviorStore_.AddProperty<AttackBehavior>(this);
}

template <>
std::shared_ptr<AttackWeaponBehavior> EntityService::AddBehavior<AttackWeaponBehavior>()
{
    frameTypes_.push_back(FrameType::AttackWeapon);
    return behaviorStore_.AddProperty<AttackWeaponBehavior>(this);
}

template <>
std::shared_ptr<CameraAttribute> EntityService::AddAttribute<CameraAttribute>()
{
    auto t = GetAttribute<TransformAttribute>();
    cameraManager_.Track(t->GetPosition());
    return attributeStore_.AddProperty<CameraAttribute>(this);
}

void EntityService::Awake()
{
    attributeStore_.Awake();
    behaviorStore_.Awake();
}

void EntityService::InitProperties(const AnimationDb& animationDb)
{
    auto dirs = attributeStore_.GetProperty<FaceDirectionAttribute>()->GetAvailableDirections();

    for (auto f : frameTypes_) {
        for (auto face : dirs) {
            auto animation = animationDb.GetAnimation(entityType_, f, face);
            attributeStore_.GetProperty<AnimationAttribute>()->AddAnimation(f, face, animation);
        }
    }
}

}  // namespace Entity

}  // namespace FA
