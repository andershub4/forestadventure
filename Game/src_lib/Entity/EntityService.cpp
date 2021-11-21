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
    return attributeStore_.AddAttribute<CameraAttribute>(this);
}

Animation EntityService::GetAnimation(FrameType frameType, FaceDirection faceDir) const
{
    return animationDb_.GetAnimation(entityType_, frameType, faceDir);
}

void EntityService::AddFrameType(FrameType frameType)
{
    frameTypes_.push_back(frameType);
}

void EntityService::AddInputIsKeyPressed(Keyboard::Key key, std::function<std::shared_ptr<BasicEvent>()> func)
{
    isKeyPressedMap_[key] = func;
}

void EntityService::AddInputIsKeyReleased(Keyboard::Key key, std::function<std::shared_ptr<BasicEvent>()> func)
{
    isKeyReleasedMap_[key] = func;
}

void EntityService::AddInputKeyPressed(Keyboard::Key key, std::function<std::shared_ptr<BasicEvent>()> func)
{
    keyPressedMap_[key] = func;
}

std::shared_ptr<BasicEvent> EntityService::HandleIsKeyPressed(Keyboard::Key key)
{
    auto it = isKeyPressedMap_.find(key);
    if (it != isKeyPressedMap_.end()) {
        return isKeyPressedMap_[key]();
    }

    return nullptr;
}

std::shared_ptr<BasicEvent> EntityService::HandleIsKeyReleased(Keyboard::Key key)
{
    auto it = isKeyReleasedMap_.find(key);
    if (it != isKeyReleasedMap_.end()) {
        return isKeyReleasedMap_[key]();
    }

    return nullptr;
}

std::shared_ptr<BasicEvent> EntityService::HandleKeyPressed(Keyboard::Key key)
{
    auto it = keyPressedMap_.find(key);
    if (it != keyPressedMap_.end()) {
        return keyPressedMap_[key]();
    }

    return nullptr;
}

}  // namespace Entity

}  // namespace FA
