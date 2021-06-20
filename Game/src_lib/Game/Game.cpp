/*
 *	Copyright (C) 2021 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#include "Game.h"

#include "Constant/Screen.h"
#include "Logging.h"
#include "Message/BroadcastMessage/CloseWindowMessage.h"
#include "Message/BroadcastMessage/KeyPressedMessage.h"
#include "System/InputSystem.h"
#include "UI/Title.h"

namespace FA {

Game::Game()
    : sceneManager_(messageBus_, textureManager_)
{
    LOG_INFO_ENTER_FUNC();

    InitWindow();
    auto cb = [this](std::shared_ptr<Message> message) { OnMessage(message); };
    messageBus_.AddSubscriber("game", {MessageType::KeyPressed, MessageType::CloseWindow}, cb);

    LOG_INFO_EXIT_FUNC();
}

Game::~Game() = default;

void Game::GameLoop()
{
    LOG_INFO_ENTER_FUNC();

    sf::Clock clock;
    InputSystem inputSystem(messageBus_, window_);

    while (sceneManager_.IsRunning()) {
        sf::Time elapsed = clock.restart();
        float deltaTime = elapsed.asSeconds();

        inputSystem.Update(deltaTime);
        messageBus_.DispatchMessages();

        sceneManager_.Update(deltaTime);

        window_.clear();
        sceneManager_.DrawTo(window_);
        window_.display();
    }

    window_.close();

    LOG_INFO_EXIT_FUNC();
}

void Game::OnMessage(std::shared_ptr<Message> message)
{
    if (message->GetMessageType() == MessageType::KeyPressed) {
        sceneManager_.OnKeyPressed(message);
    }
    else if (message->GetMessageType() == MessageType::CloseWindow) {
        sceneManager_.OnCloseWindow(message);
    }
    else {
        // cant happen
    }
}

void Game::InitWindow()
{
    LOG_INFO("Create main window");
    const std::string title = UI::GetTitle();
#ifdef _DEBUG
    window_.create(sf::VideoMode(constant::Screen::width, constant::Screen::height), title);
#else
    window_.create(sf::VideoMode::getDesktopMode(), title, sf::Style::Fullscreen);
    view_.reset(sf::FloatRect(0.0, 0.0, constant::Screen::width_f, constant::Screen::height_f));
    window_.setView(view_);
#endif
    window_.setFramerateLimit(120);
}

}  // namespace FA
