/*
 *	Copyright (C) 2021 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#include "PlayScene.h"

#include <SFML/Graphics/RenderWindow.hpp>

#include "IntroScene.h"
#include "Message/BroadcastMessage/KeyPressedMessage.h"
#include "Scene/Components/HelperComponent.h"
#include "Scene/Components/LevelComponent.h"
#include "Scene/Components/PreAlphaComponent.h"
#include "Scene/Transitions/FadeTransition.h"

namespace FA {

namespace Scene {

PlayScene::PlayScene(Manager& sceneManager, MessageBus& messageBus, TextureManager& textureManager,
                     Manager::Components& components, Manager::Data& data)
    : BasicScene(sceneManager, messageBus, textureManager, components, data)
{}

PlayScene::~PlayScene() = default;

void PlayScene::Enter()
{
    components_.clear();
    components_[ComponentId::Level] = std::make_unique<LevelComponent>(messageBus_, textureManager_);
#ifdef _DEBUG
    components_[ComponentId::Helper] = std::make_unique<HelperComponent>(messageBus_, Name());
#endif
    components_[ComponentId::PreAlpha] = std::make_unique<PreAlphaComponent>(messageBus_);
}

void PlayScene::DrawTo(sf::RenderTarget& renderTarget)
{
    for (const auto& entry : components_) {
        auto& component = entry.second;
        component->Clear();
        component->Draw();
        component->DrawTo(renderTarget);
    }
}

void PlayScene::Update(float deltaTime)
{
    for (const auto& entry : components_) {
        auto& component = entry.second;
        component->Update(deltaTime);
    }
}

void PlayScene::OnKeyPressed(std::shared_ptr<Message> message)
{
    auto m = std::dynamic_pointer_cast<KeyPressedMessage>(message);
    auto key = m->GetKey();
    if (key == Keyboard::Key::Escape) {
        data_.isRunning_ = false;
    }
    else if (key == Keyboard::Key::Return) {
        // TODO: If player press Return, while pressing an arrow key, Transition scene is shown.
        // However, player is still moving (and input is disabled).
        SwitchScene<IntroScene, FadeTransition>();
    }
}

}  // namespace Scene

}  // namespace FA
