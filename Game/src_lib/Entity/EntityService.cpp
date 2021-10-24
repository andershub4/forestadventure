/*
 *	Copyright (C) 2021 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#include "EntityService.h"

#include "Attributes//CameraAttribute.h"
#include "Attributes//FaceDirectionAttribute.h"
#include "Attributes//TransformAttribute.h"
#include "Level/CameraManager.h"
#include "Resource/AnimationDb.h"
#include "Shapes/Shape.h"

namespace FA {

namespace Entity {

EntityService::EntityService(EntityType entityType, CameraManager& cameraManager, const AnimationDb& animationDb)
    : cameraManager_(cameraManager)
    , entityType_(entityType)
    , animationDb_(animationDb)
    , shape_(std::make_shared<Shape>(this))
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
    modeStore_.Awake();
}

void EntityService::InitProperties()
{
    attributeStore_.Init();
    modeStore_.Init();
}

Animation EntityService::GetAnimation(FrameType frameType, FaceDirection faceDir) const
{
    return animationDb_.GetAnimation(entityType_, frameType, faceDir);
}

}  // namespace Entity

}  // namespace FA
