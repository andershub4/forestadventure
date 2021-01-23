/*
 *	Copyright (C) 2021 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#pragma once

#include <memory>

#include "Animation/AnimationFactory.h"
#include "Entity/Entity.h"

namespace FA {

class MessageBus;
class TextureManager;
class Layer;

class Level
{
public:
    Level(MessageBus& messageBus, TextureManager& textureManager);
    virtual ~Level();

    void Update(float deltaTime);
    void DrawTo(Layer& layer);

private:
    MessageBus& messageBus_;
    AnimationFactory animationFactory_;
    std::unique_ptr<Entity> entity_;

private:
    void RegisterAnimationInfo(TextureManager& textureManager);
};

}  // namespace FA
