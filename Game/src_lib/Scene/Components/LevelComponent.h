/*
 *	Copyright (C) 2021 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#pragma once

#include <memory>

#include "BasicComponent.h"
#include "Level/Level.h"

namespace FA {

class TextureManager;
class BasicEffect;

namespace Scene {

class LevelComponent : public BasicComponent
{
public:
    LevelComponent(MessageBus& messageBus, const Layer& layer, TextureManager& textureManager);
    virtual ~LevelComponent();

    virtual ComponentId GetId() const override { return ComponentId::Level; }
    virtual void Update(float deltaTime) override;
    virtual void Draw() override;
    virtual void EnableInput(bool enable) override;
    virtual void EnterTransition(const BasicTransition& transition) override;
    virtual void ExitTransition(const BasicTransition& transition) override;
    virtual void OnCreate() override;

private:
    Level level_;
    std::unique_ptr<BasicEffect> effect_ = nullptr;
};

}  // namespace Scene

}  // namespace FA
