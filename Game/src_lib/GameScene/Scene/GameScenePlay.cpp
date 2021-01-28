/*
 *	Copyright (C) 2021 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#include "GameScenePlay.h"

#include <SFML/Graphics/RenderWindow.hpp>

#include "GameScene/Scene/GameSceneIntro.h"
#include "Message/BroadcastMessage/KeyPressedMessage.h"
#include "SceneComponent/SceneComponentHelper.h"
#include "SceneComponent/SceneComponentLevel.h"

namespace FA {

GameScenePlay::GameScenePlay(GameSceneManager& sceneManager, MessageBus& messageBus, TextureManager& textureManager,
                             SceneComponents& sceneComponents, SceneData& sceneData)
    : GameScene(sceneManager, messageBus, textureManager, sceneComponents, sceneData)
{}

GameScenePlay::~GameScenePlay() = default;

void GameScenePlay::Enter()
{
    sceneComponents_.clear();
    sceneComponents_[SceneComponentId::Level] = std::make_unique<SceneComponentLevel>(messageBus_, textureManager_);
#ifdef _DEBUG
    sceneComponents_[SceneComponentId::Helper] = std::make_unique<SceneComponentHelper>(messageBus_, Name());
#endif
}

void GameScenePlay::DrawTo(sf::RenderTarget& renderTarget)
{
    for (const auto& component : sceneComponents_) {
        component.second->DrawTo(renderTarget);
    }
}

void GameScenePlay::Update(float deltaTime)
{
    for (const auto& component : sceneComponents_) {
        component.second->Update(deltaTime);
    }
}

void GameScenePlay::OnKeyPressed(std::shared_ptr<Message> message)
{
    auto m = std::dynamic_pointer_cast<KeyPressedMessage>(message);
    auto key = m->GetKey();
    if (key == Keyboard::Key::Escape) {
        sceneData_.isRunning_ = false;
    }
    else if (key == Keyboard::Key::Return) {
        SwitchScene<GameSceneIntro>();
    }
}

}  // namespace FA
