/*
 *	Copyright (C) 2021 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#pragma once

#include "BasicScene.h"

namespace FA {

namespace Scene {

class BasicTransition;

class TransitionScene : public BasicScene
{
public:
    TransitionScene(Manager& sceneManager, Shared::MessageBus& messageBus, Shared::TextureManager& textureManager,
                    Manager::Layers& layers, Manager::Data& Data, std::unique_ptr<BasicTransition> transition);
    virtual ~TransitionScene();

    virtual void DrawTo(Graphic::RenderTargetIf& renderTarget) override;
    virtual void Update(float deltaTime) override;
    virtual std::string Name() const override { return "TransitionScene"; }

    virtual void Enter() override;
    virtual void Exit() override;

private:
    std::unique_ptr<BasicTransition> transition_ = nullptr;
};

}  // namespace Scene

}  // namespace FA
