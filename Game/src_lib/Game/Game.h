/*
 *	Copyright (C) 2021 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#pragma once

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
    void GameLoop();

private:
    MessageBus messageBus_;
    sf::RenderWindow window_;
    sf::View view_;
    TextureManager textureManager_;
    Level level_;
    Layer levelLayer_;
    SceneHelper sceneHelper_;
    Layer sceneHelperLayer_;

private:
    void OnMessage(std::shared_ptr<Message> message);
    void InitWindow();
};

}  // namespace FA
