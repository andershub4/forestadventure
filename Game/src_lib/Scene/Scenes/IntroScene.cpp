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
#include "Scene/Layers/HelperLayer.h"
#include "Scene/Layers/IntroLayer.h"
#include "Scene/Layers/PreAlphaLayer.h"

namespace FA {

namespace Scene {

IntroScene::IntroScene(Manager& sceneManager, MessageBus& messageBus, TextureManager& textureManager,
                       Manager::Layers& layers, Manager::Data& data)
    : BasicScene(sceneManager, messageBus, textureManager, layers, data)
{}

IntroScene::~IntroScene() = default;

void IntroScene::Enter()
{
    sf::IntRect rect(0, 0, constant::Screen::width, constant::Screen::height);
    layers_.clear();
    layers_[LayerId::Intro] = std::make_unique<IntroLayer>(messageBus_, rect);
#ifdef _DEBUG
    layers_[LayerId::Helper] = std::make_unique<HelperLayer>(messageBus_, rect, Name());
#endif
    layers_[LayerId::PreAlpha] = std::make_unique<PreAlphaLayer>(messageBus_, rect);

    for (const auto& entry : layers_) {
        auto& layer = entry.second;
        layer->OnCreate();
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
