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
#include "Shapes/Shape.h"

namespace FA {

namespace Entity {

EntityService::EntityService(CameraManager& cameraManager, SheetManager& sheetManager)
    : cameraManager_(cameraManager)
    , animationDb_(sheetManager)
    , shape_(std::make_shared<Shape>(this))
{}

EntityService::~EntityService() = default;

template <>
std::shared_ptr<CameraAttribute> EntityService::AddAttribute<CameraAttribute>()
{
    auto t = GetAttribute<TransformAttribute>();
    cameraManager_.Track(t->GetPosition());
    return attributeStore_.AddAttribute<CameraAttribute>(this);
}

void EntityService::LoadAnimations(EntityType entityType, const std::vector<AnimationData>& animationData)
{
    animationDb_.Load(entityType, animationData);
}

Animation EntityService::GetAnimation(EntityType entityType, FrameType frameType, FaceDirection faceDir) const
{
    return animationDb_.GetAnimation(entityType, frameType, faceDir);
}

void EntityService::AddModeType(ModeType modeType)
{
    modeTypes_.push_back(modeType);
}

}  // namespace Entity

}  // namespace FA
