/*
 *	Copyright (C) 2021 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#include "IntroScene.h"

#include <SFML/Graphics/RenderWindow.hpp>

#include "Layers/HelperLayer.h"
#include "Layers/IntroLayer.h"
#include "Layers/PreAlphaLayer.h"
#include "Message/BroadcastMessage/CloseWindowMessage.h"
#include "Message/BroadcastMessage/KeyPressedMessage.h"
#include "PlayScene.h"
#include "Screen.h"

namespace FA {

namespace Scene {

IntroScene::IntroScene(Manager& sceneManager, Shared::MessageBus& messageBus, Shared::TextureManager& textureManager,
                       Manager::Layers& layers, Manager::Data& data)
    : BasicScene(sceneManager, messageBus, textureManager, layers, data)
{}

IntroScene::~IntroScene() = default;

void IntroScene::Enter()
{
    sf::IntRect rect(0, 0, Shared::Screen::width, Shared::Screen::height);
    layers_.clear();
    layers_[LayerId::Intro] = std::make_unique<IntroLayer>(messageBus_, rect);
#ifdef _DEBUG
    layers_[LayerId::Helper] = std::make_unique<HelperLayer>(messageBus_, rect, Name());
#endif
    layers_[LayerId::PreAlpha] = std::make_unique<PreAlphaLayer>(messageBus_, rect);

    Subscribe({Shared::MessageType::CloseWindow, Shared::MessageType::KeyPressed});
    for (const auto& entry : layers_) {
        auto& layer = entry.second;
        layer->SubscribeMessages();
    }

    for (const auto& entry : layers_) {
        auto& layer = entry.second;
        layer->OnLoad();
    }

    for (const auto& entry : layers_) {
        auto& layer = entry.second;
        layer->OnCreate();
    }
}

void IntroScene::Exit()
{
    Unsubscribe({Shared::MessageType::CloseWindow, Shared::MessageType::KeyPressed});
    for (const auto& entry : layers_) {
        auto& layer = entry.second;
        layer->UnsubscribeMessages();
    }
}

void IntroScene::DrawTo(sf::RenderTarget& renderTarget)
{
    for (const auto& entry : layers_) {
        auto& layer = entry.second;
        layer->Clear();
        layer->Draw();
        layer->DrawTo(renderTarget);
    }
}

void IntroScene::Update(float deltaTime)
{
    for (const auto& entry : layers_) {
        auto& layer = entry.second;
        layer->Update(deltaTime);
    }
}

void IntroScene::OnMessage(std::shared_ptr<Shared::Message> msg)
{
    if (msg->GetMessageType() == Shared::MessageType::CloseWindow) {
        auto m = std::dynamic_pointer_cast<Shared::CloseWindowMessage>(msg);
        OnCloseWindow();
    }
    else if (msg->GetMessageType() == Shared::MessageType::KeyPressed) {
        auto m = std::dynamic_pointer_cast<Shared::KeyPressedMessage>(msg);
        auto key = m->GetKey();
        if (key == sf::Keyboard::Key::Escape) {
            OnCloseWindow();
        }
        else if (key == sf::Keyboard::Key::Return) {
            SwitchScene<PlayScene>();
        }
    }
}

}  // namespace Scene

}  // namespace FA
