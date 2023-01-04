/*
 *	Copyright (C) 2021 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#include "TransitionScene.h"

#include "Constant/Screen.h"
#include "Layers/HelperLayer.h"
#include "Transitions/BasicTransition.h"

namespace FA {

namespace Scene {

TransitionScene::TransitionScene(Manager& sceneManager, MessageBus& messageBus, TextureManager& textureManager,
                                 Manager::Layers& layers, Manager::Data& data,
                                 std::unique_ptr<BasicTransition> transition)
    : BasicScene(sceneManager, messageBus, textureManager, layers, data)
    , transition_(std::move(transition))
{}

TransitionScene::~TransitionScene() = default;

void TransitionScene::Enter()
{
    sf::IntRect rect(0, 0, constant::Screen::width, constant::Screen::height);
#ifdef _DEBUG
    layers_[LayerId::Helper] = std::make_unique<HelperLayer>(messageBus_, rect, Name());
    layers_[LayerId::Helper]->OnLoad();
    layers_[LayerId::Helper]->OnCreate();
#endif
    for (const auto& entry : layers_) {
        auto& layer = entry.second;
        layer->EnterTransition(*transition_);
        layer->EnableInput(false);
    }
}

void TransitionScene::Exit()
{
    for (const auto& entry : layers_) {
        auto& layer = entry.second;
        layer->ExitTransition(*transition_);
    }
}

void TransitionScene::DrawTo(sf::RenderTarget& renderTarget)
{
    for (const auto& entry : layers_) {
        auto& layer = entry.second;
        layer->Clear();
        layer->Draw();
        layer->DrawTo(renderTarget);
    }
}

void TransitionScene::Update(float deltaTime)
{
    transition_->Update(deltaTime);

    if (transition_->IsFinished()) {
        SwitchScene(transition_->CreateNextScene(messageBus_, textureManager_));
        return;
    }

    for (const auto& entry : layers_) {
        auto& layer = entry.second;
        layer->Update(deltaTime);
    }
}

}  // namespace Scene

}  // namespace FA
