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
#include "PropertyManager.h"
#include "Resource/FrameHandler.h"
#include "SpawnManager.h"

namespace FA {

class CameraManager;
class Animation;
class Image;
class SheetManager;

namespace Entity {

class Shape;
class EntityManager;

class EntityService
{
public:
    EntityService(CameraManager &cameraManager, const SheetManager &sheetManager, EntityManager &entityManager);
    ~EntityService();

    void AddCamera();

    void ReadObjectData(const sf::Vector2f &position);
    void ReadCustomProperty(const std::string &name, const std::string &valueStr);
    void InitOtherData(float scale);

    template <class T>
    void RegisterProperty(const std::string &name, const T &value)
    {
        propertyManager_.Register<T>(name, value);
    }

    template <class T>
    T GetProperty(const std::string &name) const
    {
        return propertyManager_.Get<T>(name);
    }

    template <class T>
    void SetProperty(const std::string &name, const T &value)
    {
        propertyManager_.Set<T>(name, value);
    }

    sf::Vector2u GetMapSize() const;

    Animation MakeAnimation(const AnimationData &data) const;
    Image MakeImage(const ImageData &data) const;

    std::shared_ptr<Shape> GetShape() const { return shape_; }

    void SpawnEntity(EntityType entityType, FaceDirection faceDirection, const sf::Vector2f &position, float scale);
    void DeleteEntity(EntityId id);

private:
    CameraManager &cameraManager_;
    const FrameHandler frameHandler_;
    const SheetManager &sheetManager_;
    std::shared_ptr<Shape> shape_ = nullptr;
    EntityManager &entityManager_;
    SpawnManager spawnManager_;
    PropertyManager propertyManager_;
};

}  // namespace Entity

}  // namespace FA
