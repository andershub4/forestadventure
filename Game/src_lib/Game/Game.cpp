/*
 *	Copyright (C) 2021 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#include "Game.h"

#include <SFML/Graphics/RenderWindow.hpp>

#include "Constant/Screen.h"
#include "Logging.h"
#include "Manager.h"
#include "Message/MessageBus.h"
#include "Resource/TextureManager.h"
#include "SfmlLog.h"
#include "System/InputSystem.h"
#include "UI/Title.h"
#include "Version.h"

namespace FA {

int Game::Run()
{
    LOG_INFO_ENTER_FUNC();
    LOG_INFO("%s version %s", FA_APP_NAME, FA_APP_VERSION);
    LOG_INFO("SFML version %u.%u.%u", SFML_VERSION_MAJOR, SFML_VERSION_MINOR, SFML_VERSION_PATCH);

    try {
        GameLoop();
    }
    catch (const std::exception& e) {
        LOG_ERROR("Exception catched: ", e.what());
        return EXIT_FAILURE;
    }

    LOG_INFO_EXIT_FUNC();
    return EXIT_SUCCESS;
}

void Game::GameLoop()
{
    LOG_INFO("Create main window");
    sf::RenderWindow window;
    const std::string title = UI::GetTitle();
#ifdef _DEBUG
    window.create(sf::VideoMode(Shared::Screen::width, Shared::Screen::height), title);
#else
    window.create(sf::VideoMode::getDesktopMode(), title, sf::Style::Fullscreen);
    sf::View view;
    view.reset(sf::FloatRect(0.0, 0.0, Shared::Screen::width_f, Shared::Screen::height_f));
    window.setView(view);
#endif
    window.setFramerateLimit(120);

    Shared::MessageBus messageBus;
    Shared::TextureManager textureManager;
    Scene::Manager sceneManager(messageBus, textureManager);
    SfmlLog sfmlLog;
    sf::Clock clock;
    InputSystem inputSystem(messageBus, window);

    sfmlLog.Init();
    LOG_INFO("Start main loop");
    while (sceneManager.IsRunning()) {
        sf::Time elapsed = clock.restart();
        float deltaTime = elapsed.asSeconds();
        inputSystem.Update(deltaTime);
        sceneManager.Update(deltaTime);
        window.clear();
        sceneManager.DrawTo(window);
        window.display();
    }

    window.close();
}

}  // namespace FA
