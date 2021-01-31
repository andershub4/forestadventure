/*
 *	Copyright (C) 2021 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#pragma once

#include <SFML/Graphics/RectangleShape.hpp>

#include "EntityState/EntityStateMachine.h"
#include "Enum/KeyboardKey.h"
#include "Fwd/SfmlFwd.h"

namespace FA {

class MessageBus;
class Message;

class Entity
{
public:
    Entity(MessageBus& messageBus, const AnimationFactory& animationFactory);
    ~Entity();

    void Update(float deltaTime);
    void DrawTo(sf::RenderTarget& renderTarget);
    void OnMessage(std::shared_ptr<Message> msg);
    void ProcessMessages(bool process) { processMessages_ = process; }

private:
    MessageBus& messageBus_;
    sf::RectangleShape rectShape_;
    EntityStateMachine stateMachine_;
    bool processMessages_ = true;

private:
    void OnIsKeyPressed(Keyboard::Key key);

private:
    void HandleMessage(std::shared_ptr<Message> msg);
};

}  // namespace FA
