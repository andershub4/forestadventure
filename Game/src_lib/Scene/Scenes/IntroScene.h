/*
 *	Copyright (C) 2021 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#pragma once

#include "BasicScene.h"

namespace FA {

namespace Scene {

class IntroScene : public BasicScene
{
public:
    IntroScene(Manager& sceneManager, MessageBus& messageBus, TextureManager& textureManager,
               Manager::Layers& components, Manager::Data& data);
    virtual ~IntroScene();

    virtual void DrawTo(sf::RenderTarget& renderTarget) override;
    virtual void Update(float deltaTime) override;
    virtual std::string Name() const override { return "IntroScene"; }

    virtual void OnKeyPressed(Keyboard::Key key) override;
    virtual void Enter() override;
    virtual void Exit() override;
};

}  // namespace Scene

}  // namespace FA
