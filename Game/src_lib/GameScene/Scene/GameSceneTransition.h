/*
 *	Copyright (C) 2021 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#pragma once

#include <vector>

#include "GameScene.h"

namespace FA {

class GameTransition;

class GameSceneTransition : public GameScene
{
public:
    GameSceneTransition(GameSceneManager& sceneManager, MessageBus& messageBus, TextureManager& textureManager,
                        GameSceneManager::SceneComponents& sceneComponents, GameSceneManager::SceneData& sceneData,
                        std::unique_ptr<GameTransition> transition, const std::vector<SceneComponentId>& ids);
    virtual ~GameSceneTransition();

    virtual void DrawTo(sf::RenderTarget& renderTarget) override;
    virtual void Update(float deltaTime) override;
    virtual std::string Name() const override { return "GameSceneTransition"; }

    virtual void Enter() override;

private:
    std::unique_ptr<GameTransition> transition_ = nullptr;
    std::vector<SceneComponentId> ids_;
};

}  // namespace FA
