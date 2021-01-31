/*
 *	Copyright (C) 2021 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#include "GameSceneTransition.h"

#include <algorithm>

#include "GameScene/Transition/GameTransition.h"
#include "SceneComponent/SceneComponent.h"

namespace FA {

GameSceneTransition::GameSceneTransition(GameSceneManager& sceneManager, MessageBus& messageBus,
                                         TextureManager& textureManager,
                                         GameSceneManager::SceneComponents& sceneComponents,
                                         GameSceneManager::SceneData& sceneData,
                                         std::unique_ptr<GameTransition> transition,
                                         const std::vector<SceneComponentId>& ids)
    : GameScene(sceneManager, messageBus, textureManager, sceneComponents, sceneData)
    , transition_(std::move(transition))
    , ids_(ids)
{}

GameSceneTransition::~GameSceneTransition() = default;

void GameSceneTransition::Enter()
{
    for (const auto& entry : sceneComponents_) {
        auto& component = entry.second;
        component->ProcessMessages(false);
    }
}

void GameSceneTransition::DrawTo(sf::RenderTarget& renderTarget)
{
    for (const auto& entry : sceneComponents_) {
        auto& component = entry.second;
        component->Clear();
        component->Draw();
        if (std::find(ids_.begin(), ids_.end(), component->GetId()) != ids_.end()) {
            transition_->DrawTo(*component);
        }

        component->DrawTo(renderTarget);
    }
}

void GameSceneTransition::Update(float deltaTime)
{
    transition_->Update(deltaTime);

    if (transition_->IsFinished()) {
        SwitchScene(transition_->CreateNextScene(messageBus_, textureManager_));
        return;
    }

    for (const auto& entry : sceneComponents_) {
        auto& component = entry.second;
        component->Update(deltaTime);
    }
}

}  // namespace FA
