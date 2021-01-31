/*
 *	Copyright (C) 2021 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#pragma once

#include <memory>

#include "Animation/AnimationFactory.h"
#include "SceneComponent.h"

namespace FA {

namespace Entity {

class BasicEntity;

}

class TextureManager;

class SceneComponentLevel : public SceneComponent
{
public:
    SceneComponentLevel(MessageBus& messageBus, TextureManager& textureManager);
    virtual ~SceneComponentLevel();

    virtual SceneComponentId GetId() const override { return SceneComponentId::Level; }
    virtual void Update(float deltaTime) override;
    virtual void Draw() override;
    virtual void ProcessMessages(bool process) override;

private:
    AnimationFactory animationFactory_;
    std::unique_ptr<Entity::BasicEntity> entity_;

private:
    void RegisterAnimationInfo(TextureManager& textureManager);
};

}  // namespace FA
