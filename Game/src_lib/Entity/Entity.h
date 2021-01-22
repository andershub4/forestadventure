/*
 *	Copyright (C) 2021 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#pragma once

#include <SFML/Graphics/RectangleShape.hpp>

#include "Animation/AnimationHandler.h"
#include "Enum/KeyboardKey.h"
#include "Movement/Movement.h"

namespace FA {

class MessageBus;
class Message;
class TextureManager;
class Layer;

class Entity
{
public:
    Entity(MessageBus& messageBus, TextureManager& textureManager);

    void Update(float deltaTime);
    void DrawTo(Layer& layer);
    void OnMessage(std::shared_ptr<Message> msg);

private:
    MessageBus& messageBus_;
    AnimationHandler animationHandler_;
    Movement movement_;
    sf::RectangleShape rectShape_;

private:
    void RegisterAnimationInfo(TextureManager& textureManager);
    void OnIsKeyPressed(Keyboard::Key key);
    void OnKeyboardPressed(Keyboard::Key key);
};

}  // namespace FA
