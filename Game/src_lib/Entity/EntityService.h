/*
 *	Copyright (C) 2021 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#pragma once

#include <functional>
#include <memory>
#include <unordered_map>
#include <vector>

#include "AttributeStore.h"
#include "Enum/EntityType.h"
#include "Enum/FaceDirection.h"
#include "Enum/FrameType.h"
#include "Logging.h"

namespace FA {

namespace Keyboard {
enum class Key;
}

class CameraManager;
class AnimationDb;
class Animation;

namespace Entity {

struct BasicEvent;
class CameraAttribute;
class Shape;

class EntityService
{
public:
    EntityService(EntityType entityType, CameraManager &cameraManager, const AnimationDb &animationDb);
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

    Animation GetAnimation(FrameType frameType, FaceDirection faceDir) const;
    std::vector<FrameType> GetFrameTypes() const { return frameTypes_; }
    std::shared_ptr<Shape> GetShape() const { return shape_; }
    void AddFrameType(FrameType frameType);
    void AddInputIsKeyPressed(Keyboard::Key key, std::function<std::shared_ptr<BasicEvent>()> func);
    void AddInputIsKeyReleased(Keyboard::Key key, std::function<std::shared_ptr<BasicEvent>()> func);
    void AddInputKeyPressed(Keyboard::Key key, std::function<std::shared_ptr<BasicEvent>()> func);
    std::shared_ptr<BasicEvent> HandleIsKeyPressed(Keyboard::Key key);
    std::shared_ptr<BasicEvent> HandleIsKeyReleased(Keyboard::Key key);
    std::shared_ptr<BasicEvent> HandleKeyPressed(Keyboard::Key key);

private:
    AttributeStore attributeStore_;
    std::vector<FrameType> frameTypes_;
    CameraManager &cameraManager_;
    EntityType entityType_;
    const AnimationDb &animationDb_;
    std::shared_ptr<Shape> shape_ = nullptr;
    std::unordered_map<Keyboard::Key, std::function<std::shared_ptr<BasicEvent>()>> isKeyPressedMap_;
    std::unordered_map<Keyboard::Key, std::function<std::shared_ptr<BasicEvent>()>> isKeyReleasedMap_;
    std::unordered_map<Keyboard::Key, std::function<std::shared_ptr<BasicEvent>()>> keyPressedMap_;
};

}  // namespace Entity

}  // namespace FA
