/*
 *	Copyright (C) 2021 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#pragma once

#include "GameScene/Scene/GameScene.h"

namespace FA {

class GameSceneManager
{
public:
    GameSceneManager(MessageBus& messageBus, TextureManager& textureManager);
    ~GameSceneManager();

    void SetScene(std::unique_ptr<GameScene> newScene);

    void DrawTo(sf::RenderTarget& renderTarget);
    void Update(float deltaTime);

    bool IsRunning() const;

    void OnKeyPressed(std::shared_ptr<Message> message);
    void OnKeyReleased(std::shared_ptr<Message> message);
    void OnIsKeyPressed(std::shared_ptr<Message> message);
    void OnCloseWindow(std::shared_ptr<Message> message);

private:
    std::unique_ptr<GameScene> currentScene_;
    GameScene::SceneData sceneData_;
    GameScene::SceneComponents sceneComponents_;
};

}  // namespace FA
