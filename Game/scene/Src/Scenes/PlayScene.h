/*
 *	Copyright (C) 2021 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#pragma once

#include "BasicScene.h"

namespace FA {

namespace Scene {

class PlayScene : public BasicScene
{
public:
    PlayScene(Manager& sceneManager, Shared::MessageBus& messageBus, Shared::TextureManager& textureManager,
              Manager::Layers& layers, Manager::Data& data);
    virtual ~PlayScene();

    virtual void DrawTo(Graphic::IRenderTarget& renderTarget) override;
    virtual void Update(float deltaTime) override;
    virtual std::string Name() const override { return "PlayScene"; }

    virtual void Enter() override;
    virtual void Exit() override;

private:
    virtual void OnMessage(std::shared_ptr<Shared::Message> message) override;
};

}  // namespace Scene

}  // namespace FA
