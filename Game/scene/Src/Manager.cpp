/*
 *	Copyright (C) 2021 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#include "Manager.h"

#include "Logging.h"
#include "Scenes/IntroScene.h"
#include "Scenes/TransitionScene.h"

namespace FA {

namespace Scene {

Manager::Manager(Shared::MessageBus& messageBus, Shared::TextureManager& textureManager)
{
    currentScene_ = std::make_unique<IntroScene>(*this, messageBus, textureManager, layers_, data_);
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

void Manager::SetTransitionScene(Shared::MessageBus& messageBus, Shared::TextureManager& textureManager,
                                 std::unique_ptr<BasicTransition> transition)
{
    SetScene(
        std::make_unique<TransitionScene>(*this, messageBus, textureManager, layers_, data_, std::move(transition)));
}

void Manager::DrawTo(Graphic::IRenderTarget& renderTarget)
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

}  // namespace Scene

}  // namespace FA
