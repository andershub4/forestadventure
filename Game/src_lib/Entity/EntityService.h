/*
 *	Copyright (C) 2021 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#pragma once

#include <memory>

#include "AttributeStore.h"
#include "Enum/FaceDirection.h"
#include "Id.h"
#include "Logging.h"
#include "Resource/AnimationDb.h"
#include "Resource/ImageDb.h"
#include "SpawnManager.h"

namespace FA {

class CameraManager;
class Animation;
class SheetManager;

namespace Entity {

class CameraAttribute;
class Shape;
class EntityManager;

class EntityService
{
public:
    EntityService(CameraManager &cameraManager, const SheetManager &sheetManager, EntityManager &entityManager);
    ~EntityService();

    template <class T>
    std::shared_ptr<T> AddAttribute()
    {
        return attributeStore_.AddAttribute<T>(this);
    }

    template <class T>
    std::shared_ptr<T> GetAttribute()
    {
        if (attributeStore_.HasAttribute<T>()) {
            return attributeStore_.GetAttribute<T>();
        }
        else {
            LOG_ERROR(typeid(T).name(), " is not in attributeStore");
            return AddAttribute<T>();
        }
    }

    template <>
    std::shared_ptr<CameraAttribute> AddAttribute<CameraAttribute>();

    sf::Vector2u GetMapSize() const;

    void AddAnimation(const AnimationData &data);
    Animation GetAnimation(const std::string &k) const;

    void AddImage(const ImageData &data);
    Image GetImage(const std::string &k) const;

    std::shared_ptr<Shape> GetShape() const { return shape_; }

    void SpawnEntity(EntityType entityType, FaceDirection faceDirection, const sf::Vector2f &position, float scale,
                     float velocity);
    void DeleteEntity(EntityId id);

private:
    AttributeStore attributeStore_;
    CameraManager &cameraManager_;
    AnimationDb animationDb_;
    ImageDb imageDb_;
    std::shared_ptr<Shape> shape_ = nullptr;
    EntityManager &entityManager_;
    SpawnManager spawnManager_;
};

}  // namespace Entity

}  // namespace FA
