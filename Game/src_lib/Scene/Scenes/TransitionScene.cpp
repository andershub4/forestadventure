/*
 *	Copyright (C) 2021 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#include "TransitionScene.h"

#include <algorithm>

#include "Scene/Components/BasicComponent.h"
#include "Scene/Transitions/BasicTransition.h"

namespace FA {

namespace Scene {

TransitionScene::TransitionScene(Manager& sceneManager, MessageBus& messageBus, TextureManager& textureManager,
                                 Manager::Components& components, Manager::Data& data,
                                 std::unique_ptr<BasicTransition> transition, const std::vector<SceneComponentId>& ids)
    : BasicScene(sceneManager, messageBus, textureManager, components, data)
    , transition_(std::move(transition))
    , ids_(ids)
{}

TransitionScene::~TransitionScene() = default;

void TransitionScene::Enter()
{
    for (const auto& entry : components_) {
        auto& component = entry.second;
        component->ProcessMessages(false);
    }
}

void TransitionScene::DrawTo(sf::RenderTarget& renderTarget)
{
    for (const auto& entry : components_) {
        auto& component = entry.second;
        component->Clear();
        component->Draw();
        if (std::find(ids_.begin(), ids_.end(), component->GetId()) != ids_.end()) {
            transition_->DrawTo(*component);
        }

        component->DrawTo(renderTarget);
    }
}

void TransitionScene::Update(float deltaTime)
{
    transition_->Update(deltaTime);

    if (transition_->IsFinished()) {
        SwitchScene(transition_->CreateNextScene(messageBus_, textureManager_));
        return;
    }

    for (const auto& entry : components_) {
        auto& component = entry.second;
        component->Update(deltaTime);
    }
}

}  // namespace Scene

}  // namespace FA
