/*
 *	Copyright (C) 2021 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#pragma once

#include <SFML/Graphics/RectangleShape.hpp>

#include "Entity/StateMachine.h"
#include "Enum/KeyboardKey.h"
#include "Fwd/SfmlFwd.h"

namespace FA {

class MessageBus;
class Message;

namespace Entity {

class BasicEntity
{
public:
    BasicEntity(MessageBus& messageBus, const AnimationFactory& animationFactory);
    ~BasicEntity();

    void Update(float deltaTime);
    void DrawTo(sf::RenderTarget& renderTarget);
    void OnMessage(std::shared_ptr<Message> msg);
    void ProcessMessages(bool process) { processMessages_ = process; }

private:
    MessageBus& messageBus_;
    sf::RectangleShape rectShape_;
    StateMachine stateMachine_;
    bool processMessages_ = true;

private:
    void OnIsKeyPressed(Keyboard::Key key);

private:
    void HandleMessage(std::shared_ptr<Message> msg);
};

}  // namespace Entity

}  // namespace FA
