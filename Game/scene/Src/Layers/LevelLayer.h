/*
 *	Copyright (C) 2021 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#pragma once

#include <memory>

#include "BasicLayer.h"

#include "Resource/TextureManager.h"

namespace FA {

namespace Shared {

class MessageBus;

}  // namespace Shared

namespace World {

class Level;

}  // namespace World

namespace Scene {

class LevelLayer : public BasicLayer
{
public:
    LevelLayer(Shared::MessageBus& messageBus, const sf::IntRect& rect, Shared::TextureManager& textureManager);
    virtual ~LevelLayer();

    virtual std::string Name() const override { return "Level"; }
    virtual LayerId GetId() const override { return LayerId::Level; }
    virtual void Update(float deltaTime) override;
    virtual void Draw() override;
    virtual void EnableInput(bool enable) override {}
    virtual void EnterTransition(BasicTransition& transition) override;
    virtual void DrawTransition(const BasicTransition& transition) override;
    virtual void OnLoad() override;
    virtual void OnCreate() override;

private:
    Shared::MessageBus& messageBus_;
    std::unique_ptr<World::Level> level_ = nullptr;
    Shared::TextureManager& textureManager_;
};

}  // namespace Scene

}  // namespace FA
