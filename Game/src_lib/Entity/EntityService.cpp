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
#include "Level/CameraManager.h"
#include "Resource/AnimationDb.h"

namespace FA {

namespace Entity {

EntityService::EntityService(EntityType entityType, CameraManager& cameraManager, const AnimationDb& animationDb)
    : cameraManager_(cameraManager)
    , entityType_(entityType)
    , animationDb_(animationDb)
{}

EntityService::~EntityService() = default;

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

void EntityService::InitProperties()
{
    auto dirs = attributeStore_.GetProperty<FaceDirectionAttribute>()->GetAvailableDirections();

    for (auto f : frameTypes_) {
        if (f == FrameType::Undefined) continue;
        for (auto face : dirs) {
            auto animation = animationDb_.GetAnimation(entityType_, f, face);
            attributeStore_.GetProperty<AnimationAttribute>()->AddAnimation(f, face, animation);
        }
    }
}

}  // namespace Entity

}  // namespace FA
