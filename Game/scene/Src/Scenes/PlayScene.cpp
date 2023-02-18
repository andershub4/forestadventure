/*
 *	Copyright (C) 2021 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#include "PlayScene.h"

#include <SFML/Graphics/RenderWindow.hpp>

#include "IntroScene.h"
#include "Layers/HelperLayer.h"
#include "Layers/LevelLayer.h"
#include "Layers/PreAlphaLayer.h"
#include "Message/BroadcastMessage/CloseWindowMessage.h"
#include "Message/BroadcastMessage/KeyPressedMessage.h"
#include "Screen.h"
#include "Transitions/FadeTransition.h"

namespace FA {

namespace Scene {

PlayScene::PlayScene(Manager& sceneManager, Shared::MessageBus& messageBus, Shared::TextureManager& textureManager,
                     Manager::Layers& layers, Manager::Data& data)
    : BasicScene(sceneManager, messageBus, textureManager, layers, data)
{}

PlayScene::~PlayScene() = default;

void PlayScene::Enter()
{
    sf::IntRect rect(0, 0, Shared::Screen::width, Shared::Screen::height);
    layers_.clear();
    layers_[LayerId::Level] = std::make_unique<LevelLayer>(messageBus_, rect, textureManager_);
#ifdef _DEBUG
    layers_[LayerId::Helper] = std::make_unique<HelperLayer>(messageBus_, rect, Name());
#endif
    layers_[LayerId::PreAlpha] = std::make_unique<PreAlphaLayer>(messageBus_, rect);

    // subscribe layer message before entity is created (so layer can receive EntityInitializedMessage)
    Subscribe({Shared::MessageType::CloseWindow, Shared::MessageType::KeyPressed, Shared::MessageType::GameOver});
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

void PlayScene::Exit()
{
    Unsubscribe({Shared::MessageType::CloseWindow, Shared::MessageType::KeyPressed, Shared::MessageType::GameOver});
    for (const auto& entry : layers_) {
        auto& layer = entry.second;
        layer->UnsubscribeMessages();
    }
}

void PlayScene::DrawTo(sf::RenderTarget& renderTarget)
{
    for (const auto& entry : layers_) {
        auto& layer = entry.second;
        layer->Clear();
        layer->Draw();
        layer->DrawTo(renderTarget);
    }
}

void PlayScene::Update(float deltaTime)
{
    for (const auto& entry : layers_) {
        auto& layer = entry.second;
        layer->Update(deltaTime);
    }
}

void PlayScene::OnMessage(std::shared_ptr<Shared::Message> msg)
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
    }
    else if (msg->GetMessageType() == Shared::MessageType::GameOver) {
        SwitchScene<IntroScene, FadeTransition>();
    }
}

}  // namespace Scene

}  // namespace FA
