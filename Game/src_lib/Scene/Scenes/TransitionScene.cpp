/*
 *	Copyright (C) 2021 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#include "TransitionScene.h"

#include "Constant/Screen.h"
#include "Scene/Components/HelperComponent.h"
#include "Scene/Transitions/BasicTransition.h"

namespace FA {

namespace Scene {

TransitionScene::TransitionScene(Manager& sceneManager, MessageBus& messageBus, TextureManager& textureManager,
                                 Manager::Components& components, Manager::Data& data,
                                 std::unique_ptr<BasicTransition> transition)
    : BasicScene(sceneManager, messageBus, textureManager, components, data)
    , transition_(std::move(transition))
{}

TransitionScene::~TransitionScene() = default;

void TransitionScene::Enter()
{
    sf::IntRect rect(0, 0, constant::Screen::width, constant::Screen::height);
#ifdef _DEBUG
    components_[ComponentId::Helper] = std::make_unique<HelperComponent>(messageBus_, rect, Name());
    components_[ComponentId::Helper]->OnCreate();
#endif
    for (const auto& entry : components_) {
        auto& component = entry.second;
        component->EnterTransition(*transition_);
        component->EnableInput(false);
    }
}

void TransitionScene::Exit()
{
    for (const auto& entry : components_) {
        auto& component = entry.second;
        component->ExitTransition(*transition_);
    }
}

void TransitionScene::DrawTo(sf::RenderTarget& renderTarget)
{
    for (const auto& entry : components_) {
        auto& component = entry.second;
        component->Clear();
        component->Draw();
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
