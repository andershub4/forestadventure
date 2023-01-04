/*
 *	Copyright (C) 2021 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#include "PlayScene.h"

#include <SFML/Graphics/RenderWindow.hpp>

#include "Constant/Screen.h"
#include "IntroScene.h"
#include "Layers/HelperLayer.h"
#include "Layers/LevelLayer.h"
#include "Layers/PreAlphaLayer.h"
#include "Message/BroadcastMessage/CloseWindowMessage.h"
#include "Message/BroadcastMessage/KeyPressedMessage.h"
#include "Transitions/FadeTransition.h"

namespace FA {

namespace Scene {

PlayScene::PlayScene(Manager& sceneManager, MessageBus& messageBus, TextureManager& textureManager,
                     Manager::Layers& layers, Manager::Data& data)
    : BasicScene(sceneManager, messageBus, textureManager, layers, data)
{}

PlayScene::~PlayScene() = default;

void PlayScene::Enter()
{
    sf::IntRect rect(0, 0, constant::Screen::width, constant::Screen::height);
    layers_.clear();
    layers_[LayerId::Level] = std::make_unique<LevelLayer>(messageBus_, rect, textureManager_);
#ifdef _DEBUG
    layers_[LayerId::Helper] = std::make_unique<HelperLayer>(messageBus_, rect, Name());
#endif
    layers_[LayerId::PreAlpha] = std::make_unique<PreAlphaLayer>(messageBus_, rect);

    // subscribe layer message before entity is created (so layer can receive EntityCreatedMessage)
    Subscribe({MessageType::CloseWindow, MessageType::KeyPressed, MessageType::GameOver});
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
    Unsubscribe({MessageType::CloseWindow, MessageType::KeyPressed, MessageType::GameOver});
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

void PlayScene::OnMessage(std::shared_ptr<Message> msg)
{
    if (msg->GetMessageType() == MessageType::CloseWindow) {
        auto m = std::dynamic_pointer_cast<CloseWindowMessage>(msg);
        OnCloseWindow();
    }
    else if (msg->GetMessageType() == MessageType::KeyPressed) {
        auto m = std::dynamic_pointer_cast<KeyPressedMessage>(msg);
        auto key = m->GetKey();
        if (key == sf::Keyboard::Key::Escape) {
            OnCloseWindow();
        }
    }
    else if (msg->GetMessageType() == MessageType::GameOver) {
        SwitchScene<IntroScene, FadeTransition>();
    }
}

}  // namespace Scene

}  // namespace FA
