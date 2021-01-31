/*
 *	Copyright (C) 2021 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#pragma once

#include <vector>

#include "BasicScene.h"

namespace FA {

namespace Scene {

class BasicTransition;

class TransitionScene : public BasicScene
{
public:
    TransitionScene(Manager& sceneManager, MessageBus& messageBus, TextureManager& textureManager,
                    Manager::Components& components, Manager::Data& Data, std::unique_ptr<BasicTransition> transition,
                    const std::vector<SceneComponentId>& ids);
    virtual ~TransitionScene();

    virtual void DrawTo(sf::RenderTarget& renderTarget) override;
    virtual void Update(float deltaTime) override;
    virtual std::string Name() const override { return "TransitionScene"; }

    virtual void Enter() override;

private:
    std::unique_ptr<BasicTransition> transition_ = nullptr;
    std::vector<SceneComponentId> ids_;
};

}  // namespace Scene

}  // namespace FA
