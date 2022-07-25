/*
 *	Copyright (C) 2021 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#include "EntityService.h"

#include "Constant/Entity.h"
#include "EntityManager.h"
#include "Level/CameraManager.h"
#include "Resource/Animation.h"
#include "Resource/AnimationData.h"
#include "Resource/Image.h"
#include "Resource/ImageData.h"
#include "Resource/SheetManager.h"
#include "SpawnManager.h"

namespace FA {

namespace Entity {

EntityService::EntityService(CameraManager& cameraManager, const SheetManager& sheetManager,
                             EntityManager& entityManager, const sf::Vector2u& mapSize)
    : cameraManager_(cameraManager)
    , sheetManager_(sheetManager)
    , entityManager_(entityManager)
    , spawnManager_(entityManager)
{
    mapRect_ = sf::FloatRect({0.0f, 0.0f}, static_cast<sf::Vector2f>(mapSize));
}

EntityService::~EntityService() = default;

void EntityService::AddCamera(sf::Vector2f& pos)
{
    cameraManager_.Track(pos);
}

sf::FloatRect EntityService::GetMapRect() const
{
    return mapRect_;
}

Animation EntityService::MakeAnimation(const AnimationData& data) const
{
    float t = constant::Entity::stdSwitchTime;
    auto frames = sheetManager_.MakeFrames(data);
    return Animation(frames, data.locationData_.defaultIndex_, t);
}

Image EntityService::MakeImage(const ImageData& data) const
{
    auto frame = sheetManager_.MakeFrame(data);
    return Image(frame);
}

void EntityService::SpawnEntity(EntityType entityType, FaceDirection faceDirection, const sf::Vector2f& position)
{
    spawnManager_.Spawn(entityType, position, faceDirection);
}

void EntityService::DeleteEntity(EntityId id)
{
    entityManager_.DeleteEntity(id);
}

}  // namespace Entity

}  // namespace FA
