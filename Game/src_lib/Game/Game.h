/*
 *	Copyright (C) 2021 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#pragma once

#include <iosfwd>
#include <memory>

#include <SFML/Graphics/RenderWindow.hpp>

#include "Layer.h"
#include "Message/MessageBus.h"
#include "Misc/TextureManager.h"
#include "SceneComponent/Level/Level.h"
#include "SceneComponent/SceneHelper/SceneHelper.h"

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
    SceneHelper sceneHelper_;
    Layer sceneHelperLayer_;

private:
    void RedirectSfmlLogEntries();
    void OnMessage(std::shared_ptr<Message> message);
    void InitWindow();
};

}  // namespace FA
