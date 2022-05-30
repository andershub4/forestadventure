/*
 *	Copyright (C) 2021 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#pragma once

#include <memory>

#include "Enum/FaceDirection.h"
#include "Id.h"
#include "Logging.h"
#include "Resource/FrameHandler.h"
#include "SpawnManager.h"

namespace FA {

class CameraManager;
class Animation;
class Image;
class SheetManager;

namespace Entity {

class EntityManager;

class EntityService
{
public:
    EntityService(CameraManager &cameraManager, const SheetManager &sheetManager, EntityManager &entityManager);
    ~EntityService();

    void AddCamera(sf::Vector2f &pos);

    sf::Vector2u GetMapSize() const;

    Animation MakeAnimation(const AnimationData &data) const;
    Image MakeImage(const ImageData &data) const;

    void SpawnEntity(EntityType entityType, FaceDirection faceDirection, const sf::Vector2f &position);
    void DeleteEntity(EntityId id);

private:
    CameraManager &cameraManager_;
    const FrameHandler frameHandler_;
    const SheetManager &sheetManager_;
    EntityManager &entityManager_;
    SpawnManager spawnManager_;
};

}  // namespace Entity

}  // namespace FA
