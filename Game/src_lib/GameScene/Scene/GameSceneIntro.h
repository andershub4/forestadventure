/*
 *	Copyright (C) 2021 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#pragma once

#include "GameScene.h"

namespace FA {

class GameSceneIntro : public GameScene
{
public:
    GameSceneIntro(GameSceneManager& sceneManager, MessageBus& messageBus, TextureManager& textureManager,
                   GameSceneManager::SceneComponents& sceneComponents, GameSceneManager::SceneData& sceneData);
    virtual ~GameSceneIntro();

    virtual void DrawTo(sf::RenderTarget& renderTarget) override;
    virtual void Update(float deltaTime) override;
    virtual std::string Name() const override { return "GameSceneIntro"; }

    virtual void OnKeyPressed(std::shared_ptr<Message> message) override;
    virtual void Enter() override;
};

}  // namespace FA
