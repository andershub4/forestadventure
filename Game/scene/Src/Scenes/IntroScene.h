/*
 *	Copyright (C) 2021 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#pragma once

#include "BasicScene.h"

namespace FA {

namespace Graphic {

class IRenderTarget;

}  // namespace Graphic

namespace Scene {

class IntroScene : public BasicScene
{
public:
    IntroScene(Manager& sceneManager, Shared::MessageBus& messageBus, Shared::TextureManager& textureManager,
               Manager::Layers& components, Manager::Data& data);
    virtual ~IntroScene();

    virtual void DrawTo(Graphic::IRenderTarget& renderTarget) override;
    virtual void Update(float deltaTime) override;
    virtual std::string Name() const override { return "IntroScene"; }

    virtual void Enter() override;
    virtual void Exit() override;

private:
    virtual void OnMessage(std::shared_ptr<Shared::Message> message) override;
};

}  // namespace Scene

}  // namespace FA
