/*
 *	Copyright (C) 2021 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#pragma once

#include <SFML/Graphics/RectangleShape.hpp>

#include "EntityState/EntityStateMachine.h"
#include "Enum/KeyboardKey.h"

namespace FA {

class MessageBus;
class Message;
class Layer;

class Entity
{
public:
    Entity(MessageBus& messageBus, const AnimationFactory& animationFactory);
    ~Entity();

    void Update(float deltaTime);
    void DrawTo(Layer& layer);
    void OnMessage(std::shared_ptr<Message> msg);

private:
    MessageBus& messageBus_;
    sf::RectangleShape rectShape_;
    EntityStateMachine stateMachine_;

private:
    void OnIsKeyPressed(Keyboard::Key key);
};

}  // namespace FA
