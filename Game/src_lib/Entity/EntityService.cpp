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
#include "Resource/Image.h"
#include "Shape.h"
#include "SpawnManager.h"

namespace FA {

namespace Entity {

EntityService::EntityService(CameraManager& cameraManager, const SheetManager& sheetManager,
                             EntityManager& entityManager)
    : cameraManager_(cameraManager)
    , sheetManager_(sheetManager)
    , shape_(std::make_shared<Shape>(this))
    , entityManager_(entityManager)
    , spawnManager_(entityManager)
{}

EntityService::~EntityService() = default;

void EntityService::AddCamera()
{
    cameraManager_.Track(propertyManager_.GetRef<sf::Vector2f>("Position"));
}

void EntityService::ReadObjectData(const sf::Vector2f& position)
{
    propertyManager_.Set<sf::Vector2f>("Position", position);
}

void EntityService::ReadCustomProperty(const std::string& name, const std::string& valueStr)
{
    propertyManager_.ReadCustomProperty(name, valueStr);
}

sf::Vector2u EntityService::GetMapSize() const
{
    return cameraManager_.GetMapSize();
}

Animation EntityService::MakeAnimation(const AnimationData& data) const
{
    float t = constant::Entity::stdSwitchTime;
    auto frames = frameHandler_.MakeFrames(sheetManager_, data);
    auto alignFn = [](sf::Sprite& sprite) {
        sprite.setOrigin(sprite.getLocalBounds().width / 2, sprite.getLocalBounds().height / 2);
    };
    return Animation(frames, data.locationData_.defaultIndex_, t, alignFn);
}

Image EntityService::MakeImage(const ImageData& data) const
{
    auto frame = frameHandler_.MakeFrame(sheetManager_, data);
    return Image(frame);
}

void EntityService::SpawnEntity(EntityType entityType, FaceDirection faceDirection, const sf::Vector2f& position,
                                float rotation)
{
    spawnManager_.Spawn(entityType, position, faceDirection, rotation);
}

void EntityService::DeleteEntity(EntityId id)
{
    entityManager_.DeleteEntity(id);
}

}  // namespace Entity

}  // namespace FA
