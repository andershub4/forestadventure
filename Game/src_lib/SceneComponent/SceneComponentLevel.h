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

class TextureManager;
class Entity;

class SceneComponentLevel : public SceneComponent
{
public:
    SceneComponentLevel(MessageBus& messageBus, TextureManager& textureManager);
    virtual ~SceneComponentLevel();

    virtual void Update(float deltaTime) override;
    virtual void DrawTo(sf::RenderTarget& renderTarget) override;

private:
    AnimationFactory animationFactory_;
    std::unique_ptr<Entity> entity_;

private:
    void RegisterAnimationInfo(TextureManager& textureManager);
};

}  // namespace FA
