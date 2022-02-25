/*
 *	Copyright (C) 2021 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#include "Game.h"

#include "Constant/Screen.h"
#include "Logging.h"
#include "System/InputSystem.h"
#include "UI/Title.h"

namespace FA {

Game::Game()
    : sceneManager_(messageBus_, textureManager_)
{
    LOG_INFO_ENTER_FUNC();
    InitWindow();
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
