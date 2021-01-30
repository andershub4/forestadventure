/*
 *	Copyright (C) 2021 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#include "GameScene.h"

namespace FA {

GameScene::GameScene(GameSceneManager &sceneManager, MessageBus &messageBus, TextureManager &textureManager,
                     GameSceneManager::SceneComponents &sceneComponents, GameSceneManager::SceneData &sceneData)
    : sceneManager_(sceneManager)
    , messageBus_(messageBus)
    , textureManager_(textureManager)
    , sceneComponents_(sceneComponents)
    , sceneData_(sceneData)
{}

GameScene::~GameScene() = default;

// TODO: Consider to request for sceneSwitch here, and do actual switch after Update().
// Then Update() can continue to execute code after the request is made.
void GameScene::SwitchScene(std::unique_ptr<GameScene> newScene)
{
    sceneManager_.SetScene(std::move(newScene));
}

void GameScene::OnCloseWindow(std::shared_ptr<Message> message)
{
    sceneData_.isRunning_ = false;
}

bool GameScene::IsRunning() const
{
    return sceneData_.isRunning_;
}

}  // namespace FA
