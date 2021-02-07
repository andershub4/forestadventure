/*
 *	Copyright (C) 2021 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#include "IntroScene.h"

#include <SFML/Graphics/RenderWindow.hpp>

#include "Message/BroadcastMessage/KeyPressedMessage.h"
#include "PlayScene.h"
#include "Scene/Components/HelperComponent.h"
#include "Scene/Components/IntroComponent.h"

namespace FA {

namespace Scene {

IntroScene::IntroScene(Manager& sceneManager, MessageBus& messageBus, TextureManager& textureManager,
                       Manager::Components& components, Manager::Data& data)
    : BasicScene(sceneManager, messageBus, textureManager, components, data)
{}

IntroScene::~IntroScene() = default;

void IntroScene::Enter()
{
    components_.clear();
    components_[ComponentId::Intro] = std::make_unique<IntroComponent>(messageBus_);
#ifdef _DEBUG
    components_[ComponentId::Helper] = std::make_unique<HelperComponent>(messageBus_, Name());
#endif
}

void IntroScene::DrawTo(sf::RenderTarget& renderTarget)
{
    for (const auto& entry : components_) {
        auto& component = entry.second;
        component->Clear();
        component->Draw();
        component->DrawTo(renderTarget);
    }
}

void IntroScene::Update(float deltaTime)
{
    for (const auto& entry : components_) {
        auto& component = entry.second;
        component->Update(deltaTime);
    }
}

void IntroScene::OnKeyPressed(std::shared_ptr<Message> message)
{
    auto m = std::dynamic_pointer_cast<KeyPressedMessage>(message);
    auto key = m->GetKey();
    if (key == Keyboard::Key::Escape) {
        data_.isRunning_ = false;
    }
    else if (key == Keyboard::Key::Return) {
        SwitchScene<PlayScene>();
    }
}

}  // namespace Scene

}  // namespace FA
