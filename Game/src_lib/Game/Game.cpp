/*
 *	Copyright (C) 2021 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#include "Game.h"

#include <fstream>
#include <memory>

#include <SFML/Config.hpp>

#include "Constant/Screen.h"
#include "Message/BroadcastMessage/CloseWindowMessage.h"
#include "Message/BroadcastMessage/KeyPressedMessage.h"
#include "System/InputSystem.h"
#include "Utils/Logger.h"
#include "Utils/Path.h"
#include "Version.h"

namespace FA {

Game::Game()
    : sceneHelper_(messageBus_, "GamePlayScene")
    , level_(messageBus_, textureManager_)
{
    LOG_INFO_ENTER_FUNC();

    InitWindow();
    auto cb = [this](std::shared_ptr<Message> message) { OnMessage(message); };
    messageBus_.AddSubscriber("game", {MessageType::KeyPressed, MessageType::CloseWindow}, cb);

    LOG_INFO_EXIT_FUNC();
}

void Game::GameLoop()
{
    LOG_INFO_ENTER_FUNC();
    sf::Clock clock;
    InputSystem inputSystem(messageBus_, window_);

    while (window_.isOpen()) {
        sf::Time elapsed = clock.restart();
        float deltaTime = elapsed.asSeconds();

        inputSystem.Update(deltaTime);
        messageBus_.DispatchMessages();

        level_.Update(deltaTime);

        window_.clear();

        level_.DrawTo(levelLayer_);
        levelLayer_.DrawTo(window_);
#ifdef _DEBUG
        sceneHelper_.DrawTo(sceneHelperLayer_);
        sceneHelperLayer_.DrawTo(window_);
#endif
        window_.display();
    }

    LOG_INFO_EXIT_FUNC();
}

void Game::OnMessage(std::shared_ptr<Message> message)
{
    if (message->GetMessageType() == MessageType::KeyPressed) {
        auto m = std::dynamic_pointer_cast<KeyPressedMessage>(message);
        auto key = m->GetKey();
        if (key == Keyboard::Key::Escape) {
            window_.close();
        }
    }
    else if (message->GetMessageType() == MessageType::CloseWindow) {
        window_.close();
    }
    else {
        // cant happened
    }
}

void Game::InitWindow()
{
    LOG_INFO("Create main window");
#ifdef _DEBUG
    const std::string title = std::string(FA_APP_NAME) + " v" + FA_APP_VERSION;
    window_.create(sf::VideoMode(constant::Screen::width, constant::Screen::height), title);
#else
    window_.create(sf::VideoMode::getDesktopMode(), FA_APP_NAME, sf::Style::Fullscreen);
    view_.reset(sf::FloatRect(0.0, 0.0, constant::Screen::width_f, constant::Screen::height_f));
    window_.setView(view_);
#endif
    window_.setFramerateLimit(120);
}

}  // namespace FA
