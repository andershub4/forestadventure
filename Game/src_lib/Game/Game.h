/*
 *	Copyright (C) 2021 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#pragma once

#include <iosfwd>
#include <memory>

#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#ifdef _DEBUG
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/Text.hpp>
#endif

#include "Layer.h"
#include "Level/Level.h"
#include "Message/MessageBus.h"
#include "Misc/TextureManager.h"

namespace FA {

class Game
{
public:
    Game();
    ~Game();
    void GameLoop();

public:
    static const sf::Vector2u screen;
    static const sf::Vector2u centerScreen;

private:
    MessageBus messageBus_;
    std::unique_ptr<std::ofstream> sfmlLogStream_;
    sf::RenderWindow window_;
    sf::View view_;
    TextureManager textureManager_;
    Level level_;
    Layer levelLayer_;
#ifdef _DEBUG
    sf::RectangleShape dotShape_;
    sf::Font font_;
    sf::Text sceneText_;
#endif

private:
    void RedirectSfmlLogEntries();
    void OnMessage(std::shared_ptr<Message> message);
    void InitWindow();
#ifdef _DEBUG
    void InitDebugSceneGraphics();
#endif
};

}  // namespace FA
