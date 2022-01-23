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

void EntityService::AddAnimation(EntityType entityType, const AnimationData& data)
{
    animationDb_.AddAnimation(entityType, data);
}

Animation EntityService::GetAnimation(EntityType entityType, FrameType frameType, FaceDirection faceDir) const
{
    return animationDb_.GetAnimation(entityType, frameType, faceDir);
}

void EntityService::AddImage(EntityType entityType, const ImageData& data)
{
    imageDb_.AddImage(entityType, data);
}

Image EntityService::GetImage(EntityType entityType, FrameType frameType, FaceDirection faceDir) const
{
    return imageDb_.GetImage(entityType, frameType, faceDir);
}

void EntityService::SpawnEntity(EntityType entityType, FaceDirection faceDirection, const sf::Vector2f& position,
                                float scale, float velocity)
{
    spawnManager_.Spawn(entityType, position, faceDirection, scale, velocity);
}

void EntityService::DeleteEntity(EntityId id)
{
    entityManager_.DeleteEntity(id);
}

}  // namespace Entity

}  // namespace FA
