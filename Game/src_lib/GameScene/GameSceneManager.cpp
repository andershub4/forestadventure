/*
 *	Copyright (C) 2021 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#include "GameSceneManager.h"

#include "GameScene/Scene/GameSceneIntro.h"
#include "Message/Message.h"
#include "Utils/Logger.h"

namespace FA {

GameSceneManager::GameSceneManager(MessageBus& messageBus, TextureManager& textureManager)
{
    currentScene_ = std::make_unique<GameSceneIntro>(*this, messageBus, textureManager, sceneComponents_, sceneData_);
    // LOG_INFO("Enter ", currentScene_->Name());
    currentScene_->Enter();
}

GameSceneManager::~GameSceneManager()
{
    // LOG_INFO("Exit ", currentScene_->Name());
    currentScene_->Exit();
}

void GameSceneManager::SetScene(std::unique_ptr<GameScene> newScene)
{
    // LOG_INFO("Exit ", currentScene_->Name());
    currentScene_->Exit();
    currentScene_ = std::move(newScene);
    // LOG_INFO("Enter ", currentScene_->Name());
    currentScene_->Enter();
}

void GameSceneManager::DrawTo(sf::RenderTarget& renderTarget)
{
    currentScene_->DrawTo(renderTarget);
}

void GameSceneManager::Update(float deltaTime)
{
    currentScene_->Update(deltaTime);
}

bool GameSceneManager::IsRunning() const
{
    return currentScene_->IsRunning();
}

void GameSceneManager::OnKeyPressed(std::shared_ptr<Message> message)
{
    currentScene_->OnKeyPressed(message);
}

void GameSceneManager::OnKeyReleased(std::shared_ptr<Message> message)
{
    currentScene_->OnKeyReleased(message);
}

void GameSceneManager::OnIsKeyPressed(std::shared_ptr<Message> message)
{
    currentScene_->OnIsKeyPressed(message);
}

void GameSceneManager::OnCloseWindow(std::shared_ptr<Message> message)
{
    currentScene_->OnCloseWindow(message);
}

}  // namespace FA
