/*
 *	Copyright (C) 2021 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#include "GameSceneIntro.h"

#include <SFML/Graphics/RenderWindow.hpp>

#include "GameScenePlay.h"
#include "Message/BroadcastMessage/KeyPressedMessage.h"
#include "SceneComponent/SceneComponentHelper.h"
#include "SceneComponent/SceneComponentIntro.h"

namespace FA {

GameSceneIntro::GameSceneIntro(GameSceneManager& sceneManager, MessageBus& messageBus, TextureManager& textureManager,
                               SceneComponents& sceneComponents, SceneData& sceneData)
    : GameScene(sceneManager, messageBus, textureManager, sceneComponents, sceneData)
{}

GameSceneIntro::~GameSceneIntro() = default;

void GameSceneIntro::Enter()
{
    sceneComponents_.clear();
    sceneComponents_[SceneComponentId::Intro] = std::make_unique<SceneComponentIntro>(messageBus_);
#ifdef _DEBUG
    sceneComponents_[SceneComponentId::Helper] = std::make_unique<SceneComponentHelper>(messageBus_, Name());
#endif
}

void GameSceneIntro::DrawTo(sf::RenderTarget& renderTarget)
{
    for (const auto& component : sceneComponents_) {
        component.second->DrawTo(renderTarget);
    }
}

void GameSceneIntro::Update(float deltaTime)
{
    for (const auto& component : sceneComponents_) {
        component.second->Update(deltaTime);
    }
}

void GameSceneIntro::OnKeyPressed(std::shared_ptr<Message> message)
{
    auto m = std::dynamic_pointer_cast<KeyPressedMessage>(message);
    auto key = m->GetKey();
    if (key == Keyboard::Key::Escape) {
        sceneData_.isRunning_ = false;
    }
    else if (key == Keyboard::Key::Return) {
        SwitchScene<GameScenePlay>();
    }
}

}  // namespace FA
