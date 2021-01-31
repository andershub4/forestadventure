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
    PlayScene(Manager& sceneManager, MessageBus& messageBus, TextureManager& textureManager,
              Manager::Components& components, Manager::Data& data);
    virtual ~PlayScene();

    virtual void DrawTo(sf::RenderTarget& renderTarget) override;
    virtual void Update(float deltaTime) override;
    virtual std::string Name() const override { return "PlayScene"; }

    virtual void OnKeyPressed(std::shared_ptr<Message> message) override;
    virtual void Enter() override;
};

}  // namespace Scene

}  // namespace FA