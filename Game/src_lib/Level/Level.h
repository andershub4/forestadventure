/*
 *	Copyright (C) 2021 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#pragma once

#include "Entity/Entity.h"

namespace FA {

class MessageBus;
class TextureManager;

class Level
{
public:
    Level(MessageBus& messageBus, TextureManager& textureManager);
    virtual ~Level();

    void Update(float deltaTime);
    void DrawTo(sf::RenderWindow& window);

private:
    MessageBus& messageBus_;
    Entity entity_;
};

}  // namespace FA
