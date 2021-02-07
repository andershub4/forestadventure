/*
 *	Copyright (C) 2021 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#include "Manager.h"

#include "Message/Message.h"
#include "Scenes/IntroScene.h"
#include "Scenes/TransitionScene.h"
#include "Utils/Logger.h"

namespace FA {

namespace Scene {

Manager::Manager(MessageBus& messageBus, TextureManager& textureManager)
{
    currentScene_ = std::make_unique<IntroScene>(*this, messageBus, textureManager, components_, data_);
    // LOG_INFO("Enter ", currentScene_->Name());
    currentScene_->Enter();
}

Manager::~Manager()
{
    // LOG_INFO("Exit ", currentScene_->Name());
    currentScene_->Exit();
}

void Manager::SetScene(std::unique_ptr<BasicScene> newScene)
{
    // LOG_INFO("Exit ", currentScene_->Name());
    currentScene_->Exit();
    currentScene_ = std::move(newScene);
    // LOG_INFO("Enter ", currentScene_->Name());
    currentScene_->Enter();
}

void Manager::SetTransitionScene(MessageBus& messageBus, TextureManager& textureManager,
                                 std::unique_ptr<BasicTransition> transition)
{
    SetScene(std::make_unique<TransitionScene>(*this, messageBus, textureManager, components_, data_,
                                               std::move(transition)));
}

void Manager::DrawTo(sf::RenderTarget& renderTarget)
{
    currentScene_->DrawTo(renderTarget);
}

void Manager::Update(float deltaTime)
{
    currentScene_->Update(deltaTime);
}

bool Manager::IsRunning() const
{
    return currentScene_->IsRunning();
}

void Manager::OnKeyPressed(std::shared_ptr<Message> message)
{
    currentScene_->OnKeyPressed(message);
}

void Manager::OnKeyReleased(std::shared_ptr<Message> message)
{
    currentScene_->OnKeyReleased(message);
}

void Manager::OnIsKeyPressed(std::shared_ptr<Message> message)
{
    currentScene_->OnIsKeyPressed(message);
}

void Manager::OnCloseWindow(std::shared_ptr<Message> message)
{
    currentScene_->OnCloseWindow(message);
}

}  // namespace Scene

}  // namespace FA
