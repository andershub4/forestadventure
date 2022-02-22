/*
 *	Copyright (C) 2021 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#include "IntroScene.h"

#include <SFML/Graphics/RenderWindow.hpp>

#include "Constant/Screen.h"
#include "Message/BroadcastMessage/KeyPressedMessage.h"
#include "PlayScene.h"
#include "Scene/Components/HelperComponent.h"
#include "Scene/Components/IntroComponent.h"
#include "Scene/Components/PreAlphaComponent.h"

namespace FA {

namespace Scene {

IntroScene::IntroScene(Manager& sceneManager, MessageBus& messageBus, TextureManager& textureManager,
                       Manager::Components& components, Manager::Data& data)
    : BasicScene(sceneManager, messageBus, textureManager, components, data)
{}

IntroScene::~IntroScene() = default;

void IntroScene::Enter()
{
    //    Layer layer{0.0f, 0.0f, constant::Screen::width, constant::Screen::height};
    sf::IntRect rect(0, 0, constant::Screen::width, constant::Screen::height);
    components_.clear();
    components_[ComponentId::Intro] = std::make_unique<IntroComponent>(messageBus_, rect);
#ifdef _DEBUG
    components_[ComponentId::Helper] = std::make_unique<HelperComponent>(messageBus_, rect, Name());
#endif
    components_[ComponentId::PreAlpha] = std::make_unique<PreAlphaComponent>(messageBus_, rect);

    for (const auto& entry : components_) {
        auto& component = entry.second;
        component->OnCreate();
    }
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
