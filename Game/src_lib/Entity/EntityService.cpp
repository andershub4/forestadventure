/*
 *	Copyright (C) 2021 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#include "EntityService.h"

#include "Attributes//CameraAttribute.h"
#include "Attributes//FaceDirectionAttribute.h"
#include "Attributes//TransformAttribute.h"
#include "EntityManager.h"
#include "Level/CameraManager.h"
#include "Shape.h"
#include "SpawnManager.h"

namespace FA {

namespace Entity {

EntityService::EntityService(CameraManager& cameraManager, const SheetManager& sheetManager,
                             EntityManager& entityManager)
    : cameraManager_(cameraManager)
    , animationDb_(sheetManager)
    , imageDb_(sheetManager)
    , shape_(std::make_shared<Shape>(this))
    , entityManager_(entityManager)
    , spawnManager_(entityManager)
{}

EntityService::~EntityService() = default;

template <>
std::shared_ptr<CameraAttribute> EntityService::AddAttribute<CameraAttribute>()
{
    auto t = GetAttribute<TransformAttribute>();
    cameraManager_.Track(t->GetPosition());
    return attributeStore_.AddAttribute<CameraAttribute>(this);
}

sf::Vector2u EntityService::GetMapSize() const
{
    return cameraManager_.GetMapSize();
}

void EntityService::LoadAnimation(EntityType entityType, const AnimationData& data)
{
    animationDb_.LoadAnimation(entityType, data);
}

Animation EntityService::GetAnimation(EntityType entityType, FrameType frameType, FaceDirection faceDir) const
{
    return animationDb_.GetAnimation(entityType, frameType, faceDir);
}

void EntityService::LoadImage(EntityType entityType, const ImageData& data)
{
    imageDb_.LoadImage(entityType, data);
}

Image EntityService::GetImage(EntityType entityType, FrameType frameType, FaceDirection faceDir) const
{
    return imageDb_.GetImage(entityType, frameType, faceDir);
}

void EntityService::SpawnEntity()
{
    auto position = GetAttribute<TransformAttribute>()->GetPosition();
    auto scale = GetAttribute<TransformAttribute>()->GetScale();
    auto faceDirection = GetAttribute<FaceDirectionAttribute>()->GetDirection();
    float velocity = 120.0f;
    spawnManager_.SpawnArrow(position, faceDirection, scale, velocity);
}

void EntityService::DeleteEntity(EntityId id)
{
    entityManager_.DeleteEntity(id);
}

}  // namespace Entity

}  // namespace FA
