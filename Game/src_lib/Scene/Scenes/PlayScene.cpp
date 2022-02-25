/*
 *	Copyright (C) 2021 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#include "PlayScene.h"

#include <SFML/Graphics/RenderWindow.hpp>

#include "Constant/Screen.h"
#include "IntroScene.h"
#include "Message/BroadcastMessage/KeyPressedMessage.h"
#include "Scene/Layers/HelperLayer.h"
#include "Scene/Layers/LevelLayer.h"
#include "Scene/Layers/PreAlphaLayer.h"
#include "Scene/Transitions/FadeTransition.h"

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

    for (const auto& entry : layers_) {
        auto& layer = entry.second;
        layer->OnCreate();
    }

    Subscribe({MessageType::CloseWindow, MessageType::KeyPressed});
}

void PlayScene::Exit()
{
    Unsubscribe({MessageType::CloseWindow, MessageType::KeyPressed});
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

void PlayScene::OnKeyPressed(Keyboard::Key key)
{
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
